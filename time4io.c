#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){
	
	
	int jsw;
	jsw =0;
	int ans;
	ans = (PORTD>>8) & 0xf;
   
	 //int jsw;
	int sw;
	sw	= ans &0x1 | ans &0x2 | ans &0x4| ans &0x8;
	/*
	if (sw ==1){
		jsw =1;
	}
	
	if (sw ==2){
		jsw =2;
	}
	
	if (sw ==4){
		jsw =3;
	}
	if (sw ==8){
		jsw =4;
	}
	*/
	return sw;
}

int getbtns(void){
	int jbtn;
	jbtn =0;
	int ans;
	ans = (PORTD>>5) & 0x7;
	int ans1;
	ans1 = (PORTF>>1) & 0x1;
    int btn; 
btn	= ans &0x1 | ans &0x2 | ans &0x4;
	int btn1;
	btn1=ans1&0x1;
	if (btn1 ==1){
		jbtn =1;
	}
	if (btn ==1){
		jbtn =2;
	}
	
	if (btn ==2){
		jbtn =3;
	}
	
	if (btn ==4){
		jbtn =4;
	}

	return jbtn;
	
}