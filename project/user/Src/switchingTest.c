#include "stdint.h"
#include "pwmGeneration.h"
#include "plib.h"

uint8_t switchingEnable=0;

transition_parameters swTransition={0,0};
delay_parameters swEnable={0,10,0};

void switchingTest(void){
	
	low2highTransition(switchingEnable,&swTransition);
	off_delay(swTransition.output,&swEnable);
	
	if(swTransition.output){modulatorEnable();}
	if(!swEnable.output){modulatorDisable();}
	
	sw_count_a=wscale*0.25;
	sw_count_b=wscale*0.25;
	sw_count_c=wscale*0.25;
	
	modulator();


}