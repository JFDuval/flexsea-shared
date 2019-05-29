#ifndef INC_MN_RE_INTERFACE_H
#define INC_MN_RE_INTERFACE_H

//****************************************************************************
// Include(s)
//****************************************************************************

//****************************************************************************
// Shared variable(s)
//****************************************************************************


//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Definition(s):
//****************************************************************************

//MnRe Interface:
#define MNRE_DEBOUNCE				2
#define MNRE_PULSE_LEN				15
#define MNRE_PULSE_WIGGLE			2


/*
#define EX_I2C_ADDR					0x66	//7-bits: 0x33
#define EX_I2C_TIMEOUT				10

//EZI2C Buffer (Execute):
#define EX_EZI2C_WBUF_SIZE			8
#define EX_EZI2C_RBUF_SIZE			20
#define EX_EZI2C_BUF_SIZE			(EX_EZI2C_WBUF_SIZE + EX_EZI2C_RBUF_SIZE)

//EZI2C Shared memory locations (Execute):
#define EX_MEM_W_CONTROL1			0
#define EX_MEM_W_CONTROL2			1
//#define UNUSED					2
//#define UNUSED					3
//#define UNUSED					4
//#define UNUSED					5
//#define UNUSED					6
//#define UNUSED					7
#define EX_MEM_R_MOT_ANGLE3			8
#define EX_MEM_R_MOT_ANGLE2			9
#define EX_MEM_R_MOT_ANGLE1			10
#define EX_MEM_R_MOT_ANGLE0			11
#define EX_MEM_R_MOT_VEL3			12
#define EX_MEM_R_MOT_VEL2			13
#define EX_MEM_R_MOT_VEL1			14
#define EX_MEM_R_MOT_VEL0			15
#define EX_MEM_R_STRAINH			16
#define EX_MEM_R_STRAINL			17
#define EX_MEM_R_CURRENT3			18
#define EX_MEM_R_CURRENT2			19
#define EX_MEM_R_CURRENT1			20
#define EX_MEM_R_CURRENT0			21
#define EX_MEM_R_PWMH				22
#define EX_MEM_R_PWML				23
#define EX_MEM_R_STATUSH			24
#define EX_MEM_R_STATUSL			25
//#define UNUSED					26
//#define UNUSED					27

//Manage:
#define MN_WBUF_SIZE				12
#define MN_RBUF_SIZE				4
#define MN_BUF_SIZE					(MN_WBUF_SIZE + MN_RBUF_SIZE)

//Manage shared memory locations:
//(Re writes to Manage)
#define MN_W_CONTROL1				0
#define MN_W_CONTROL2				1
#define MN_W_VB_MSB					2
#define MN_W_VB_LSB					3
#define MN_W_VG_MSB					4
#define MN_W_VG_LSB					5
#define MN_W_5V_MSB					6
#define MN_W_5V_LSB					7
#define MN_W_CURRENT_MSB			8
#define MN_W_CURRENT_LSB			9
#define MN_W_TEMP					10
#define MN_W_STATUS					11
//(Re reads from Manage) //ToDo
#define MN_R_B0						0
#define MN_R_B1						1
#define MN_R_B2						2
#define MN_R_B3						3

#define I2C_READ_KEY				0x55
#define I2T_ENABLE_NON_LIN			0x80
#define I2T_DISABLE_NON_LIN			0x00
*/

#endif // INC_MN_RE_INTERFACE_H

