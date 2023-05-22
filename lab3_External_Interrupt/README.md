# External Interrupt 

In this lab, we will be using two push buttons and a LED. 

## Connection and Concept

The push buttons are connect to PD2 and PD3, respectively (Note* External Interrupt cannot use with another pin out of PD2 and PD3) and a LED is connected to PD5

The concept in here is when one button is pressed, it detected the falling down, then the LED is turned ON. Then when another button is pressed or the same button is pressed, 
it will detect the falling edge, the LED will change the state.

## Register Description

First we need to declare the External Interrupt Mask register which is EIMSK as shown in the image below

