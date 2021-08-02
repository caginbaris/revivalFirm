#ifndef __faultHandling_H__
#define __faultHandling_H__

#include <stdint.h>

typedef union faultInputs{
	
	struct{
	

		uint64_t pwrgd_3v3:1;
		uint64_t pwrgd_v5:1;
		uint64_t pwrgd_24v:1;
		
		uint64_t hb1_fault:1;	
		uint64_t hb2_fault:1;
		uint64_t hb3_fault:1;
		
		uint64_t comp_vdc:1;
		uint64_t comp_v5:1;
		
		uint64_t oc_rms_L1:1;
		uint64_t oc_rms_L2:1; 
		uint64_t oc_rms_L3:1;

		uint64_t oc_cs_L1:1;
		uint64_t oc_cs_L2:1; 
		uint64_t oc_cs_L3:1;
		
		uint64_t oc_peak_L1:1;
		uint64_t oc_peak_L2:1; 
		uint64_t oc_peak_L3:1;
		
		uint64_t ov_dc:1;
		uint64_t ov_ac:1; 

		uint64_t uv_dc:1;
		uint64_t uv_ac:1; 

		uint64_t ntc1:1;
		uint64_t ntc2:1; 
		uint64_t ntc3:1;
		
		uint64_t meanIa:1;
		uint64_t meanIb:1; 
		uint64_t meanIc:1;
		
		uint64_t dcRippleOverLimit:1;
		

		uint64_t charged_state_error:1;
		uint64_t idle_state_error:1;
		uint64_t run_state_error:1;
		
		uint64_t overCurrentProtectionInit:1;
		uint64_t voltageProtectionInit:1;
		uint64_t ntcProtectionInit:1;
		
		
		uint64_t synchronization:1;
		uint64_t analogWatchDogFired:1;
		uint64_t gridFrequency:1;


			

	}bit;
	
	uint64_t all;
	
}faultInputs; 

extern faultInputs faultWord;

void faultHandling(void);


#endif
