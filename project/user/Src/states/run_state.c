#include "states.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "clib.h"
#include "measurement.h"
#include "LEDs.h"
#include "commandHandling.h"
#include "pwmGeneration.h"
#include "controlRoutines.h"
#include "references.h"
#include "testBenches.h"

static delay_parameters wait4InitialConditions={0,samplingRate*5,0};
static delay_parameters timeout={0,samplingRate*15,0};
static transition_parameters checked={0};

static uint8_t dcRamp=0;


stateID run_state(void){
	
	
uint8_t initialCheck;	
	
LED.out._2=1;

	
initialCheck=	DO.bit.mcb_in==1 && tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.15;

on_delay(initialCheck,&wait4InitialConditions);
	
on_delay(wait4InitialConditions.output==0,&timeout);


if(timeout.output==1){ 

if(LED.out._3==0){

faultWord.bit.run_state_error=1;
	
}

}	
	
	
low2highTransition(wait4InitialConditions.output,&checked);


if(checked.output){
	
	LED.out._3=1; 
	
	modulatorEnable();

	pidcf.flag.enable=1;
	piqf.flag.enable=1;
	pidf.flag.enable=1;	
  	
	
	dcRamp=1;
	ref.Vdc=Vdcf;

}
	
	

if(dcRamp){

	
	ref.Vdc+=0.00002;	// increases 1v per sec
	
	if(ref.Vdc>ref.Vdc_opt){ref.Vdc=ref.Vdc_opt,dcRamp=0;}	
	//if(ref.Vdc>ref.Vdc_final){ref.Vdc=ref.Vdc_final,dcRamp=0;}	
	
}


if(dcRamp==0 && LED.out._3==1){

ref.Vdc=ref.Vdc_opt;

}


modulator();


if(command.bit.stop){currentState=stopped;}
if(faultWord.all){currentState=fault;}

if(currentState!=run){
	
	
	modulatorDisable();
	
	recorder();
	
	pidcf.flag.enable=0;
	piqf.flag.enable=0;
	pidf.flag.enable=0;	
	
	dcRamp=0;
	
	previousState=run;
	
	wait4InitialConditions.count=0;
	wait4InitialConditions.output=0;
	
	timeout.count=0;
	timeout.output=0;

	checked.output=0;
	checked.back=0;
	
	
}

return currentState;
	

}

