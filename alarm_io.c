#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int ans;
int index=0x0;
int pass =0x0000;
int mask =0xffff;
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

void alarm_off(void){
	ans =0;
	display_string(3, "System clear");
	return;
}

int auth_on(){
	
	int btn;
	btn =getbtns();
	if(index >12){
		index =0;
	}
	if (btn !=0){
		btn =btn <<index;
	  pass =pass | btn;
	  index=index+4;
	}
	
	int org;
	org =0x4321;
	int swnr;
	swnr =getsw();
	
	swnr &= 0x2;
if (swnr ==2){
if (pass==org){
	display_string( 3, "PASSWORD CORRECT" );
}
else{
	display_string (3,"PASSWORD WRONG!!");
}
}

display_update();
swnr =getsw();
swnr &= 0x4;
if (swnr ==4){
	pass &=0x0000;
	display_string( 3, "Password Cleared!!" );
	display_update();
}
return pass;
}


