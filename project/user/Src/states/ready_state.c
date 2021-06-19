#include "states.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "commandHandling.h"
#include "ios.h"
#include "plib.h"
#include "LEDs.h"

static transition_parameters startTrigger={0,0};

stateID ready_state(void){
	
	
LED.out._2=1;
LED.out._3=0;		
	

low2highTransition(command.bit.start,&startTrigger);
	

if(startTrigger.output){currentState=charged;}
if(faultWord.all){currentState=fault;}

if(currentState!=ready){

previousState=ready;
startTrigger.back=0;

}

return currentState;

}

