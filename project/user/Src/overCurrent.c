
#include "plib.h"
#include "adcHandling.h"
#include "ios.h"

#define samplingFrequency 50000

overLimit_inputParameters overCurrentRMS_Config;
overLimit_outputParameters overCurrentRMS_L1,overCurrentRMS_L2,overCurrentRMS_L3;

overLimit_inputParameters overCurrentCS_Config;
overLimit_outputParameters overCurrentCS_L1,overCurrentCS_L2,overCurrentCS_L3;

overLimit_inputParameters overCurrentPeak_Config;
overLimit_outputParameters overCurrentPeak_L1,overCurrentPeak_L2,overCurrentPeak_L3;



void overCurrentInit(void){


overCurrentRMS_Config.level=24;
overCurrentRMS_Config.delay=0.04;
overCurrentRMS_Config.dropout_ratio=0.99;
overCurrentRMS_Config.dropout_time=0.01;
overCurrentRMS_Config.comm_pick_on_delay=0.01;	
overCurrentRMS_Config.comm_pick_off_delay=10;
overCurrentRMS_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L1);
overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L2);	
overLimitInitialization(overCurrentRMS_Config,&overCurrentRMS_L3);	
	
	
overCurrentCS_Config.level=30;
overCurrentCS_Config.delay=0.005;
overCurrentCS_Config.dropout_ratio=0.99;
overCurrentCS_Config.dropout_time=0.001;
overCurrentCS_Config.comm_pick_on_delay=0.0025;	
overCurrentCS_Config.comm_pick_off_delay=10;
overCurrentCS_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L1);
overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L2);	
overLimitInitialization(overCurrentCS_Config,&overCurrentCS_L3);		


overCurrentPeak_Config.level=50;
overCurrentPeak_Config.delay=0.001;
overCurrentPeak_Config.dropout_ratio=0.99;
overCurrentPeak_Config.dropout_time=0.0005;
overCurrentPeak_Config.comm_pick_on_delay=0.0025;	
overCurrentPeak_Config.comm_pick_off_delay=10;
overCurrentPeak_Config.fs=samplingFrequency;

overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L1);
overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L2);	
overLimitInitialization(overCurrentPeak_Config,&overCurrentPeak_L3);		
	

}


void overCurrent(void){

	
	overLimit(adc.ch.Ia,overCurrentPeak_Config,&overCurrentPeak_L1,0,DO.bit.rst);
	overLimit(adc.ch.Ib,overCurrentPeak_Config,&overCurrentPeak_L2,0,DO.bit.rst);
	overLimit(adc.ch.Ic,overCurrentPeak_Config,&overCurrentPeak_L3,0,DO.bit.rst);


}