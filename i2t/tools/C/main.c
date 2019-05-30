#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

//User inputs:
uint8_t userShift = 7;
//Maximum average current you want to support:
int32_t userMaxAvgCurrent = 5000;			//mA
//Maximum peak current you want to support, and duration:
int32_t userCurrentLimit = 17500;			//mA
float userCurrentLimitTime = 1;				//s
//Non-linear threshold
int32_t userNlTresh = 22500;

//Values that will get programmed:
uint8_t I2T_SHIFT = 0;
int32_t I2T_LEAK = 0;
int32_t I2T_LIMIT = 0;
int32_t I2T_WARNING = 0;
int32_t I2T_NON_LINEAR_THRESHOLD = 0;

//Has to match HW & firmware:
float dt = 0.1;      					//Every 100ms
//At what fraction of the max to you want a warning? (0-1)
float warn = 0.8;

//Input variable limits:
#define LIM_L_SHIFT				5
#define LIM_H_SHIFT				7
#define LIM_L_AVG_CURRENT		1000
#define LIM_H_AVG_CURRENT		30000
#define LIM_L_CURRENT			1000
#define LIM_H_CURRENT			30000
#define LIM_L_NL_CURRENT		1000
#define LIM_H_NL_CURRENT		30000
#define LIM_L_CURR_LIM_TIME		0.01
#define LIM_H_CURR_LIM_TIME		20

//Prototypes:
void printUserInputs(int32_t maxAvgCurrent, int32_t currentLimit, float currentLimitTime, int32_t nlTresh, uint8_t shift);
int32_t precheckI2tUserRequests(int32_t* maxAvgCurrent, int32_t* currentLimit, float* currentLimitTime, int32_t* nlTresh, uint8_t* shift);
int32_t calculateI2tConstants(int32_t maxAvgCurrent, int32_t currentLimit, float currentLimitTime, int32_t nlTresh, uint8_t shift);
void printI2tConstants(void);
void test(int32_t current);

#ifndef BOARD_TYPE_FLEXSEA_PLAN

int main(void)
{
	printf( "I2t Configuration\n");
	printf("==================\n\n");

	printUserInputs(userMaxAvgCurrent, userCurrentLimit, userCurrentLimitTime, userNlTresh, userShift);

	int r = precheckI2tUserRequests(&userMaxAvgCurrent, &userCurrentLimit, &userCurrentLimitTime, &userNlTresh, &userShift);
	if(!r){printf("All values in range.\n\n");}
	else
	{
		printf("Attention! Value(s) modified to fit limits.\nNew values:\n\n");
		printUserInputs(userMaxAvgCurrent, userCurrentLimit, userCurrentLimitTime, userNlTresh, userShift);
	}

	calculateI2tConstants(userMaxAvgCurrent, userCurrentLimit, userCurrentLimitTime, userNlTresh, userShift);
	printI2tConstants();

	test(25000);
}

#endif

int32_t precheckI2tUserRequests(int32_t* maxAvgCurrent, int32_t* currentLimit, float* currentLimitTime, int32_t* nlTresh, uint8_t* shift)
{
	uint8_t errors = 0;

	//First pass - input range:
	//=========================

	//Average current:
	if(!(*maxAvgCurrent >= LIM_L_AVG_CURRENT))
	{
		*maxAvgCurrent = LIM_L_AVG_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	if(!(*maxAvgCurrent <= LIM_H_AVG_CURRENT))
	{
		*maxAvgCurrent = LIM_H_AVG_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	//Maximum current:
	if(!(*currentLimit >= LIM_L_CURRENT))
	{
		*currentLimit = LIM_L_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	if(!(*currentLimit <= LIM_H_CURRENT))
	{
		*currentLimit = LIM_H_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	//Time at limit
	if(!(*currentLimitTime >= LIM_L_CURR_LIM_TIME))
	{
		*currentLimitTime = LIM_L_CURR_LIM_TIME;
		errors++;
		//ToDo: Flag in GUI
	}

	if(!(*currentLimitTime <= LIM_H_CURR_LIM_TIME))
	{
		*currentLimitTime = LIM_H_CURR_LIM_TIME;
		errors++;
		//ToDo: Flag in GUI
	}

	//Non-linear treshold
	if(!(*nlTresh >= LIM_L_NL_CURRENT))
	{
		*nlTresh = LIM_L_NL_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	if(!(*nlTresh <= LIM_H_NL_CURRENT))
	{
		*nlTresh = LIM_H_NL_CURRENT;
		errors++;
		//ToDo: Flag in GUI
	}

	//Bit shifting
	if(!(*shift >= LIM_L_SHIFT && *shift <= LIM_H_SHIFT))
	{
		*shift = LIM_L_SHIFT;
		errors++;
		//ToDo: Flag in GUI
	}

	if(!(*shift <= LIM_H_SHIFT))
	{
		*shift = LIM_H_SHIFT;
		errors++;
		//ToDo: Flag in GUI
	}

	//Second pass - relations:
	//========================

	if(*maxAvgCurrent >= *currentLimit)
	{
		*currentLimit = *maxAvgCurrent + 1;
		errors++;
		//ToDo: Flag in GUI
	}

	if(*nlTresh <= *maxAvgCurrent)
	{
		*nlTresh = *maxAvgCurrent + 1;
		errors++;
		//ToDo: Flag in GUI
	}

	return errors;
}

int32_t calculateI2tConstants(int32_t maxAvgCurrent, int32_t currentLimit, float currentLimitTime, int32_t nlTresh, uint8_t shift)
{
	I2T_SHIFT = shift;

	int32_t c_shifted = (maxAvgCurrent >> shift);
	double c = (double)c_shifted;
	I2T_LEAK = (int32_t)pow(c,2);

	c_shifted = (currentLimit >> shift);
	c = (double)c_shifted;
	int32_t d = (int32_t)pow(c, 2);
	I2T_LIMIT = (currentLimitTime / dt) * (d - I2T_LEAK);

	I2T_WARNING = (int32_t) (warn * I2T_LIMIT);

	//8-bit non-lin:
	I2T_NON_LINEAR_THRESHOLD = nlTresh >> shift;

	return 1;
}

void printUserInputs(int32_t maxAvgCurrent, int32_t currentLimit, float currentLimitTime, int32_t nlTresh, uint8_t shift)
{
	printf("maxAvgCurrent: %i\n", maxAvgCurrent);
	printf("currentLimit: %i\n", currentLimit);
	printf("currentLimitTime: %f\n", currentLimitTime);
	printf("nlTresh: %i\n", nlTresh);
	printf("shift: %i\n", shift);
	printf("\n");
}

void printI2tConstants(void)
{
	printf("I2T_LEAK: %i\n", I2T_LEAK);
	printf("I2T_LIMIT: %i\n", I2T_LIMIT);
	printf("I2T_WARN: %i\n", I2T_WARNING);
	printf("I2T_NON_LIN_TRESH: %i\n", I2T_NON_LINEAR_THRESHOLD);
	printf("\n");
}

void test(int32_t current)
{
	//Current:
	int32_t c_shifted = (current >> I2T_SHIFT);
	double c = (double)c_shifted;
	int32_t tmp = (int32_t)pow(c,2);

	int32_t currNl = current - (I2T_NON_LINEAR_THRESHOLD << I2T_SHIFT);
	if(currNl < 0){currNl = 0;}
	int32_t currCombo = (current + 10*currNl) >> I2T_SHIFT;
	c = (double)currCombo;
	int32_t tmpNl = (int32_t)pow(c,2);

	//Time:
	float time = (float)((float)I2T_LIMIT * dt) / ( tmp - I2T_LEAK );
	float timeNl = (float)((float)I2T_LIMIT * dt) / ( tmpNl - I2T_LEAK );

	//Print results:
	printf("Time at given current (%i mA):\n", current);
	printf("%fs\n", time);
	printf("Including non-linearity:\n");
	printf("%fs\n", timeNl);
}
