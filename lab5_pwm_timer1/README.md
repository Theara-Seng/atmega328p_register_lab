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
