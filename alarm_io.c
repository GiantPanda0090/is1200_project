#include <stdint.h>
#include<stdio.h>
#include <pic32mx.h>

#include "mipslab.h" 

int ans;
int ix=0x0;
int pass =0x0000;
int mask =0xffff;
int org=0x0000;
int out=0x0000;
int auth=0;

void pass_in(void){
	int btn;
	btn =getbtns();
	
	int swnr;
	swnr =getsw();
	swnr &= 0x8;
	
	
	if(ix >12){
		ix =0;
		
	}
	if (btn !=0){
		btn =btn <<ix;
	  pass =pass | btn;
	  print_pass();
	  if(swnr ==8){
	  out= out| btn;
	  }
	  ix=ix+4;
	}
	
	return ;
}
void alarm_off(void){
	ans =0;
	display_string(3, "System clear");
	return;
}

void alarm_on( void ) {

	ans=(PORTD>>2) & 0x1;
		
	if (ans==0){
	 display_string( 3, "System Armed" );
	} 
	
	  if (ans ==1){
	PORTE=0xff;
display_string( 3, "Motion detected" );
}
display_update();



return;


}



 
int print_pass(){
	return pass;
}

void pass_gen(void){
	
	int swnr;
	swnr =getsw();
	swnr &= 0x8;
	 if(swnr ==8){ 
		 display_string(3, "PASSWORD RESET MODE ON!");
		 pass_in();
		 org =out;
	
	     if (ix >12 ){
			  pass &=0x0000;
			  ix =0;
			  if (org ==out){
		  display_string(3, "Password Set!");
	 }
	 else{
		  display_string(3, "PASSWORD NOT SET!!");
		  
	 }
	 display_update();
		  quicksleep(1500);
		  return;
	 }
	
	 }
	 
	if (swnr !=8){
		 out&=0x0000;
	}
	return;
}




void clear(void){
int swnr;
	//clear 
swnr =getsw();
swnr &= 0x4;
if (swnr ==4){
	pass &=0x0000;
	ix =0;
	out&=0x0000;
	display_string( 3, "Password Cleared!!" );
}
return;
}

int auth_on(){
	int swnr;
	swnr =getsw();
	swnr &= 0x2;
	
	
if (swnr ==2){
	display_string( 3, "ADMINISTRATOR LOGIN" );
	 pass_in();
	if (swnr ==2){
		 if (ix >12 ){
			  ix =0;
		if (pass==org){
	display_string( 3, "PASSWORD CORRECT" );
	
	auth =1;
}
else{
	display_string (3,"PASSWORD WRONG!!");
		auth =0;
	
}
pass &=0x0000;
	}
	}	
	
display_update();
 
return auth;
}
}


