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