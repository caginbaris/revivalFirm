#include "plib.h"
#include "adcHandling.h"
#include "measurement.h"
#include "ios.h"
#include "faultHandling.h"
#include "states.h"

#define meanCurrentThreshold 1.0
#define dcRippleThreshold 1.0

double meanValueIa=0;
double meanValueIb=0;
double meanValueIc=0;


void meanCurrentCheck(void){
	
	static uint32_t meanValueCounter=0;
	
	static double meanValueSumIa=0;
	static double meanValueSumIb=0;
	static double meanValueSumIc=0;
	
	
	
	meanValueSumIa+=adc.ch.Ia;
	meanValueSumIb+=adc.ch.Ib;
	meanValueSumIc+=adc.ch.Ic;
	
	meanValueCounter++;
	
	if(meanValueCounter==5000){
	
	meanValueCounter=0;
		
	meanValueIa=meanValueSumIa*0.0002;	
	meanValueIb=meanValueSumIb*0.0002;
	meanValueIc=meanValueSumIc*0.0002;
		
	meanValueSumIa=0;	
	meanValueSumIb=0;
	meanValueSumIc=0;	
		
		
	}
	
	
	if(meanValueIa>meanCurrentThreshold){faultWord.bit.meanIa=1;}
	if(meanValueIb>meanCurrentThreshold){faultWord.bit.meanIb=1;}
	if(meanValueIc>meanCurrentThreshold){faultWord.bit.meanIc=1;}

	
}


void dcRippleCheck(void){
	
	static delay_parameters dcRippleDelay={0,50000,0};
	
	on_delay(dcRipple>dcRippleThreshold,&dcRippleDelay); 
	
	if(dcRippleDelay.output){faultWord.bit.dcRippleOverLimit=1;}
	

}


void phaseSeqCheck(void){
	
	static delay_parameters phaseSeqDelay={0,50000,0};
	
	on_delay(sym.V2>sym.V1*0.25,&phaseSeqDelay);
	
	if(phaseSeqDelay.output){faultWord.bit.phaseSequenceControl=1;}
	

}





void miscProtections(){

	meanCurrentCheck();
	dcRippleCheck();
	
	//cau not active for now if(currentState!=run){phaseSeqCheck();}
	

}