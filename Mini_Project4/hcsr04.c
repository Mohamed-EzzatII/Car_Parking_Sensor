/******************************************************************************
 *
 * Module: Ultrasonic HCSR04
 *
 * File Name: hcsr04.c
 *
 * Description: source file for the Ultrasonic HCSR04 sensor
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 13, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Inclusions                                    *
 *******************************************************************************/

#include"icu.h"
#include"gpio.h"
#include"hcsr04.h"
#include<util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint16 g_time = 0; /* The ICU return 16 bit*/
uint8 g_edges = 0;

/*******************************************************************************
 *                           	Functions                                      *
 *******************************************************************************/

/*
 * Description:
 * 1 - Initialize the ICU driver as required.
 * 2 - Setup the ICU call back function.
 * 3 - Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void ultrasonic_init(void)
{
	/*set the freq and edge of ICU*/
	ICU_ConfigType config={F_CPU_8,RISING_EDGE};

	/*initialize the ICU driver*/
	ICU_init(&config);

	/* set call back function */
	ICU_setCallBack(*ultrasonic_edgeProcessing);

	/* make the trigger pin at PB5 as output*/
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,1);

}
/*
 * Description :
 * 1 - Send the Trigger pulse to the ultrasonic.
 */
void ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,1);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,0);
}
/*
 * Description :
 * 1 - Send the trigger pulse by using Ultrasonic_Trigger function
 * 2 - Start the measurements by the ICU from this moment
 */
uint16 ultrasonic_readDistance(void)
{
	/*clear the edges to look for the next one*/
	g_edges=0;

	/*clear the ICU timer*/
	ICU_clearTimerValue();

	/* send trigger */
	ultrasonic_Trigger();

	/* wait till we recieve counting */
	while(g_edges != 2)
	{

	}

	/*return distance which equals time/58.8*/
	return (g_time / 58);
}
/*
 * Description :
 * 1 - This is the call back function called by the ICU driver
 * 2 - This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void ultrasonic_edgeProcessing(void)
{
	g_edges++;

	/*we detect a rising edge*/
	if(g_edges==1)
	{
		/*clear timer*/
		ICU_clearTimerValue();

		/*look for the falling edge*/
		ICU_setEdgeDetectionType(FALLING_EDGE);
	}

	/*we detect a rising edge*/
	else if(g_edges==2)
	{
		/*get the value*/
		g_time=ICU_getInputCaptureValue();

		/*look for the rising edge for next pulse*/
		ICU_setEdgeDetectionType(RISING_EDGE);

	}
}