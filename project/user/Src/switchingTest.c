#include <stdint.h>
#include "pwmGeneration.h"
#include "plib.h"
#include "LEDs.h"

uint8_t switchingEnable=0;

transition_parameters swHTransition={0,0};
transition_parameters swLTransition={0,0};

delay_parameters swEnable={0,1000,0};

void switchingTest(void){
	
	low2highTransition(switchingEnable,&swHTransition);
	off_delay(swHTransition.output,&swEnable);
	high2lowTransition(switchingEnable,&swLTransition);
	
	if(swHTransition.output){
	
	modulatorEnable();

	}
	
	if(swLTransition.output){
	
	modulatorDisable();
	
	}
	
	sw_count_a=1000;
	sw_count_b=1000;
	sw_count_c=1000;
	
	modulator();


}