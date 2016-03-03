#include <stdint.h>
#include<stdio.h>
#include <pic32mx.h>

#include "mipslab.h" 
//harison harris chapter 8 
//Example 8.20 Serial Communication with a PC
//init
/*
#include <stdio.h>

void inituart(void) {

 U1STAbits.UTXEN = 1; // enable transmit pin

 U1STAbits.URXEN = 1; // enable receive pin

 U1BRG = 10; // set baud rate to 115.2k

 U1MODEbits.ON = 1; // enable UART

}
*/
//U1STAbits.UTXEN = bit10
//U1STAbits.URXEN = bit12
//U1BRG=9960
// U1MODEbits.ON =bit15
 char str[80];
 
void uart_init(void){
	U1STA=0x1400;
	U1BRG =9960;
	U1MODE=0x8000;
	return;
}
//harison harris chapter 8 
//Example 8.20 Serial Communication with a PC
//write
/*
void putcharserial(char c) {

 while (U2STAbits.UTXBF); // wait until transmit buffer empty

 U2TXREG = c; // transmit character over serial port

}
*/
//U2STAbits.UTXBF= U2STA BIT9 0X200

void putcharserial(char c) {
	while (U2STA&=0X200);
	U2TXREG = c;
	return;
}


/*
void putstrserial(char *str) {

 int i = 0;

 while (str[i] != 0) { // iterate over string

 putcharserial(str[i++]); // send each character

 }

}
*/

void putstrserial(char *str) {
	 int i = 0;
	 while (str[i] != 0) { // iterate over string

 putcharserial(str[i++]); // send each character

 }
	return; 
}
void uart_on(void){
	uart_init();
	 while(1) {

 putstrserial("Please type something: ");

 //getstrserial(str);

 printf("\n\rYou typed: %s\n\r", str);

 }
}
