#include "commandHandling.h"
#include "states.h"

commandInputs command={0};

void commandHandling(void){
	
if(currentState!=ready){command.bit.start=0;}
if(currentState==stopped){command.bit.stop=0;}

}