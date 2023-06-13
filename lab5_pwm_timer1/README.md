# Timer 1 Fast PWM (Inverting Mode and Non Inverting Mode)

In the lab, we will use timer 1 to generate a PWM signal with FAST PWM (8 bit, 9 bit and 10 bit) using Inverting Mode and Non-Inverting Mode

## FAST PWM 8 BIT

In FAST PWM 8 bit mode, there are two different kind of mode (Inverting mode and none inverting mode), so first we need to select one of them by choosing TCCR1A as shown 
in the register below
![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/TCCR1A.png)

By choosing the bit COM1A1/COM1B1 and COM1A0/COM1B0, we can choose the non-inverting mode and inverting mode

### Non-Inverting Mode Selection

To select the non inverting mode, we need to set COM1A1/COM1B1 to 1  and COM1A0/COM1B0 to 0

![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/fast_pwm.png)
We can write 

```sh
TCCR1A = (1<<COM1A1)
```

However by choosing the 8 bit FAST PWM, we need to set **WGM10=1** and **WGM12=1**, and WGM10 is in register TCCR1A, so we can write 

![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/8_bit.png)

```sh
TCCR1A = (1<<COM1A1) | (1<<WGM10);
```

And then we need to choose prescaler clock by working on register TCCR1B


![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/TCCR1B.png)

We see that in TCCR1B, there is a WGM12 in bit 4 to set the fast pwm 8 bit, so we need set them in TCCR1B too. and for bit 2 to bit 0 is the prescaler selection,

![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/clock_selection.png)

In this testing, I use the  prescaler 8, so I need to set CS11 to 1,

Then I can write:

```sh
TCCR1B = 1 << CS11 | 1<<WGM12;  // prescaler 8 and fast pwm
```

For the fast pwm8 bit, the frequency is defined by


$$ Frequency = \dfrac{F_{cpu}}{2^{8}\times{N}} \quad , \textnormal{N is the prescaler selection} $$ 

By the $F_{cpu}= 16000000$ and $N=8$, we get:

$$Frequency = \dfrac{16000000}{256\times8} = 7812.5HZ$$

For the duty cycle we need to select the OCR1A/OCR1B or ICR1 as shown in the image below


![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/OCR1A.png)

The formula is define by

$$ OCR1A = \dfrac{2^{8}\times {D}}{100} - 1 \quad, \textnormal{D is the duty cycle} $$ 

So if want to selection the duty cycle of 50% we get

$$ OCR1A = \dfrac{256\times 50}{100} - 1  = 127 $$

By choosing OCR1A we get the Duty cycle of 50% in the pin 9 of the atmega328p or PB1

## Inverting Mode Selection 

For the inverting mode, we need to set both COM1A1/COM1B1 and COM1A0/COM1B0 to 1 


![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/fast_pwm.png)

Then we need to write 

```sh
TCCR1A = (1<<COM1B1) | (1<<COM1B0) | 1 << WGM10); // Inverting mode with fast pwm 8 bit
```

and for the TCCR1B is the same since we use the fast pwm 8 bit and prescaler 8

```sh
TCCR1B = 1 << CS11 | 1<<WGM12;  // prescaler 8 and fast pwm
```

The frequency is the same as the Non-inverting mode

$$ Frequency = \dfrac{F_{cpu}}{2^{8}\times{N}} \quad , \textnormal{N is the prescaler selection} $$ 

But for the duty cycle the formula is different, the formula is below 

$$ OCR1A/OCR1B = (2^{8}-1) - \dfrac{2^{8}\times D}{100}  $$

## Fast PWM 9 BIT 

For the fast pwm 9 bit, all of the concept is the same as 8-bit fast pwm, the only different is only change from 2^{8} to 2^{9} and the top value is 0x01FF 


![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/9_bit.png)


As shown in the image above to select the 9 bit fast pwm and non inverting mode, we need to select

```sh 
TCCR1A = 1<<WGM11 | 1<<COM1A1 ; // fast pwm 9 bit and non inverting mode
```

Then in the TCCR1B, we use the same prescaler 8 as fast pwm 8 bit

```sh
TCCR1B = 1<<WGM12 | 1<<CS11;
```

The the frequency is define by 

$$ Frequency = \dfrac{F_{cpu}}{2^{9}\times N} = \dfrac{16000000}{512\times 8} =  3906.25HZ $$

And the duty cycle is (Non-inverting mode)

$$ OCR1A = \dfrac{2^{9}\times D}{100} - 1 $$

Invering Mode 

$$ OCR1A = (2^{9} - 1) - \dfrac{2^{9}\times D}{100} $$

## Fast PWM 10 BIT 

For the fast PWM 10 bit, we need to select the TCCR1A register 


![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/10_bit.png)

```sh
TCCR1A = (1<<WGM10) | (1<<WGM11) | (1<<COM1A1); //fast pwm 10 bit and non-inverting mode
```

Then for the TCCR1B 

```sh
TCCR1B = (1<<WGM12) | (1<<CS10); // fast pwm 10 bit and prescaler 1
```

The frequency is defined by 

$$ Frequency = \dfrac{F_{cpu}}{2^{10}\times N} = \dfrac{16000000}{1024\times 1} =  15625HZ $$

And the duty cycle for the non-inverting mode is 

$$ OCR1A = \dfrac{2^{10}\times D}{100} - 1 $$

The inverting mode duty cycle 

$$ OCR1A = (2^{10} - 1) - \dfrac{2^{10}\times D}{100} $$

## Code

The whole code can be found below 

```sh
/*
 * lab5_pwm_timer1.cpp
 *
 * Created: 5/22/2023 8:50:10 AM
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void pwm_8bit_nm(uint8_t duty1 );
void pwm_8bit_im(uint8_t duty);
void pwm_9bit_nm(uint16_t duty);
void pwm_9bit_im(uint16_t duty);
void pwm_10bit_nm(uint32_t duty1, uint32_t duty2);
void pwm_10bit_im(uint32_t duty);

int main(void)
{
    /* Replace with your application code */
	
	DDRB |= 1<<PB1 | 1<< PB2;
    while (1) 
    {
		//pwm_10bit_im(30);
		pwm_10bit_nm(50, 30);  // PB1 = 50% and PB2 = 30%
    }
}

 void pwm_8bit_nm(uint8_t duty){
	//Non Inverting Mode
	// Frequency = F_cpu/ 256*N = 16*10^6/ 256*8 = 7812.5 Hz
	// duty cycle: OCR1A = 256D/100 - 1 => D = (OCR1A+1)*100/256;
	OCR1A = ((256*duty)/100) - 1;
	TCCR1A = (1<<COM1A1) | 1<<WGM10; // Non-inverting Mode and Fast PWM 8-BIT
	TCCR1B = (1<<WGM12) | 1<<CS11; // Prescaler 8
	
}
void pwm_8bit_im(uint8_t duty){
	// Inverting Mode
	// Frequency = F_cpu/ 256*N = 16*10^6/ 256*8 = 7812.5 Hz
	// OCR1B = 255 - 256*D/100;
	OCR1B = 255 - ((256*duty)/100);
	TCCR1A = (1<<COM1B1)| (1<<COM1B0) | 1<<WGM10; // inverting Mode and Fast PWM 8-BIT
	TCCR1B = (1<<WGM12) | 1<<CS11; // Prescaler 8
}
void pwm_9bit_nm(uint16_t duty){
	//Non Inverting Mode
	// Frequency = F_cpu/ 512*N = 16*10^6/ 512*8 = 3906.25 Hz
	// duty cycle: OCR1A = 512D/100 - 1 => D = (OCR1A+1)*100/256;
	OCR1A = ((512*duty)/100)-1;
	TCCR1A = (1<<COM1A1) | 1<<WGM11; // Non-inverting Mode and Fast PWM 9-BIT
	TCCR1B = (1<<WGM12) | 1<<CS11; // Prescaler 8
}
void pwm_9bit_im(uint16_t duty){
	// Inverting Mode
	// Frequency = F_cpu/ 512*N = 16*10^6/ 512*8 = 3906.25Hz
	// OCR1B = 511 - 512*D/100;
	OCR1B = 511 - ((512*duty)/100);
	TCCR1A = (1<<COM1B1)| (1<<COM1B0) | 1<<WGM11; // inverting Mode and Fast PWM 9-BIT
	TCCR1B = (1<<WGM12) | 1<<CS11; // Prescaler 8
}
void pwm_10bit_im(uint32_t duty){
	// Inverting Mode
	// Frequency = F_cpu/ 1024*N = 16*10^6/ 1024*1 = 15625Hz
	// OCR1B = 1023 - 1024*D/100;
	OCR1B = 1023 - ((1024*duty)/100);
	TCCR1A = (1<<COM1B1)| (1<<COM1B0) | (1<<WGM10) | 1<<WGM11; // Inverting Mode and Fast PWM 10-BIT
	TCCR1B = (1<<WGM12) | 1<<CS10; // Prescaler 1
}
void pwm_10bit_nm(uint32_t duty1, uint32_t duty2 ){
	//Non Inverting Mode
	// Frequency = F_cpu/ 1024 = 16*10^6/ 1024 = 15625 HZ
	// duty cycle: OCR1A = 1024D/100 - 1 => D = (OCR1A+1)*100/256;
	OCR1A = ((1024*duty1)/100)-1;
	OCR1B = ((1024*duty2)/100)-1;
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10) | (1<<WGM11); // Non-inverting Mode and Fast PWM 10-BIT
	TCCR1B = (1<<WGM12) | 1<<CS10; // Prescaler 1
}
```

## RESULT 

The result is shown in the image below 

![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/result.png)
