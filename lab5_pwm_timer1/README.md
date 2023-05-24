# Timer 1 Fast PWM (Inverting Mode and Non Inverting Mode)

In the lab, we will use timer 1 to generate a PWM signal with FAST PWM (8 bit, 9 bit and 10 bit) using Inverting Mode and Non-Inverting Mode

## FAST PWM 8 BIT

In FAST PWM 8 bit mode, there are two different kind of mode (Inverting mode and none inverting mode), so first we need to select one of them by choosing TCCR1A as shown 
in the register below
![TTCR1A](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab5_pwm_timer1/lab5_image/TCCR1A.png)

By choosing the bit COM1A1/COM1B1 and COM1A0/COM1B0, we can choose the non-inverting mode and inverting mode

### Non-Inverting Mode Selection

We can write 

```sh
TCCR1A = (1<<COM1A1)
```

