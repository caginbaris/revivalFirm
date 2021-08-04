
#include "adcHandling.h"
#include "measurement.h"
#include <math.h>


#define hA 0.003354016
#define hB 	0.000256524



ntcVariables ntcVar={0};

void ntcMeasurements(void){
	

	
	double R1den,R2den,R3den;
	double T1den,T2den,T3den;
	
	

	
	if(calculationCounter==18){
	
	R1den=3.3-2.0*adc.ch.NTCa;
	ntcVar.R1=(R1den >0.1) ? adc.ch.NTCa*10000.0 /(R1den) : 500;
	T1den=(hA+hB*log(ntcVar.R1*0.0001));	
	ntcVar.T1=(T1den >0.00001) ? 1.0 /(T1den) - 273 : 200;
		
	}
	
	if(calculationCounter==19){
	
	R2den=3.3-2.0*adc.ch.NTCb;
	ntcVar.R2=(R2den >0.1) ? adc.ch.NTCb*10000.0 /(R2den) : 500;
	T2den=(hA+hB*log(ntcVar.R2*0.0001));	
	ntcVar.T2=(T2den >0.00001) ? 1.0 /(T2den) - 273 : 200;
		
	}
		
	
	if(calculationCounter==20){
	
	R3den=3.3-2.0*adc.ch.NTCc;
	ntcVar.R3=(R3den >0.1) ? adc.ch.NTCc*10000.0 /(R3den) : 500;
	T3den=(hA+hB*log(ntcVar.R3*0.0001));	
	ntcVar.T3=(T3den >0.00001) ? 1.0 /(T3den) - 273 : 200;
		
	}
	
	

}