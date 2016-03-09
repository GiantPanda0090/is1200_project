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
// char str[80];
 /*
void uart_init(void){
	U1STA=0x1400;
	U1BRG =519; //9600
	U1MODE=0x8000;
	return;
}
*/
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
int lognr=0; // log number
// transmmit char
void putcharserial(char c) {
	
	while (U1STA&0x200);//transmit buffer status
	U1TXREG = c;
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
// loop put char and make transmitte string
void putstrserial(char *str) {
	 int i;
	 i= 0;
	
	 while (str[i] != 0) { // iterate over string

 putcharserial(str[i++]); // send each character

 }
// str[i++]='\n';
 //str[i++]='\r';
	return; 
}
/*
char getcharserial(void) {

 while (!U2STAbits.URXDA); // wait until data available

 return U2RXREG; // return character received from

 // serial port

}
*/
// receive void (with bug!!!!!!!!)
char getcharserial(void) {
	
 while (!U1STA&0x1); // wait until data available

 return U1RXREG; // return character received from

 // serial port

}

/*
void getstrserial(char *str) {

 int i = 0;

 do { // read an entire string until detecting

 str[i] = getcharserial(); // carriage return

 } while (str[i++] != '\r'); // look for carriage return

 str[i−1] = 0; // null-terminate the string

}
*/
//receive (with bug!!!!!!!!!!1)
void getstrserial(char *str) {

 int i = 0;

 do { // read an entire string until detecting

 str[i] = getcharserial(); // carriage return

 } while (str[i++] != '\r'); // look for carriage return

str[i++] =0; // null-terminate the string

return;
}

char *compare;
char *stor;
//log start
void log(char *str){
	// make sure no double log and filt unnessasary log
     if(compare ==str||stor ==str){
		 return;
	 }
	//[LOG lognr]
	lognr++;
	 putstrserial("[LOG");
	  putstrserial(itoaconv(lognr));
	  putstrserial("]");
	  //space
	  putcharserial(' ');
	  //log message
 putstrserial(str);
putcharserial('\n');
   putcharserial('\r');
 //getstrserial(str);
 /*
 display_string( 0, str );
 display_update();
 */
 //save previous info and compare later
 stor =compare;
	compare =str;
 //printf("\n\rYou typed: %s\n\r", str);
 return;
}
















/*
char print(){
	return *str;
}
*/
/*
void sw_uart(void){
	int swnr;
	swnr= getsw();	
    swnr &= 0x1;
	if(swnr ==0x1){
	uart_init();
	
	}
	return;
}

*/