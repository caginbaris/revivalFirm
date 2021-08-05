#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurement.h"
#include "LEDs.h"

static delay_parameters chargedToggle={0,samplingRate*0.1,0};
static delay_parameters waiting4dcLevel={0,samplingRate*20,0};

stateID charged_state(void){
	

fToggle(1,&chargedToggle);		
	
LED.out._2=chargedToggle.output;
LED.out._3=0;			

on_delay(1,&waiting4dcLevel);
	
if(waiting4dcLevel.output==1 || tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.1){

	if(tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.1){
		
	DO.bit.mcb_in=1;
	currentState=idle;
	
	}else{
		
	faultWord.bit.charged_state_error=1;
	currentState=fault;

	}

}	
	

if(faultWord.all){currentState=fault;}

if(currentState!=charged){
	

waiting4dcLevel.output=0;
waiting4dcLevel.count=0;
	
previousState=charged;

	
}


return currentState;

}

