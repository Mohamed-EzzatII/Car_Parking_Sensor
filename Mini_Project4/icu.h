 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the ICU AVR driver
 *
 * Author: Mohamed Ezzat
 *
 * created date : 6/10/2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

/*******************************************************************************
 *                                Inclusions                                  *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                         	   Type Definitions                                *
 *******************************************************************************/

typedef enum{
	FALLING_EDGE,RISING_EDGE
}ICU_edge_Type;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_clock;

typedef struct
{
	ICU_clock 	  clock;
	ICU_edge_Type edge;
}ICU_ConfigType;


/*******************************************************************************
 *                         FUNCTIONS Prototypes                                *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_edge_Type edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
