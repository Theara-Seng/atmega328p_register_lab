# USART (Universal Synchronous and Asynchronous Receiver and Transmitter)

This lab we will learn how to communicate between the computer and atmegega328p using USART communication based on the Microchip Studio

## Define Baudrate 

So first we need to define the Baudrate that we want to communicate between the computer and the Atmega328p

![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/baudrate.png)

As shown in the image above, in order to communicate between the computer and the atmega328p, we need to define the baudrate which is the kind of speed which transfer the data

So, in this lab, we will use the baudrate of 115200, so by the formula above, we can see that

$$UBBRn = \dfrac{f_{osc}}{16BAUD} - 1 = \dfrac{16\times 10^{6}}{16\times 115200} - 1 = 8$$

So, we can define the UBBRn by 

```sh
// set baudrate in UBRR
  UBRR0H = 0x00;                       /
  UBRR0L = 8;     // UBRR = Fcpu/16*BAUD - 1 = (16000000/16*115200) -1 = 8
  ```
  
## Enable the Tx (Transmit) and Rx (Receive)

Then we need to enable the tranmitter and receiver as shown in the image below 


![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/USART0B.png)

We see that we need to enable the bit 3 and 4 of the USART0B by setting 

```sh
UCSR0B = (1 << TXEN0) | (1 << RXEN0); // enable the transmitter and receiver
```

## Define the DataFrame and the stop bit 

There different type of the transmit or receive, and also the stop bit 

![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/frame_format.png)

But in the scenario, we use the 8-bit dataframe and 1 stop bit, so we need to set the register USART0C

![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/USART0C.png)

![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/bit8.png)

Seeing that in order to set the dataframe 8bit and one stop bit, we need to set UCSZ0[2:0] to 011, it means that UCSZ01 = 1 and UCSZ00 = 1;

The code can be written by 

```sh 
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
```

# Transmit the data 

In order to transmit the data we need to wait for the old data to send it all, by releasing we need to wait for the buffer to be cleard. 

The register for the buffer to be clear is the USART0A and the UDRE0 as shown in the image below 


![BAUDRATE](https://github.com/Theara-Seng/atmega328p_register_lab/blob/main/lab6_uart/image/USART0A.png)

As detail above, we need to wait for the bit UDRE0 = 1 then the data can be transmit using USR0 = data 


```sh
void transmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	while ((UCSR0A & (1<<UDRE0))==0);
	//loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;                                            /* send data */
}
```

