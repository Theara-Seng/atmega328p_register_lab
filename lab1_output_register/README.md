# OUTPUT Register of ATMEGA328P

In this lab, we will understand the basic of the register of atmega328 for blinking the led and we also understand some basic of the bit twiddling for more general purpose in the next lab

## Arduino Board Output PORT and Pin

![Atmega328p](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab1_output_register/lab1_image/pin.png)

we will blink the led of the PORTB and bit 5 that is the pin 13 of the arduino UNO as shown in image below



## Register Description

So we need to declare the PORTB bit 5 as the output in order to control the state of the led. 

![Atmega328p](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab1_output_register/lab1_image/register_output.png)

To declare the PORTB bit 5 as the output, we need the register DDRD 

We can write:

```sh
DDRD = 0b00100000; // bit 5 is equal to 1, that is the output
```

Then in order to control the state to high or low, we need the PORTB Register, 1 is High and 0 is Low

we can write 

```sh
PORTB = 0b00100000;
```

## Clock 

So in order to blink the led of the atmega328p PORTB bit 5, we need a delay. To do that we need a delay function which need to define the clock of the atmega328P

#define F_CPU 16000000UL // clock of the atmega328p is 16MHz
#include <util/delay.h> // include delay library


Then in the main code, we can write 
```sh
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
```

## Bit Twiddling 

We need to understand some bit twiddling for a better performance 

### Bitwise OR(|)

In the code we can write:

```sh
DDRD |= 0b00100000;
```

which mean that 

```sh
 0b00000000
|0b00100000
=0b00100000;
``` 

Using this OR(|) a bitwise OR returns 1 if either bit in the comparition is 1 or 0, it will return 1.

### Bitwise XOR(^)

To blink the led we can just use the Bitwise XOR(^)

```sh
PORTB ^= 0b00100000;
_delay_ms(1000);
```

XOR Gate 1^1 = 0 and 1^0 = 1

so in the first loop 

```sh
 0b00000000
^0b00100000
=0b00100000
```
So the led will turn on for 1 second

Then in the second loop

```sh
 0b00100000
^0b00100000
=0b00000000
```
So the led will turn off for one second also 

### Bitwise AND(&)
 
1 & 0 = 0 and 1 & 1 = 1

### Bitwise NOT(~)

```sh
~00100000
=11011111
```

so we can combine the AND(&) and (~) to clear the bit by 

```sh
PORTB |= 0b00100000; // BIT 5 is on 
_delay_ms(1000); // delay 1000 millisecond
PORTB &= ~0b00100000; // BIT 5 is off because-> ~0b00100000= 0b11011111. Then 0b00100000 & 0b11011111 = 0b00000000 
_delay_ms(1000); // delay 1000 millisecond
```
