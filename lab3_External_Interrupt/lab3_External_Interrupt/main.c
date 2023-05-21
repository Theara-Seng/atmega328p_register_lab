/*
 * lab3_External_Interrupt.c
 *
 * Created: 5/22/2023 4:23:08 AM
 * Author : User
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect){
	_delay_ms(50);
	if (bit_is_clear(PIND,PD2)){
		PORTD ^= 1<<PD5;
	}
}

ISR(INT1_vect){
	_delay_ms(50);
	if (bit_is_clear(PIND,PD3)){
		PORTD ^= 1<<PD5;
	}
}

int main(void)
{
	/* Replace with your application code */
	DDRD = 0b00110000;
	EIMSK = 1<<INT0 | 1<<INT1; //Enable interrupt 0 and 1
	EICRA = 1<<ISC01 | 1<<ISC11 ; // Detect falling edge for both INT0 and INT1
	sei(); //enable global interrupt
	while (1)
	{
	
	}
}
