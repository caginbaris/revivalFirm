
#ifndef __underLimit_h
#define __underLimit_h

#include <stdint.h>

typedef struct underLimit_inputParameters {

	float level;
	float delay;
	float dropout_ratio;
	float dropout_time;
	float comm_pick_on_delay;
	float comm_pick_off_delay;
	
	uint32_t enable:1;
	uint32_t init_error:1;
	uint32_t fs:30;

}underLimit_inputParameters;

typedef struct underLimit_outputParameters {

	uint32_t trip_counter;
	uint32_t dropout_counter;
	uint32_t comm_pick_counter;


	uint32_t initial_pick_up:1;
	uint32_t pick_up:1;
	uint32_t comm_pick_up:1;
	uint32_t trip:1;
	uint32_t trip_latch:1;
	uint32_t rem:27;


}underLimit_outputParameters;

void underLimitInitialization(underLimit_inputParameters *in,underLimit_inputParameters init,underLimit_outputParameters out);
void underLimit(float rms,underLimit_inputParameters underLimit_in, underLimit_outputParameters *underLimit_out,uint8_t inhibit,uint8_t reset);



#endif


