
#include "adcHandling.h"
#include "mlib.h" 

double dcRipple=0, dcAverage=0, Vdcf=0;

static sos_parameters sos_pDC={0};
static double Vdcz=0;



//1e2 filter
double fofCoefficents1e2[2]={

0.006244035046343,
-0.987511929907314

};

double fofCoefficents2e1[2]={

0.001255060566451,
-0.997489878867098

};



void dcMeasurement(void){
	
	
//SOS(adc.ch.Vdc,dcAverage,sosCoefficentsDC,sos_pDC);
FOF(adc.ch.Vdc,Vdcz,Vdcf,fofCoefficents2e1); 	
dcRipple=adc.ch.Vdc-Vdcf; 
//FOF(adc.ch.Vdc,Vdcz,Vdcf,fofCoefficents1e2); 



}