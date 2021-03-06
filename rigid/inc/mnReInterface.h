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

//MnRe Interface (two DIOs):
#define MNRE_DEBOUNCE				2
#define MNRE_PULSE_LEN				15
#define MNRE_PULSE_WIGGLE			2

enum MN_RE_MSG{MN_BOOTED = 0, NEW_CONFIG, GET_SESSION};

//I2C buffers:
#define MN_WBUF_SIZE				12	//Re writes to Mn
#define MN_RBUF_SIZE				14	//Re reads from Mn (config)
#define MN_BUF_SIZE					(MN_WBUF_SIZE + MN_RBUF_SIZE)

//Payload type:
#define MNRE_REGULAR_UPDATE			0x33
#define MNRE_SESSION_STATS			0xAA	//Starting address

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

//Re writes Session Stats to Manage sometimes
#define MN_W_ACTIVE_SESSION         2
#define MN_W_LENGTH_MSB             3
#define MN_W_LENGTH_LSB             4
#define MN_W_MWH_3                  5
#define MN_W_MWH_2                  6
#define MN_W_MWH_1                  7
#define MN_W_MWH_0                  8
#define MN_W_END                    9
#define MN_W_DUMMY1                 10
#define MN_W_DUMMY2                 11

//(Re reads from Manage buffer: not defined)

#define I2C_READ_KEY				0x55
#define I2T_ENABLE_NON_LIN			0x80
#define I2T_DISABLE_NON_LIN			0x00

#endif // INC_MN_RE_INTERFACE_H
