# Input Register 

In this lab, we will understand some basic concept of the input register with atmega328P

We will do two thing

1. Press the push button the led is on, release the led is off
2. Press the push button the led is on, release the led is still on, until one more press the led is off

## Connection 

* Push button is using pull up resistance with 10K and connect to PORTB bit 0
* LED is connect to PORTB bit 5

# Register Description

![INPUT_REGISTER](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab2_input_register/lab2_image/PINB.png)

As shown in the image above, the PINB is the input register and all the pins are pull up, so it means that all of the input pins are HIGH.


So we need to write a code that when the button is low, the led is ON

First we need to declare the input and output pin 

```sh
DDRD = 0b00100000; // BIT 5 is OUTPUT and another bit is INPUT 
```

Then we can write 

```sh
if (!(PINB & 0b00000001)){
  PORTB = 0b00100000;
 }else{
  PORTB = 0b00000000;
  }
 ```

It mean that: 

PINB = 0b11111111; all are pull up

```sh
 0b11111111
&0b00000001
=0b00000001;
```
Then 
```sh
!0b00000001= 0b11111110;
```

so it mean that when the PB0 is low the PB5 of PORTB high

We can write a different way using the function bit_is_clear(PINx, Pxn)

```sh
if (bit_is_clear(PINB,PB0){
  PORTB = 0b00100000;
 }else{
  PORTB = 0b00000000;
  }
 ```
 
 ## Result 
 
 
![INPUT_REGISTER](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab2_input_register/lab2_image/result.png)


## Debouncing and State Change

In this debouncing and state change concept, it mean that the button has always been a debouncing or noise in the mechanical part that when we press the button it can be high or 
low for sometime, so we will use a delay for 50ms and check the state again if it still low, then the led is on even if we release the button until one more pressed, the led is turn off

The whole code is below:

```sh
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

```

## Result 

![INPUT_REGISTER](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab2_input_register/lab2_image/result1.png)
