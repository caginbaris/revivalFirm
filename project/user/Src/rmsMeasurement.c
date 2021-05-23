#include "adcHandling.h"
#include "mlib.h"



trueRMS_sampled_parameters tRMS[10]={
	
{0,0,0},
{0,0,1},
{0,0,2},
{0,0,3},
{0,0,4},
{0,0,5},
{0,0,6},
{0,0,7},
{0,0,8},
{0,0,9}
};



void rmsMeasurement(void){
	
		static uint16_t periodCounter=0;
	
		if(++periodCounter==1000){periodCounter=0;}
		
		
		trueRMS_sampled(adc.ch.Ia,&tRMS[0],periodCounter);
		trueRMS_sampled(adc.ch.Ib,&tRMS[1],periodCounter);
		trueRMS_sampled(adc.ch.Ic,&tRMS[2],periodCounter);
		
		trueRMS_sampled(adc.ch.Van,&tRMS[3],periodCounter);
		trueRMS_sampled(adc.ch.Vbn,&tRMS[4],periodCounter);
		trueRMS_sampled(adc.ch.Vcn,&tRMS[5],periodCounter);
		
		trueRMS_sampled(adc.ch.Van-adc.ch.Vbn,&tRMS[6],periodCounter);
		trueRMS_sampled(adc.ch.Vbn-adc.ch.Vcn,&tRMS[7],periodCounter);
		trueRMS_sampled(adc.ch.Vcn-adc.ch.Van,&tRMS[8],periodCounter);
		
		trueRMS_sampled(adc.ch.Vdc,&tRMS[9],periodCounter);
		

}