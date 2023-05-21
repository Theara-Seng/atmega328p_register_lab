/*
 * lab2_input_register.c
 *
 * Created: 5/22/2023 3:44:20 AM
 * Author : User
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRB = 0b00100000;
	uint8_t buttonWasPressed = 1;
    while (1) 
    {
		if (bit_is_clear(PINB,PB0)){
			_delay_ms(50);
			if (bit_is_clear(PINB,PB0)){
				if (buttonWasPressed == 0)
				PORTB ^= 0b00100000;
				buttonWasPressed = 1;
			}
		}else{
			buttonWasPressed = 0;
		}
		
    }
}

