#include "plib.h"
#include "adcHandling.h"
#include "ios.h"
#include "measurement.h"
#include "faultHandling.h"

#define samplingFrequency 50000

overLimit_inputParameters overTemp_Config;
overLimit_outputParameters overTempA,overTempB,overTempC;


void ntcProtectionsInit(void){


overTemp_Config.level=45;
overTemp_Config.delay=1;
overTemp_Config.dropout_ratio=0.99;
overTemp_Config.dropout_time=0.01;
overTemp_Config.comm_pick_on_delay=0.01;	
overTemp_Config.comm_pick_off_delay=10;
overTemp_Config.fs=samplingFrequency;

overLimitInitialization(overTemp_Config,&overTempA);
overLimitInitialization(overTemp_Config,&overTempB);
overLimitInitialization(overTemp_Config,&overTempC);
	
	
if(	overTempA.initialized==0 ||
		overTempB.initialized==0 ||
		overTempC.initialized==0 ){
		
		
		faultWord.bit.ntcProtectionInit=1;
		
		}

	
}	
	
	
	
	




void ntcProtections(void){

	
	overLimit(ntcVar.T1,overTemp_Config,&overTempA,0,DO.bit.rst);
	overLimit(ntcVar.T2,overTemp_Config,&overTempB,0,DO.bit.rst);
	overLimit(ntcVar.T3,overTemp_Config,&overTempC,0,DO.bit.rst);



}