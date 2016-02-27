#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int ans;
void alarm_on( void ) {

	ans=(PORTD>>2) & 0x1;
	if (ans==0){
	 display_string( 3, "System Armed" );
	} 
	
	  if (ans ==1){
	PORTE=0xff;
display_string( 3, "Motion detected" );
}
display_update;	
return;
}

void alarm_off(void){
	ans =0;
	display_string(3, "System clear");
	return;
}