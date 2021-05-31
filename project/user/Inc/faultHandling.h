#ifndef __faultHandling_H__
#define __faultHandling_H__

#include <stdint.h>

typedef union faultInputs{
	
	struct{
	

		uint32_t pwrgd_3v3:1;
		uint32_t pwrgd_v5:1;
		uint32_t pwrgd_24v:1;
		
		uint32_t hb1_fault:1;	
		uint32_t hb2_fault:1;
		uint32_t hb3_fault:1;
		
		uint32_t comp_vdc:1;
		uint32_t comp_v5:1;
		
		uint32_t oc_rms_L1:1;
		uint32_t oc_rms_L2:1; 
		uint32_t oc_rms_L3:1;

		uint32_t oc_cs_L1:1;
		uint32_t oc_cs_L2:1; 
		uint32_t oc_cs_L3:1;
		
		uint32_t oc_peak_L1:1;
		uint32_t oc_peak_L2:1; 
		uint32_t oc_peak_L3:1;
		
		uint32_t ov_dc:1;
		uint32_t ov_ac:1; 

		uint32_t uv_dc:1;
		uint32_t uv_ac:1; 

		uint32_t ntc1:1;
		uint32_t ntc2:1; 
		uint32_t ntc3:1;
		
		
		uint32_t charged_state_error:1;
		uint32_t idle_state_error:1;
		uint32_t run_state_error:1;
		
		uint32_t rem:4;

			

	}bit;
	
	uint32_t all;
	
}faultInputs; 

extern faultInputs faultWord;

void faultHandling(void);


#endif
