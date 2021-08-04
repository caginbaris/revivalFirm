
#include "plib.h"
#include "adcHandling.h"
#include "measurement.h"
#include "ios.h"
#include "faultHandling.h"

#define samplingFrequency 50000

overLimit_inputParameters overCurrentRMS_Config;
overLimit_outputParameters overCurrentRMS_L1,overCurrentRMS_L2,overCurrentRMS_L3;

overLimit_inputParameters overCurrentCS_Config;
overLimit_outputParameters overCurrentCS_L1,overCurrentCS_L2,overCurrentCS_L3;

overLimit_inputParameters overCurrentPeak_Config;
overLimit_outputParameters overCurrentPeak_L1,overCurrentPeak_L2,overCurrentPeak_L3;



void overCurrentInit(void){


overCurrentRMS_Config.level=2.5;
overCurrentRMS_Config.delay=0.04;
overCurrentRMS_Config.dropout_ratio=0.99;
overCurrentRMS_Config.dropout_time=0.01;
overCurrentRMS_Config.comm_pick_on_delay=0.01;	
overCurrentRMS_Config.comm_pick_off_delay=10;
overCurrentRMS_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L1);
overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L2);	
overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L3);	
	
	
overCurrentCS_Config.level=3;
overCurrentCS_Config.delay=0.005;
overCurrentCS_Config.dropout_ratio=0.99;
overCurrentCS_Config.dropout_time=0.001;
overCurrentCS_Config.comm_pick_on_delay=0.0025;	
overCurrentCS_Config.comm_pick_off_delay=10;
overCurrentCS_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L1);
overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L2);	
overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L3);		


overCurrentPeak_Config.level=4*1.414;
overCurrentPeak_Config.delay=0.001;
overCurrentPeak_Config.dropout_ratio=0.99;
overCurrentPeak_Config.dropout_time=0.0005;
overCurrentPeak_Config.comm_pick_on_delay=0.001;	
overCurrentPeak_Config.comm_pick_off_delay=10;
overCurrentPeak_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L1);
overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L2);	
overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L3);		
	

if(	overCurrentRMS_L1.initialized==0 ||overCurrentCS_L1.initialized==0 ||overCurrentPeak_L1.initialized==0 ||
		overCurrentRMS_L2.initialized==0 ||overCurrentCS_L2.initialized==0 ||overCurrentPeak_L2.initialized==0 ||
		overCurrentRMS_L3.initialized==0 ||overCurrentCS_L3.initialized==0 ||overCurrentPeak_L3.initialized==0 ){
	

	faultWord.bit.overCurrentProtectionInit=1;

	}
		
}

void overCurrent(void){
	
	double absA,absB,absC;
	
	absA=adc.ch.Ia>0?adc.ch.Ia:-adc.ch.Ia;
	absB=adc.ch.Ib>0?adc.ch.Ib:-adc.ch.Ib;
	absC=adc.ch.Ic>0?adc.ch.Ic:-adc.ch.Ic;
	
	overLimit(tRMS[rms_Ia].out,overCurrentRMS_Config,&overCurrentRMS_L1,0,DO.bit.rst);
	overLimit(tRMS[rms_Ib].out,overCurrentRMS_Config,&overCurrentRMS_L2,0,DO.bit.rst);
	overLimit(tRMS[rms_Ic].out,overCurrentRMS_Config,&overCurrentRMS_L3,0,DO.bit.rst);
	
	overLimit(cs_Aout.I,overCurrentCS_Config,&overCurrentCS_L1,0,DO.bit.rst);
	overLimit(cs_Bout.I,overCurrentCS_Config,&overCurrentCS_L2,0,DO.bit.rst);
	overLimit(cs_Cout.I,overCurrentCS_Config,&overCurrentCS_L3,0,DO.bit.rst);

	overLimit(absA,overCurrentPeak_Config,&overCurrentPeak_L1,0,DO.bit.rst);
	overLimit(absB,overCurrentPeak_Config,&overCurrentPeak_L2,0,DO.bit.rst);
	overLimit(absC,overCurrentPeak_Config,&overCurrentPeak_L3,0,DO.bit.rst);


}