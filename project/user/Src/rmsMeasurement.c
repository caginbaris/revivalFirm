#include "adcHandling.h"
#include "mlib.h"
#include "measurement.h"

rmsChannel_Type rmsSeq=rms_Ia;

trueRMS_sampled_parameters tRMS[17]={
	
{0,0,0},
{0,0,1},
{0,0,2},
{0,0,3},
{0,0,4},
{0,0,5},
{0,0,6},
{0,0,7},
{0,0,8},
{0,0,9},
{0,0,10},
{0,0,11},
{0,0,12},
{0,0,13},
{0,0,14},
{0,0,15},
{0,0,16},

};



void rmsMeasurement(void){
	
		static uint16_t periodCounter=0;
	
		if(++periodCounter==10000){periodCounter=0;}
		
		
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
		
		trueRMS_sampled(sym.V0,&tRMS[10],periodCounter);
		trueRMS_sampled(sym.V1,&tRMS[11],periodCounter);
		trueRMS_sampled(sym.V2,&tRMS[12],periodCounter);
		
		trueRMS_sampled(sym.I0,&tRMS[13],periodCounter);
		trueRMS_sampled(sym.I1,&tRMS[14],periodCounter);
		trueRMS_sampled(sym.I2,&tRMS[15],periodCounter);
		
		trueRMS_sampled(dcRipple,&tRMS[16],periodCounter);
		

}