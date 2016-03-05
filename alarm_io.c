#include <stdint.h>
#include<stdio.h>
#include <pic32mx.h>

#include "mipslab.h" 

int ans;
int ix=0x0;
int pass =0x0000;
int mask =0xffff;
int org=0x1234;
int out=0x0000;
int auth=3;
int swnr;
char *str;
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
	str= "System Clear";
 display_string( 3,str );
 log (str);
	return;
}

void alarm_on( void ) {

	ans=(PORTD>>2) & 0x1;
		
	if (ans==0){
	 display_string( 3, "System Armed" );
	 //log("Welcome home!");
	} 
	
	  if (ans ==1){
	PORTE=0xff;
	//str="Motion detected";
display_string( 3, "Motion detected" );
log ("WE ARE IN TROUBLE!");
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
	 str ="PASSWORD RESET MODE ON!";
	 log (str);
		 display_string(0, str);
		
		 pass_in();
		 org =out;
	
	     if (ix >12 ){
			  pass &=0x0000;
			  ix =0;
			  if (org ==out){
				  str="Password Set!";
		  display_string(3, str);
	 }
	 else{
		 str ="PASSWORD NOT SET!!";
		  display_string(3, str);
		  
	 }
	 
	 display_update();
	quicksleep(1500);
	log (str);
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
	str =  "Password Cleared!!";
	log (str);
	display_string( 0,str );
}

return;
}

int auth_on(){
	
	swnr= getsw();	
    swnr &= 0x2;
	


if (swnr ==0x2){
	str ="ADMINISTRATOR LOGIN";
	display_string( 0, str );
	display_update();
	 pass_in();
	
		 if (ix >12 ){
			  ix =0;
		if (pass==org){
			str="PASSWORD CORRECT" ;
	display_string( 3, str);
	display_update();
	quicksleep(1500);
	auth =1;
	if (auth ==1){
		str ="System unlock!";
	display_string(3,str);
	display_update();
	quicksleep(1500);
	alarm_off(); 

}
}
else{
	str ="PASSWORD WRONG!!";
	display_string (3,str);
	display_update();
	quicksleep(1500);
		auth =0;
	if (auth ==0){
		str="Non-authorized user!!";
		log (str);
	while(1){
	PORTE=0xff;
display_string( 0, str );
display_update();
	quicksleep(1500);
	PORTE|=0xff;
	quicksleep(2500);
	PORTE&=0x00;
	}
}
}
pass &=0x0000;
	}
		

 log (str);

}

return auth;
}

void sec_on(void){
	auth_on();
	
	swnr= getsw();	
    swnr &= 0x1;
	


if (swnr ==0x1){
	auth =3;
	str="ALARM ON!!";
	display_string( 0, str );
display_update();
log (str);
quicksleep(1500);
}


if (auth==3){
alarm_on();
}


/*
if (swnr ==0x0 &&auth ==0){
	display_string(3, "PASS WRONG!!");
	display_update();
	alarm_on();
}
*/

return;
}
