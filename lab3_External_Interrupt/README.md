# External Interrupt 

In this lab, we will be using two push buttons and a LED. 

## Connection and Concept

The push buttons are connect to PD2 and PD3, respectively (Note* External Interrupt cannot use with another pin out of PD2 and PD3) and a LED is connected to PD5

The concept in here is when one button is pressed, it detected the falling down, then the LED is turned ON. Then when another button is pressed or the same button is pressed, 
it will detect the falling edge, the LED will change the state.

## Register Description

First we need to declare the External Interrupt Mask register which is EIMSK as shown in the image below

![EIMSK](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab3_External_Interrupt/lab3_image/EIMSK.png)


Since we use both External interrupt we need to declare both of them

```sh
EIMSK = 1<<INT0 | 1<<INT1; //Enable interrupt 0 and 1
```

Then we can use the EICRA register to sense control. 

![EIMSK](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab3_External_Interrupt/lab3_image/EICRA.png)

So we need to detect the Falling edge of the push button when it is pressed

```sh
EICRA = 1<<ISC01 | 1<<ISC11 ; // Detect falling edge for both INT0 and INT1
```

Then enable the global interrupt

```sh
sei();
```

Interrupt Service Routine 

```sh
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
```

In the code above, when the it detecting the falling edge, then delay for 50 millisecond, after that is still LOW, the led with change the state.


## Code 

The whole code can be found below

```sh
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
```

## Result 

![EIMSK](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab3_External_Interrupt/lab3_image/result.png)
