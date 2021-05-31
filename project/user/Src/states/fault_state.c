#include "states.h"
#include "ios.h"
#include "faultHandling.h"
#include "measurement.h"
#include "LEDs.h"

stateID fault_state(void){

DO.bit.mcb_in=0;	
	
LED.out._2=0;
LED.out._3=0;	

if(DO.bit.rst){

if(faultWord.all==0){currentState=ready;}

if(currentState!=fault){previousState=fault;}


}

return currentState;

}