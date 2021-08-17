#include "adcHandling.h"
#include "measurement.h"
#include "clib.h"
#include "plib.h"
#include "mlib.h"
#include "faultHandling.h"
#include "pllHandling.h"
#include "references.h"

#define fs 50000.0
#define pi_ts (1.0/50000.0)



phase V,I;
park  pV,pI;
clarke cV,cI;
sincosValues scVal;


piInit pidInit={0},piqInit={0},pidcInit={0};
piData pidf={0},piqf={0},pidcf={0};

clarke icV;
park   ipV,ipVz;
phase  cOut,final;
phase filteredV={0},filteredVz={0};


//0.5e4 filter
double fofCoefficents5e3[2]={

0.245237275252786,
-0.509525449494429

};

void initControlRoutines(void){
	

	
//**************************************
//**************************************
	
pidInit.parameter.ts=pi_ts;
pidInit.parameter.Kp=0.1;	
pidInit.parameter.Ki=0.000054/pi_ts;
pidInit.parameter.atRest=0.0;	
	
pidInit.limit.refLimitUp=20.0;
pidInit.limit.refLimitDown=-20.0;
		
//cau can be increased	
pidInit.limit.rateLimit=2000;
	
pidInit.limit.outputLimitUp=20.0;	
pidInit.limit.outputLimitDown=-20.0;

pidInit.flag.refLimitEnable=active;
pidInit.flag.outputLimitEnable=active;
pidInit.flag.feedBackReversal=passive;
pidInit.flag.outputReversal=active;

piControllerInitialization(&pidf,pidInit);


//**************************************
//**************************************
	
piqInit.parameter.ts=pi_ts;
piqInit.parameter.Kp=0.1;	
piqInit.parameter.Ki=0.000054/pi_ts;
piqInit.parameter.atRest=0.0;

piqInit.limit.refLimitUp=20.0;
piqInit.limit.refLimitDown=-20.0;
	
piqInit.limit.rateLimit=20;

piqInit.limit.outputLimitUp=20.0;	
piqInit.limit.outputLimitDown=-20.0;

piqInit.flag.refLimitEnable=active;
piqInit.flag.outputLimitEnable=active;
piqInit.flag.feedBackReversal=passive;
piqInit.flag.outputReversal=active;

piControllerInitialization(&piqf,piqInit);



//**************************************
//**************************************
	
pidcInit.parameter.ts=pi_ts;
pidcInit.parameter.Kp=0.1;	
pidcInit.parameter.Ki=0.005/pi_ts;;
pidcInit.parameter.atRest=0.0;

pidcInit.limit.refLimitUp=100.0;
pidcInit.limit.refLimitDown=30.0;

pidcInit.limit.rateLimit=10;
	
pidcInit.limit.outputLimitUp=20.0;	
pidcInit.limit.outputLimitDown=-20.0;

pidcInit.flag.refLimitEnable=active;
pidcInit.flag.outputLimitEnable=active;
pidcInit.flag.feedBackReversal=passive;
pidcInit.flag.outputReversal=passive;

piControllerInitialization(&pidcf,pidcInit);



//**************************************	
	



}


void controlRoutines(void){
	


	V.a=adc.ch.Van;
	V.b=adc.ch.Vbn;
	V.c=adc.ch.Vcn;
	
	I.a=adc.ch.Ia;
	I.b=adc.ch.Ib;
	I.c=adc.ch.Ic;
	
	
	tCalculations(pll.theta_comp,&scVal);
	
	clarkeParkTransform(V,&cV,&pV,scVal);
	clarkeParkTransform(I,&cI,&pI,scVal);
	
	
	//d-side
	
	pidcf.signal.ref=ref.Vdc;
	pidcf.signal.feedback=Vdcf;
	piControllerImplementation(&pidcf);
	
	pidf.signal.ref=pidcf.signal.controllerOutput;
	pidf.signal.feedback=pI.d;
	piControllerImplementation(&pidf);

	//q-side
	
	piqf.signal.ref=ref.I;
	piqf.signal.feedback=pI.q;
	piControllerImplementation(&piqf);
	
	//current direction is reverse 
	
	
	FOF(pidf.signal.controllerOutput,ipVz.d,ipV.d,fofCoefficents1e2);
	FOF(piqf.signal.controllerOutput,ipVz.q,ipV.q,fofCoefficents1e2);

	
	//ipV.d=	ipV.d-ref.decouplingTermQ;			
	//ipV.q=	ipV.d+ref.decouplingTermD;
					
					
	inverseClarkeParkTransform(ipV,&icV,&cOut,scVal);

	FOF(adc.ch.Van,filteredVz.a,filteredV.a,fofCoefficents5e3); 
	FOF(adc.ch.Vbn,filteredVz.b,filteredV.b,fofCoefficents5e3); 
	FOF(adc.ch.Vcn,filteredVz.c,filteredV.c,fofCoefficents5e3); 
	
	
	final.a=cOut.a+filteredV.a;
	final.b=cOut.b+filteredV.b;
	final.c=cOut.c+filteredV.c;
	
	//final.a=cOut.a-adc.ch.Van;
	//final.b=cOut.b-adc.ch.Vbn;
	//final.c=cOut.c-adc.ch.Vcn;
	
	


}



