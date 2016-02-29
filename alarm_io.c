#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int ans;
int index=0x0;
int pass =0x0000;
int mask =0xffff;
int org=0x0000;
int out=0x0000;
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

void pass_gen(void){
	
	int swnr;
	swnr =getsw();
	swnr &= 0x8;
	 if(swnr ==8){ 
		 display_string(3, "PASSWORD RESET MODE ON!");
		 org =out;
	
	     if (index >12 ){
			  pass &=0x0000;
			  index =0;
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
	
}

void pass_in(void){
	int btn;
	btn =getbtns();
	
	int swnr;
	swnr =getsw();
	swnr &= 0x8;
	
	
	if(index >12){
		index =0;
		
	}
	
	if (btn !=0){
		btn =btn <<index;
	  pass =pass | btn;
	  if(swnr ==8){
	  out= out| btn;
	  }
	  index=index+4;
	}
	return ;
}



int auth_on(){
	int swnr;
	pass_gen();
	 pass_in();

  
   
	swnr =getsw();
	swnr &= 0x2;
	
if (swnr ==2){
	display_string( 3, "ADMINISTRATOR LOGIN" );
	
	if(index >12){
		index =0;
		
		if (pass==org){
	display_string( 3, "PASSWORD CORRECT" );
	
}
else{
	display_string (3,"PASSWORD WRONG!!");
		
	while(1){
	alarm_on();
	}
}
pass &=0x0000;
	}
	

}




swnr =getsw();
swnr &= 0x4;
if (swnr ==4){
	pass &=0x0000;
	index =0;
	out&=0x0000;
	display_string( 3, "Password Cleared!!" );
	
}
display_update();
return pass;
}


