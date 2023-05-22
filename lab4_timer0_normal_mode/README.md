# Timer 0 (NORMAL MODE)

In this lab, we will use the timer0 to generate a delay for one second using the NORMAL Mode of the atmega328p 

## TCCR0A

First we need to select the mode which we want to use with our lab. 

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/TCCR0A.png)

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/normal_mode.png)
Since we gonna use the normal mode, so we can write 

```sh
TCCR0A = 0x00; // normal mode selection
```

## TCCR0B

To generate a one second delay, we can check the formala below 

$$ TCNT0 = 256 - \dfrac{F_{clock}\times T_{delay}}{N_{prescaler}}$$

so if want to generate a one second delay we cannot use without prescaler or smaller prescaler, for example if we use prescaler 8:

$$ TCNT0 = 256- \dfrac{16\times 10^{6} \times 10^{-3}}{8} = 256-2000 = negative$$

As you see above, we cannot use smaller prescaler, in this case we can use 64 prescaler

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/TCCR0B.png)

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/prescaler.png)

We can write 

```sh
TCCR0B = 1<<CS00 | 1<<CS01; // prescaler 64
```

## TCNT0

After find the prescler, we need to find the TCNT0 which is the counter that is count until the overflow 
![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/TCNT0.png)

$$ TCNT0 = 256 - \dfrac{F_{clock}\times T_{delay}}{N_{prescaler}}$$


$$ TCNT0 = 256- \dfrac{16\times 10^{6} \times 10^{-3}}{64} = 256-250 = 6$$

So, we can write 

```sh
TCNT0 = 6; 
```

## TIFR0 

The counter is count until the overflow flag is set.

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/TIFR0.png)

So we need to write a clear the flag by 

```sh
	while ((TIFR0 & (1<<TOV0)) == 0);
	TIFR0 = 0x01;
  ```
  
  ## Code 
  
  The whole code can be found below 
  
  ```sh
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
```

## Result 

![TCCR0A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab4_timer0_normal_mode/lab4_image/result.png)
