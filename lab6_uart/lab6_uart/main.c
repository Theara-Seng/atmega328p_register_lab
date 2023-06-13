/*
 * lab6_uart.c
 *
 * Created: 6/6/2023 9:38:24 AM
 * Author : User
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <math.h>
uint16_t count = 0;
uint16_t n = 0;
void UART_init()
{
	// set baudrate in UBRR
  UBRR0H = 0x00;                       /* defined in setbaud.h */
  UBRR0L = 8;     // UBRR = Fcpu/16*BAUD - 1 = (16000000/16*115200) -1 = 8
	
  UCSR0B = (1 << TXEN0) | (1 << RXEN0); // enable the transmitter and receiver
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
}
void transmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	while ((UCSR0A & (1<<UDRE0))==0);
	//loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;                                            /* send data */
}
void printString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		transmitByte(myString[i]);
		i++;
	}
}
void printByte(uint32_t byte) {
	/* Converts a byte to a string of decimal text, sends it */
	int length = 1+(int)log10(byte);
	switch(length){
		case 1:
			transmitByte('0' + (byte % 10));
			break;
		case 2:
			transmitByte('0' + ((byte / 10) % 10));
			transmitByte('0' + (byte % 10));
			break;
		case 3: 
			transmitByte('0' + (byte / 100) % 10);                      
			transmitByte('0' + ((byte / 10) % 10));
			transmitByte('0' + (byte % 10));
			break;
		case 4:
			transmitByte('0' + (byte/1000)  % 10);
			transmitByte('0' + (byte / 100) % 10);                    
			transmitByte('0' + ((byte / 10) % 10));
			transmitByte('0' + (byte % 10));
			break;
		case 5:
			transmitByte('0' + (byte/10000));
			transmitByte('0' + (byte/1000)  % 10);
			transmitByte('0' + (byte / 100) % 10);                   
			transmitByte('0' + ((byte / 10) % 10));
			transmitByte('0' + (byte % 10));
			break;
		case 6: 
			transmitByte('0' + (byte/100000));
			transmitByte('0' + (byte/10000) % 10);
			transmitByte('0' + (byte/1000)  % 10);
			transmitByte('0' + (byte / 100) % 10);                   
			transmitByte('0' + ((byte / 10) % 10));
			transmitByte('0' + (byte % 10));
			break;
			
	}
	
}
int main(void)
{
    /* Replace with your application code */
//	DDRD =0xFF;
	UART_init();
    while (1) 
    {
		uint32_t x = 240;
		//printString("hello world\n");
		printByte(x);
		printString("\n");
    }
}

