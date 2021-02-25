
#ifndef __overLimit_h
#define __overLimit_h

#include <stdint.h>

typedef struct overLimit_inputParameters {

	float level;
	float delay;
	float dropout_ratio;
	float dropout_time;
	float comm_pick_on_delay;
	float comm_pick_off_delay;
	
	uint32_t enable:1;
	uint32_t init_error:1;
	uint32_t fs:30;

}overLimit_inputParameters;

typedef struct overLimit_outputParameters {

	uint32_t trip_counter;
	uint32_t dropout_counter;
	uint32_t comm_pick_counter;


	uint32_t initial_pick_up:1;
	uint32_t pick_up:1;
	uint32_t comm_pick_up:1;
	uint32_t trip:1;
	uint32_t trip_latch:1;
	uint32_t rem:27;
	

}overLimit_outputParameters;


void overLimitInitialization(overLimit_inputParameters *in,overLimit_inputParameters init,overLimit_outputParameters out);
void overLimit(float rms,overLimit_inputParameters overLimit_in, overLimit_outputParameters *overLimit_out,uint8_t inhibit,uint8_t reset);



#endif


