#include "faultHandling.h"
#include "adcHandling.h"
#include "ios.h"
#include "protection.h"

faultInputs faultWord={0};
delay_parameters resetUpTime={0,1000,0};


void faultHandling(void){
	
	
	if(DO.bit.rst==1){
	
	faultWord.all=0;
	
	DO.bit.rst=0;		
		
	}
	
	
	
	//faultWord.bit.pwrgd_3v3 = (DI.bit.pwrgd_3v3 ==0) ? 1 : 0; //cau check for this
	
	if(adc.ch.v5<4.85){faultWord.bit.pwrgd_v5=1;}
	if(DI.bit.pwrgd_24v){faultWord.bit.pwrgd_24v=1;}
	
	if(!DI.bit.hb1_fault){faultWord.bit.hb1_fault=1;}
	if(!DI.bit.hb2_fault){faultWord.bit.hb2_fault=1;}
	if(!DI.bit.hb3_fault){faultWord.bit.hb3_fault=1;}
	

	faultWord.bit.oc_rms_L1=overCurrentRMS_L1.trip_latch;
	faultWord.bit.oc_rms_L2=overCurrentRMS_L2.trip_latch;
	faultWord.bit.oc_rms_L3=overCurrentRMS_L3.trip_latch;

	faultWord.bit.oc_cs_L1=overCurrentCS_L1.trip_latch;
	faultWord.bit.oc_cs_L2=overCurrentCS_L2.trip_latch;
	faultWord.bit.oc_cs_L3=overCurrentCS_L3.trip_latch;
		
	faultWord.bit.oc_peak_L1=overCurrentPeak_L1.trip_latch;
	faultWord.bit.oc_peak_L2=overCurrentPeak_L2.trip_latch;
	faultWord.bit.oc_peak_L3=overCurrentPeak_L3.trip_latch;
	
	faultWord.bit.ov_dc=overVoltageDC.trip_latch;
	faultWord.bit.ov_ac=overVoltageAC.trip_latch;
	
	faultWord.bit.uv_dc=underVoltageDC.trip_latch;
	faultWord.bit.uv_ac=underVoltageAC.trip_latch;
	
	faultWord.bit.ntc1=overTempA.trip_latch;
	faultWord.bit.ntc2=overTempB.trip_latch;
	faultWord.bit.ntc3=overTempC.trip_latch;


		

}