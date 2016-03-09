#include <stdint.h>
#include<stdio.h>
#include <pic32mx.h>

#include "mipslab.h" 
/*
alarm function file
*/

/*constant*/
int ans;
int ix=0x0;
int pass =0x0000;
int mask =0xffff;
int org=0x1234;
int out=0x0000;
int auth=3;
int swnr;
char *str;

//password input
void pass_in(void){
	//button initialize
	int btn;
	btn =getbtns();
	
	//switch initlize
	swnr =getsw();
	swnr &= 0x8;
	
	//clean the input as soon as it reach 4 digit input
	if(ix >12){
		ix =0;
		
	}
	// if button is not 0 do sth
	if (btn !=0){
		//move the value depends on the time of input
		btn =btn <<ix;
		//current input
	  pass =pass | btn;
	  print_pass();
	  //save input storage for future usage
	  if(swnr ==8){
	  out= out| btn;
	  }
	  //next digit
	  ix=ix+4;
	}
	
	return ;
}
//shut down alarm
void alarm_off(void){
	ans =0; 
	str= "System Clear";
 display_string( 3,str );
 log (str);
	return;
}
//start up alarm
void alarm_on( void ) {
//input sensor connect to  pin 6
	ans=(PORTD>>2) & 0x1;
		// if receive 0
	if (ans==0){
	 display_string( 3, "System Armed" );
	 //log("Welcome home!");
	} 
	//if receive 1
	  if (ans ==1){
		  //all led on
	PORTE=0xff;
	//str="Motion detected";
	//display message
display_string( 3, "Motion detected" );
//log certain message
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
