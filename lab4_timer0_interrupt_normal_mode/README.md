# Timer 0 Interrupt (Normal Mode)

In this lab, we will use the Timer0 Interrupt to generate a 500 millisecond delay 

The same as polling mode we will use normal mode with prescaler 64, so we can write 

```sh
DDRB = 1<<PB5;
TCCR0A = 0x00; //Normal Mode
TCCR0B = 1<<CS00 | 1<<CS01; // using prescaler 64
TCNT0 = 6; // set 1ms delay
 ```
 
 After that we need to generate a timer interrupt 
 
 ![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_interrupt_normal_mode/lab4_image/TIM.png)
 
 We can write
 
 ```sh
TIMSK0 = 1 << TOIE0; // select timer0 overflow interrupt
sei(); // Enable global Interrupt
  ```
  
 Create a global variable count 
 
 ```sh
 uint16_t count = 0;
 ```
 
  Then in the interrupt service routine 
  ```sh
  ISR(TIMER0_OVF_vect){
	count++;
	TCNT0 =6;
}
```

Then create a function that blink the led of the PORTB Bit 5

```sh
void blink_ms(uint16_t ms){
	if (count == ms){
		PORTB ^= 1<<PB5;
		count=0;
	}
  
  ```
  
  # Code
  
  The whole program can be found below 
  
  ```sh
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



}
``` 
## Result 

 ![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_interrupt_normal_mode/lab4_image/result.png)
