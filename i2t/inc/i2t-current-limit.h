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
#if(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)
#include "main.h"
#endif	//(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)
	
//****************************************************************************
// Structure(s):
//****************************************************************************

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

enum i2tPresets_s{I2T_RE_PRESET_A = 0, I2T_RE_PRESET_B};

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

uint8_t presetI2t(struct i2t_s *i, enum i2tPresets_s b);

#if(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)

void initI2t(void);	
void i2t_sample(int32_t lastCurrentRead);
int i2t_compute(void);
void updateI2tSettings(struct i2t_s i2t);
uint8_t i2t_get_percentage(void);
uint8_t i2t_get_flag(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//ADC readings:
#define I2T_SAMPLES				8
#define I2T_SAMPLES_SHIFT		3

//Return values:
#define RET_I2T_NORMAL			0
#define RET_I2T_WARNING			1
#define RET_I2T_LIMIT			2

#define I2T_ENABLE_NON_LIN		0x80
#define I2T_DISABLE_NON_LIN		0x00

#endif	//(defined BOARD_TYPE_FLEXSEA_EXECUTE || defined BOARD_TYPE_FLEXSEA_REGULATE)

#endif 	//INC_I2TCURRENT_H
