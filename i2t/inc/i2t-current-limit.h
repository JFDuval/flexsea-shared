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

#ifndef INC_I2TCURRENT_H
#define INC_I2TCURRENT_H

//****************************************************************************
// Include(s)
//****************************************************************************
#include <stdint.h>
struct i2t_s
{
	uint8_t shift;
	uint16_t leak;
	uint32_t limit;
	uint32_t warning;
	uint8_t nonLinThreshold;	//ToDo Change to uint16
	uint8_t useNL;
	uint8_t config;
};

#if(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)

#include "main.h"



//****************************************************************************
// Structure(s):
//****************************************************************************





//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void i2t_sample(int32_t lastCurrentRead);
int i2t_compute(void);
void updateI2tSettings(struct i2t_s i2t);
uint8_t i2t_get_percentage(void);
uint8_t i2t_get_flag(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Important: the settings below are the DEFAULT. Mn can now update them.

//The algorithm uses 8-bit values: we need to scale down the maximum current
//accordingly. It uses real units (mA). Ex.: ±30000mA sensor =>
//30000/256 = 117 => shift 7 (div by 128). 30A will give us 234
#ifndef BOARD_SUBTYPE_POCKET
#define I2C_SCALE_DOWN_SHIFT	7
#else
#define I2C_SCALE_DOWN_SHIFT	5
#endif
//We use a leaky integrator. The leak should be set to the maximum sustained
//current required by your application. It's applied on the squared value (so 
//max current = 65536). Pick a fraction of that number. Ex.: if the max current
//that your sensor can read is 30A and you wan to support 10A continuous, 
//use (10000 >> I2C_SCALE_DOWN_SHIFT)^2 = 6104. With 10A flowing, your 
//integrator will stay at 0. Anything above it will increase its count.
#ifndef BOARD_SUBTYPE_POCKET
//#define I2T_LEAK				382		//2.5A
//#define I2T_LEAK				1526	//5A
//#define I2T_LEAK				6104	//10A
#define I2T_LEAK				13732	//15A
#else
#define I2T_LEAK				4944	//2.25A
#endif
//What current limit do you want?
//Limit = (TIME_AT_LIMIT_CURR / dt) * ( (CURR_LIMIT>>I2C_SCALE_DOWN_SHIFT)^2 - I2T_LEAK )
//Ex.: 15A for 10s 
//	Limit = (10s / 100ms) * ( (15000mA/128)^2 - 6104)
//	Limit = 100 * ( 13733 - 6104) = 762891
#ifndef BOARD_SUBTYPE_POCKET
//#define I2T_LIMIT				71411	//8A 3s
//#define I2T_LIMIT				100135	//15A 750ms (2.5A cont.)
//#define I2T_LIMIT				76294	//15A 1s (10A cont.)
//#define I2T_LIMIT				171661	//17.5A 1s (5A cont.)
#define I2T_LIMIT				458221	//50A 0.33s (15A cont.)
#else
#define I2T_LIMIT				302124	//6A 1s
#endif
#define I2T_WARNING				(0.8*I2T_LIMIT)
//#define I2T_NON_LIN_TRESHOLD	125		//16000mA/(2^7) = 125
//#define I2T_NON_LIN_TRESHOLD	195		//25000mA/(2^7) = 195
#define I2T_NON_LIN_TRESHOLD	255		//55000mA/(2^7) = 429 (invalid, > 255)

//How long will it last at 11A?
//time = (Limit * dt) / ( (CURR>>I2C_SCALE_DOWN_SHIFT)^2 - I2T_LEAK )
//time = (762891 * 0.1) / ( (11000mA>>7)^2 - 6104 ) = 76289 / (7385 - 6104)
//time = 1 minute

//Please note that there is an Octave/Matlab script in /ref/. It makes this 
//calculation faster, and it plots limit vs time.
//http://dephy.com/wiki/flexsea/doku.php?id=i2t

//ADC readings:
#define I2T_SAMPLES				8
#define I2T_SAMPLES_SHIFT		3

//Return values:
#define RET_I2T_NORMAL			0
#define RET_I2T_WARNING			1
#define RET_I2T_LIMIT			2

#define I2T_ENABLE_NON_LIN		0x80
#define I2T_DISABLE_NON_LIN		0x00

#endif 	//INC_I2TCURRENT_H

#endif	//(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)
