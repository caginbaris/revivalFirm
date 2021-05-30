
#include "adcHandling.h"
#include "mlib.h" 

double dcRipple=0, dcAverage=0, Vdcf=0;

static sos_parameters sos_pDC={0};
static double Vdcz=0;



//1e1 filter
static double sosCoefficentsDC[]={

0.0000065694008554209,   0.0000262363266723440,   0.0000065487948485740,
-1.993697158102402,   0.993736512624778

};

//1e2 filter
double fofCoefficents1e2[2]={

0.006244035046343,
-0.987511929907314

};




void dcMeasurement(void){
	
	
SOS(adc.ch.Vdc,dcAverage,sosCoefficentsDC,sos_pDC);
dcRipple=adc.ch.Vdc-dcAverage;

FOF(adc.ch.Vdc,Vdcz,Vdcf,fofCoefficents1e2);



}