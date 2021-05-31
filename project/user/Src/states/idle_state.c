#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurement.h"
#include "LEDs.h"

static delay_parameters idleToggle={0,samplingRate*0.1,0};
static delay_parameters waiting4dcLevel={0,samplingRate*12,0};

stateID idle_state(void){
	
fToggle(1,&idleToggle);	
	
LED.out._2=idleToggle.output;
LED.out._3=0;		

on_delay(1,&waiting4dcLevel);
	
if(waiting4dcLevel.output){

if(tRMS[rms_Vdc].out<tRMS[rms_Vab].out*1.3){

faultWord.bit.idle_state_error=1;
currentState=fault;

}else{

currentState=idle;

}

}	
	




if(currentState!=idle){
	

waiting4dcLevel.count=0;
previousState=idle;

	
}


return currentState;

}

