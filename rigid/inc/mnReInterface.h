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

enum MN_RE_MSG{MN_BOOTED = 0, NEW_CONFIG};

//Manage:
#define MN_WBUF_SIZE				12
#define MN_RBUF_SIZE				12
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

#endif // INC_MN_RE_INTERFACE_H
