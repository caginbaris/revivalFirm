#include "adcHandling.h"
#include "mlib.h"
#include "measurement.h"
#include "controlRoutines.h"

rmsChannel_Type rmsSeq=rms_Ia;

trueRMS_sampled_parameters tRMS[23]={
	
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
{0,0,17},
{0,0,18},
{0,0,19},
{0,0,20},
{0,0,21},
{0,0,22},

};



void rmsMeasurement(void){
	

		trueRMS_sampled(adc.ch.Ia,&tRMS[0],calculationCounter);
		trueRMS_sampled(adc.ch.Ib,&tRMS[1],calculationCounter);
		trueRMS_sampled(adc.ch.Ic,&tRMS[2],calculationCounter);
		
		trueRMS_sampled(adc.ch.Van,&tRMS[3],calculationCounter);
		trueRMS_sampled(adc.ch.Vbn,&tRMS[4],calculationCounter);
		trueRMS_sampled(adc.ch.Vcn,&tRMS[5],calculationCounter);
		
		trueRMS_sampled(adc.ch.Van-adc.ch.Vbn,&tRMS[6],calculationCounter);
		trueRMS_sampled(adc.ch.Vbn-adc.ch.Vcn,&tRMS[7],calculationCounter);
		trueRMS_sampled(adc.ch.Vcn-adc.ch.Van,&tRMS[8],calculationCounter);
		
		
		trueRMS_sampled(adc.ch.Vdc,&tRMS[9],calculationCounter);

		
		trueRMS_sampled(sym.V0,&tRMS[10],calculationCounter);
		trueRMS_sampled(sym.V1,&tRMS[11],calculationCounter);
		trueRMS_sampled(sym.V2,&tRMS[12],calculationCounter);
		
		trueRMS_sampled(sym.I0,&tRMS[13],calculationCounter);
		trueRMS_sampled(sym.I1,&tRMS[14],calculationCounter);
		trueRMS_sampled(sym.I2,&tRMS[15],calculationCounter);
		
		trueRMS_sampled(dcRipple,&tRMS[16],calculationCounter);
		
		trueRMS_sampled(final.a,&tRMS[17],calculationCounter);
		trueRMS_sampled(final.b,&tRMS[18],calculationCounter);
		trueRMS_sampled(final.c,&tRMS[19],calculationCounter);
		
		trueRMS_sampled(cOut.a,&tRMS[20],calculationCounter);
		trueRMS_sampled(cOut.b,&tRMS[21],calculationCounter);
		trueRMS_sampled(cOut.c,&tRMS[22],calculationCounter);


}