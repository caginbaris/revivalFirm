#include "states.h"
#include "plib.h"
#include "ios.h"
#include "LEDs.h"
#include "faultHandling.h"


static delay_parameters startupPassTime={0,samplingRate*10,0};
static delay_parameters startupToggle={0,samplingRate*1,0};

stateID startup_state(void){


//initial DO & LED action


fToggle(1,&startupToggle);

LED.out._2=startupToggle.output;
LED.out._3=!startupToggle.output;


on_delay(1,&startupPassTime);
	
if(startupPassTime.output){
	
startupPassTime.count=0;

currentState=ready;	
	
if(faultWord.all){currentState=fault;}previousState=startup;}

return currentState;

}

