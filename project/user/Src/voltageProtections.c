#include "plib.h"
#include "adcHandling.h"
#include "ios.h"
#include "measurement.h"
#include "states.h"
#include "faultHandling.h"

#define samplingFrequency 50000

overLimit_inputParameters overVoltageDC_Config,overVoltageAC_Config;
overLimit_outputParameters overVoltageDC, overVoltageAC;

underLimit_inputParameters underVoltageDC_Config,underVoltageAC_Config;
underLimit_outputParameters underVoltageDC, underVoltageAC;



void voltageProtectionsInit(void){


overVoltageDC_Config.level=10;
overVoltageDC_Config.delay=0.01;
overVoltageDC_Config.dropout_ratio=0.99;
overVoltageDC_Config.dropout_time=0.01;
overVoltageDC_Config.comm_pick_on_delay=0.01;	
overVoltageDC_Config.comm_pick_off_delay=10;
overVoltageDC_Config.fs=samplingFrequency;

overLimitInitialization(overVoltageDC_Config,&overVoltageDC);

	
overVoltageAC_Config.level=70;
overVoltageAC_Config.delay=0.01;
overVoltageAC_Config.dropout_ratio=0.99;
overVoltageAC_Config.dropout_time=0.01;
overVoltageAC_Config.comm_pick_on_delay=0.01;	
overVoltageAC_Config.comm_pick_off_delay=10;
overVoltageAC_Config.fs=samplingFrequency;

overLimitInitialization(overVoltageAC_Config,&overVoltageAC);	


underVoltageDC_Config.level=5;
underVoltageDC_Config.delay=0.04;
underVoltageDC_Config.dropout_ratio=1.01;
underVoltageDC_Config.dropout_time=0.01;
underVoltageDC_Config.comm_pick_on_delay=0.01;	
underVoltageDC_Config.comm_pick_off_delay=10;
underVoltageDC_Config.fs=samplingFrequency;

underLimitInitialization(underVoltageDC_Config,&underVoltageDC);

	
underVoltageAC_Config.level=7;
underVoltageAC_Config.delay=0.04;
underVoltageAC_Config.dropout_ratio=1.01;
underVoltageAC_Config.dropout_time=0.01;
underVoltageAC_Config.comm_pick_on_delay=0.01;	
underVoltageAC_Config.comm_pick_off_delay=10;
underVoltageAC_Config.fs=samplingFrequency;

underLimitInitialization(underVoltageAC_Config,&underVoltageAC);


if(	overVoltageDC.initialized==0 ||
		overVoltageAC.initialized==0 ||
		underVoltageDC.initialized==0 ||
		underVoltageAC.initialized==0 ){
		
		
		faultWord.bit.voltageProtectionInit=1;
		
		}

	

}


void voltageProtections(void){
	
	uint8_t inhibitUV_DC;
	
	underVoltageDC_Config.level=5;//tRMS[rms_Van].out*1.414*0.8; //cau config and real parameters 
	inhibitUV_DC=(currentState==charged ||currentState==idle || currentState==run )?(0):(1);

	
	overLimit(adc.ch.Vdc,overVoltageDC_Config,&overVoltageDC,0,DO.bit.rst);
	overLimit(max3p(cs_Aout.V,cs_Bout.V,cs_Cout.V),overVoltageAC_Config,&overVoltageAC,0,DO.bit.rst);
	
	
	underLimit(adc.ch.Vdc,underVoltageDC_Config,&underVoltageDC,0,DO.bit.rst); //cau inhibit condition should be added
	underLimit(min3p(cs_Aout.V,cs_Bout.V,cs_Cout.V),underVoltageAC_Config,&underVoltageAC,0,DO.bit.rst); //cau inhibit condition should be added


}