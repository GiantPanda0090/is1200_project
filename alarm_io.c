#include <stdint.h>
#include<stdio.h>
#include <pic32mx.h>

#include "mipslab.h" 

int ans;
int ix=0x0;
int pass =0x0000;
int mask =0xffff;
int org=0x01234;
int out=0x0000;
int auth=0;
int swnr;

void pass_in(void){
	int btn;
	btn =getbtns();
	
	
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
	quicksleep(1500);
	


return;


}



 
int print_pass(){
	return pass;
}

void pass_gen(void){
	
	
	swnr =getsw();
	swnr &= 0x8;
	 if(swnr ==8){ 
		 display_string(3, "PASSWORD RESET MODE ON!");
		 display_update();
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

	//clear 
swnr =getsw();
swnr &= 0x4;
if (swnr ==4){
	pass &=0x0000;
	ix =0;
	out&=0x0000;
	display_string( 3, "Password Cleared!!" );
	display_update();
	quicksleep(1500);
	
}

return;
}

int auth_on(){
	
	swnr= getsw();	
    swnr &= 0x1;
	
	if (swnr==0x1){
	alarm_on();
}

if (swnr ==0x0){
	display_string( 3, "ADMINISTRATOR LOGIN" );
	display_update();
	 pass_in();
	
		 if (ix >12 ){
			  ix =0;
		if (pass==org){
	display_string( 3, "PASSWORD CORRECT" );
	display_update();
	quicksleep(1500);
	
	alarm_off();
	auth =1;
}
else{
	display_string (3,"PASSWORD WRONG!!");
	display_update();
	quicksleep(1500);
	
		auth =0;
	alarm_on();
}
pass &=0x0000;
	}
		

 

}

return auth;
}


