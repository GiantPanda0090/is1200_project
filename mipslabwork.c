/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int prime = 1234567;

int mytime = 0x5957;

int pretime;
int *p;
int j =0;
int flag =0;
int counter =0;
int flagsw;
char textstring[] = "text, more text, and even more text!";
int index;
	
/* Interrupt Service Routine */
void user_isr( void ) {
	/*
	flag =IFS(0) & 0x100;
	 flag = flag >> 8;
	 */
 
 
	if ( IFS(0) & 0x100){
		counter=counter+1;
		  IFS(0)&=0xFF;
	 }
	 
	  if (counter ==10){
		 counter =0;
		PORTE=0x0;
 time2string( textstring, mytime );
 display_string( 1, textstring );
 display_update();
 tick( &mytime );

  }
	 /*
	 if (IFS(0) & 0x80){
	 

	IFS(0)&=0x7f;	
 }
 */
	
 
 //IFS(0)&=0x7f;
 
 
 
  
 /*
 else {
	 IFS(0)&=0x7f;
 */
 /*
 flagsw =IFS(0) & 0x80;
	 flagsw = flagsw >> 7;
 */
 
 
 
 /*
 if (IFS(0) & 0x80){
	 IFS(0)&=0x7f;
	 p =&mytime;
  pretime =*p;
  
  tick( &mytime );
  
  if (pretime = *p){
	  j=1;
	  PORTE = PORTE + 1;
  }
 }
 */
  return;
}

/* Lab-specific initialization goes here */
volatile int* porte;
volatile int* trise; 


void labinit( void )
{
	
	 porte = (volatile int*)0xbf886110;
	trise = (volatile int*)0xbf886100;
	*trise &= ~0xff; 
	T2CON = 0x0070; // Stop timer and clear control register,
// set prescaler at 1:32, internal clock source
TMR2 = 0x0; // Clear timer register
PR2 = 0x7a12; // Load period register
  IFS(0)&=0xFF;
   //INTCONbits.MVEC = 1;
   IPC(2)=0000;
   IPC(2)|=  0x7 << 2 | 0x3;
   IEC(0)=0000;
   IEC(0)|=0X100;
     enable_interrupt();
T2CONSET = 0x8000;

IPC(1)=0x1F000000;

PORTE =0x0000;

//pin 6 in J6-13 50 OC3/RD2

//TRISD|=0x2; //motion sensor set as input

	//portd
	TRISD |= 0x7f4; //7f0|2 motion activated
TRISF |= 0x2;
  return ;
}


/* This function is called repetitively from the main program */
void labwork( void ) {
	int swnr;
		swnr= getsw();	
		swnr &= 0x1;
if (swnr==0x1){
	alarm_on();
}
else {
	alarm_off();
}
int jbtn;
jbtn = auth_on();
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
display_string( 0, "Welcome home!" );
// debug
 time2string( textstring, jbtn );
  display_string( 2, textstring );
display_update();
 return;
}

  


