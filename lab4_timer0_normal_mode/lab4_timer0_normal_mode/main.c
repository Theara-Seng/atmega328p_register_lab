/*
 * lab4_timer0_normal_mode.c
 *
 * Created: 5/22/2023 6:18:44 AM
 * Author : User
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void delay_1ms();
void delay_1s();

int main(void)
{
    /* Replace with your application code */
	DDRB = 1<<PB5;
    while (1) 
    {
		PORTB ^= 1<<PB5;
		delay_1s();
		
    }
}

void delay_1ms(){
	TCCR0A = 0x00;
	TCCR0B = 1<<CS00 | 1<< CS01;
	// Generate a 1 delay 
	// delay = 256 - (16*10^6 * 10^-3)/64 = 256 - 250
	TCNT0 = 6;
	
	while ((TIFR0 & (1<<TOV0)) == 0);
	TIFR0 = 0x01;
}

void delay_1s(){
	for (int i=1; i<=1000;i++){
		delay_1ms();
	}
}