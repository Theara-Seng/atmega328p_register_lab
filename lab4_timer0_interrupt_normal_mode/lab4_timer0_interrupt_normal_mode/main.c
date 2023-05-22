/*
 * lab4_timer0_interrupt_normal_mode.c
 *
 * Created: 5/22/2023 7:36:43 AM
 * Author : User
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
uint16_t count = 0;
void blink_ms(uint16_t ms);
int main(void)
{
    /* Replace with your application code */
	DDRB  = 1<<PB5;
	TCCR0A = 0x00; // normal Mode
	TCCR0B = 1<<CS01 | 1<<CS00; // prescaler 64
	TCNT0 = 6; // 1 ms delay 
	TIMSK0 = 1 << TOIE0; // Enable timer0 interrupt
	sei(); //enable global interrupt
	
    while (1) 
    {
		blink_ms(500);	
    }
}

ISR(TIMER0_OVF_vect){
	count++;
	TCNT0 =6;
}
void blink_ms(uint16_t ms){
	if (count == ms){
		PORTB ^= 1<<PB5;
		count=0;
	}

}

