/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'shared/i2t': Safety Features
	Copyright (C) 2019 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developer] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab 
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors] 
*****************************************************************************
	[This file] I2t current limit
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-14 | jfduval | New file
	* 2019-03-26 | jfduval | Moved to flexsea-shared, cleaned
****************************************************************************/

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include <stdlib.h>
#include "i2t-current-limit.h"
#include "i2t-squares.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

int16_t currentSamples[I2T_SAMPLES];
uint8_t currentSampleIndex = 0;
uint8_t currentLimitFlag = 0;
uint8_t i2tPct = 0;

//Structure with default values:
struct i2t_s i2t = {.shift = I2C_SCALE_DOWN_SHIFT, .leak = I2T_LEAK, \
					.limit = I2T_LIMIT, .warning = I2T_WARNING, \
					.nonLinThreshold = I2T_NON_LIN_TRESHOLD, \
					.useNL = I2T_ENABLE_NON_LIN};

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static uint8 getCurrentSampleIndex(void);
static void resetCurrentSampleIndex(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function every ms, and give it the latest current reading
//Use a signed value, without offset
void i2t_sample(int32 lastCurrentRead)
{
	static int tb_div = 1;
	uint8_t index = 0;
	
	//We create a 12ms timebase to get 8 samples per calculation:
	tb_div++;
	tb_div %= 12;
	if(!tb_div)
	{
		//Ready for a new sample:
		index = getCurrentSampleIndex();
		if(index < I2T_SAMPLES)
		{
			//Only save I2T_SAMPLES, values, if there is more we discard.
			currentSamples[index] = lastCurrentRead;
		}
	}
}

//Call this function every 100ms. It will use the last samples saved by i2t_sample()
//Return: RET_I2T_[NORMAL, WARNING, LIMIT]
int i2t_compute(void)
{
	int32_t i = 0;
	int32_t sampleAverage = 0, nonLinGain = 0;
	uint32_t squaredCurrent = 0;
	static uint32_t integral = 0;
	
	//Average samples:
	for(i = 0; i < I2T_SAMPLES; i++)
	{
		//We use absolute values:
		sampleAverage += abs(currentSamples[i]);
	}
	sampleAverage = (sampleAverage >> I2T_SAMPLES_SHIFT);
	resetCurrentSampleIndex();	//Ready for next cycle
	
	//Now we need to bring that value down to 8bits-ish, and saturate it:
	sampleAverage = sampleAverage >> i2t.shift;
	
	if(i2t.useNL == I2T_ENABLE_NON_LIN)
	{
		//Non-linearity at high currents:
		if(sampleAverage > i2t.nonLinThreshold)
		{
			nonLinGain = 10*(sampleAverage - i2t.nonLinThreshold);
			sampleAverage += nonLinGain;
		}
		//Note: saturation limits the impact of this function at high currents
	}
	
	//Saturation
	if(sampleAverage > SQUARE_MAX){sampleAverage = SQUARE_MAX;}
	
	//We are now ready to square the value and add it to our integral:
	squaredCurrent = squared[sampleAverage];
	integral = integral + squaredCurrent;
	if(integral > i2t.leak)
	{
		integral -= i2t.leak;
	}
	else
	{
		integral = 0;
	}
	
	//Last step: limits
	if(integral < i2t.warning)
	{
		//Lower than the warning treshold
		currentLimitFlag = RET_I2T_NORMAL;
		return currentLimitFlag;
	}
	else
	{
		if(integral < i2t.limit)
		{
			//Warning - getting close to the limit
			currentLimitFlag = RET_I2T_WARNING;
			return currentLimitFlag;
		}
		else
		{
			//Problems!
			currentLimitFlag = RET_I2T_LIMIT;
			return currentLimitFlag;
		}
	}
}

void updateI2tSettings(struct i2t_s newI2t)
{
	//ToDo add safety checks!
	
	//Set values not shared:
	newI2t.warning = (4*newI2t.limit) / 5;	//80%
	//Compute from what's received:
	newI2t.shift = (newI2t.config & 0x0F);
	newI2t.useNL = (newI2t.config & 0x80);	
	
	//Copy structure:
	i2t = newI2t;
}

//Returns the %. 0% means no integral, 100% = we are at the limit.
uint8_t i2t_get_percentage(void){return i2tPct;}

//Return the current limit flag
uint8_t i2t_get_flag(void){return currentLimitFlag;}

//****************************************************************************
// Private Function(s)
//****************************************************************************

static uint8_t getCurrentSampleIndex(void)
{
	currentSampleIndex++;
	return currentSampleIndex-1;
}

static void resetCurrentSampleIndex(void)
{
	currentSampleIndex = 0;
}
