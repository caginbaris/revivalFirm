#ifndef __ios_h
#define __ios_h

#include <stdint.h>


typedef union digitalInputs{
	
	struct{
	

		uint32_t pwrgd_3v3:1;
		uint32_t pwrgd_24v:1;
		uint32_t ext_input:1;
		uint32_t mcb_in_check:1;
		uint32_t pb_in:1;
		uint32_t modbus_enable:1;
		uint32_t hb1_fault:1;
		uint32_t hb2_fault:1;
		uint32_t hb3_fault:1;
		uint32_t hb1p_firing:1;
		uint32_t hb2p_firing:1;
		uint32_t hb3p_firing:1;
		uint32_t hb1n_firing:1;
		uint32_t hb2n_firing:1;
		uint32_t hb3n_firing:1;
		
		
		uint32_t rem:17;

	}bit;
	
	uint32_t all;
	
}digitalInputs; 


typedef union digitalOutputs{
	
	struct{
	
		uint32_t LD1:1;
		uint32_t LD2:1;
		uint32_t LD3:1;
		uint32_t rst:1;
		uint32_t mcb_in:1;
		uint32_t ext_SSR:1;
		uint32_t ext_REL:1;
		uint32_t hold_eeprom:1;
		uint32_t cs_eeprom:1;
		
		uint32_t rem2:23;

	}bit;
	
	
	uint32_t all;
	

}digitalOutputs; 


extern digitalInputs input;
extern digitalOutputs output;



void ios(void);




#endif





