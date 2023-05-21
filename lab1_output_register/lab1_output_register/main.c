/*
 * lab1_output_register.c
 *
 * Created: 5/22/2023 2:47:42 AM
 * Author : User
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRB = 0b00100000;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0b00100000;
		_delay_ms(1000);
		PORTB = 0b00000000;
		_delay_ms(1000);
    }
}

