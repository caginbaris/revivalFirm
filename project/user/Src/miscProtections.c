#include "plib.h"
#include "adcHandling.h"
#include "measurement.h"
#include "ios.h"
#include "faultHandling.h"

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
	

	faultWord.bit.meanIa=(meanValueIa>1.0);
	faultWord.bit.meanIb=(meanValueIb>1.0);
	faultWord.bit.meanIc=(meanValueIc>1.0);
	


}


void dcRippleCheck(void){
	
	static delay_parameters dcRippleDelay={0,50000,0};
	
	on_delay(dcRipple>50.0,&dcRippleDelay);
	
	faultWord.bit.dcRippleOverLimit=dcRippleDelay.output;
	

}

void miscProtections(){

	meanCurrentCheck();
	dcRippleCheck();
	

}