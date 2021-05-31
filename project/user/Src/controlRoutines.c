#include "adcHandling.h"
#include "measurement.h"
#include "clib.h"
#include "references.h"

#define fs 50000.0
#define pi_ts (1.0/50000.0)


pll_parameters pll={0};
phase V,I;
park  pV,pI;
clarke cV,cI;


piInit pidInit={0},piqInit={0},pidcInit={0};
piData pidf={0},piqf={0},pidcf={0};

clarke icV;
park   ipV,ipVz;
phase  cOut,final;


void initControlRoutines(void){
	
//**************************************
//**************************************
	
pidInit.parameter.ts=pi_ts;
pidInit.parameter.Kp=0.05;	
pidInit.parameter.Ki=0.000048/pi_ts;
pidInit.parameter.atRest=0.0;	
	
pidInit.limit.refLimitUp=500.0;
pidInit.limit.refLimitDown=-500.0;
	
	
pidInit.limit.outputLimitUp=200.0f;	
pidInit.limit.outputLimitDown=-200.0f;

pidInit.flag.refLimitEnable=active;
pidInit.flag.outputLimitEnable=active;
pidInit.flag.feedBackReversal=passive;
pidInit.flag.outputReversal=active;

piControllerInitialization(&pidf,pidInit);


//**************************************
//**************************************
	
piqInit.parameter.ts=pi_ts;
piqInit.parameter.Kp=0.05;	
piqInit.parameter.Ki=0.000048/pi_ts;
piqInit.parameter.atRest=0.0;

piqInit.limit.refLimitUp=900.0;
piqInit.limit.refLimitDown=-900.0;
	
	
piqInit.limit.outputLimitUp=100.0f;	
piqInit.limit.outputLimitDown=-100.0f;

piqInit.flag.refLimitEnable=active;
piqInit.flag.outputLimitEnable=active;
piqInit.flag.feedBackReversal=passive;
piqInit.flag.outputReversal=active;

piControllerInitialization(&piqf,piqInit);



//**************************************
//**************************************
	
pidcInit.parameter.ts=pi_ts;
pidcInit.parameter.Kp=0.1;	
pidcInit.parameter.Ki=0.03/pi_ts;;
pidcInit.parameter.atRest=0.0;

pidcInit.limit.refLimitUp=900.0;
pidcInit.limit.refLimitDown=700.0;
	

	
pidcInit.limit.outputLimitUp=500.0f;	
pidcInit.limit.outputLimitDown=-500.0f;

pidcInit.flag.refLimitEnable=active;
pidcInit.flag.outputLimitEnable=active;
pidcInit.flag.feedBackReversal=passive;
pidcInit.flag.outputReversal=passive;

piControllerInitialization(&pidcf,pidcInit);



//**************************************	
	



}


void controlRoutines(void){
	
	rmsChannel_Type rms_channel=rms_Van;

	V.a=adc.ch.Van;
	V.c=adc.ch.Vcn;
	V.b=-adc.ch.Van-adc.ch.Vcn;//cau fictitiously generated
	
	I.a=adc.ch.Ia;
	I.b=adc.ch.Ib;
	I.c=adc.ch.Ic;
	
	if(tRMS[rms_channel].out>1.0){PLL(1.4142*V.a/tRMS[rms_channel].out,&pll);}
	
	
	clarkeParkTransform(V,&cV,&pV,pll.theta_comp);
	clarkeParkTransform(I,&cI,&pI,pll.theta_comp);
	
	
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
	
	
	//ipV.d=	pidf.signal.controllerOutput;//-ref.decouplingTermQ;			
	//ipV.q=	piqf.signal.controllerOutput;//+ref.decouplingTermD;
					
					
	inverseClarkeParkTransform(ipV,&icV,&cOut,pll.theta_comp);
	//inverseClarkeParkTransform(pV,&icV,&cOut,theta);
	
	
	



}


