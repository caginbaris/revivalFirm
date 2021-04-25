#include "adcHandling.h"
#include "mlib.h"

#define halfPeriod 500

trueRMS_sampled_parameters tRMS[6]={
	
{0,0,0},
{0,0,1},
{0,0,2},
{0,0,3},
{0,0,4},
{0,0,5},


};



void rmsMeasurement(void){
	
		static uint16_t periodCounter=0;
	
		if(++periodCounter==halfPeriod){periodCounter=0;}
		
		
		trueRMS_sampled(adc.ch.Ia,&tRMS[0],periodCounter);
		trueRMS_sampled(adc.ch.Ib,&tRMS[1],periodCounter);
		trueRMS_sampled(adc.ch.Ic,&tRMS[2],periodCounter);
		
		trueRMS_sampled(adc.ch.Van,&tRMS[3],periodCounter);
		trueRMS_sampled(adc.ch.Vbn,&tRMS[4],periodCounter);
		trueRMS_sampled(adc.ch.Vcn,&tRMS[5],periodCounter);
		


}