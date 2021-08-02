#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurement.h"
#include "LEDs.h"

static delay_parameters idleToggle={0,samplingRate*0.05,0};
static delay_parameters waiting4dcLevel={0,samplingRate*5,0};

stateID idle_state(void){
	
	
fToggle(1,&idleToggle);	
	
LED.out._2=idleToggle.output;
LED.out._3=0;		

on_delay(1,&waiting4dcLevel);
	
if(waiting4dcLevel.output==1 && DI.bit.mcb_in_check==1){

	if(tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.3){

	currentState=run;	

	}else{

	faultWord.bit.idle_state_error=1;
	currentState=fault;

	}

}	
	



if(faultWord.all){currentState=fault;}
if(currentState!=idle){
	

waiting4dcLevel.output=0;
waiting4dcLevel.count=0;
	
previousState=idle;

	
}


return currentState;

}

