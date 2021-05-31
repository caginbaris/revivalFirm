#include "states.h"
#include "plib.h"
#include "ios.h"
#include "faultHandling.h"

static delay_parameters timeout={0,samplingRate*5,0};

stateID stopped_state(void){

on_delay(1,&timeout);
	
if(timeout.output){
	
currentState=ready;	
	
if(faultWord.all){currentState=fault;}

previousState=stopped;

timeout.output=0;
timeout.count=0;

}

return currentState;

}

