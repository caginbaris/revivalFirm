#include "states.h"
#include "plib.h"
#include "ios.h"
#include "faultHandling.h"
#include "LEDs.h"

static delay_parameters timeout={0,samplingRate*5,0};

stateID stopped_state(void){
	
	
LED.out._2=0;
LED.out._3=0;	
	

on_delay(1,&timeout);
	
if(timeout.output){
	
currentState=ready;	
	
if(faultWord.all){currentState=fault;}

previousState=stopped;

timeout.count=0;
timeout.output=0;

}

return currentState;

}

