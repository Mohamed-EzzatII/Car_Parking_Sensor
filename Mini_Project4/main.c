#include"hcsr04.h"
#include"lcd.h"
#include<avr/io.h>
#include<util/delay.h>
int main()
{
	uint16 new_distance = 0,old_distance=0;

	/* Enable I-Bit to enable the interrupts */
	SREG |= (1<<7);

	/* Initialize the LCD driver */
	LCD_init();

	/* Initialize the ultrasonic driver */
	ultrasonic_init();

	/* the first displayed item on screen */
	LCD_displayString("Distance = ");
	new_distance = ultrasonic_readDistance();
	LCD_integerToString(999);
	LCD_displayString("cm");

	while(1)
	{
		/*The big delay is to keep up the slow reading*/
		_delay_ms(300);

		/* get the distance read by the ultrasonic sensor */
		new_distance = ultrasonic_readDistance();

		if(new_distance!=old_distance)
		{
			/*display the new reading*/
			LCD_moveCursor(0,10);
			LCD_integerToString(new_distance);
			LCD_displayString("cm  ");

			/*the new reading became old*/
			old_distance=new_distance;
		}
	}
}
