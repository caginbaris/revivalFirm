#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurement.h"
#include "LEDs.h"

static delay_parameters chargedToggle={0,samplingRate*1,0};
static delay_parameters waiting4dcLevel={0,samplingRate*12,0};

stateID charged_state(void){

fToggle(1,&chargedToggle);		
	
LED.out._2=chargedToggle.output;
LED.out._3=0;			

on_delay(1,&waiting4dcLevel);
	
if(waiting4dcLevel.output){

if(tRMS[rms_Vdc].out<tRMS[rms_Vab].out*1.2){

faultWord.bit.charged_state_error=1;
currentState=fault;

}else{

DO.bit.mcb_in=1;
currentState=idle;

}

}	
	




if(currentState!=charged){
	

waiting4dcLevel.count=0;
previousState=charged;

	
}


return currentState;

}

