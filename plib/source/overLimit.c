#include "plib.h"


void overLimitInitialization(overLimit_inputParameters *in, overLimit_inputParameters init,overLimit_outputParameters out){

	
	if( ( init.level>0.0f) 					 				&&
			( init.delay>0.0f) 					 				&&
			( (init.dropout_ratio>0.0f)  				&& (init.dropout_ratio<=1.0f)) &&
			( (init.dropout_time >=0.0f) 				&& (init.dropout_time<=init.delay)) &&
			( (init.comm_pick_on_delay  >=0.0f) && (init.comm_pick_on_delay<=init.delay)) &&
			( init.comm_pick_off_delay >=0.0f ) &&
			( out.initial_pick_up==0 &&
				out.pick_up==0 &&
				out.comm_pick_up==0 &&
				out.trip==0 &&
	      out.trip_latch==0
			)
	
		){
		
			*(in)=init;
			in->init_error=0;
			
		}else{
		
			in->init_error=1;
		}
}


void overLimit(float rms,overLimit_inputParameters overLimit_in, overLimit_outputParameters *overLimit_out,uint8_t inhibit,uint8_t reset)
{
	
	if (overLimit_in.enable){
		
		if (rms > overLimit_in.level)
		{
			overLimit_out->initial_pick_up = 1;
		}
		
		if (rms < (overLimit_in.level * overLimit_in.dropout_ratio) || inhibit==1)
		{
			overLimit_out->initial_pick_up = 0;
		}
		
		
		overLimit_out->pick_up 				=off_delay(			overLimit_out->initial_pick_up,
																									overLimit_out->pick_up, 
																									(uint32_t)(overLimit_in.dropout_time *overLimit_in.fs),
																									&(overLimit_out->dropout_counter));
		
		overLimit_out->comm_pick_up		=on_off_delay2(	overLimit_out->initial_pick_up,
																									overLimit_out->comm_pick_up,
																									(uint32_t)(overLimit_in.comm_pick_on_delay*overLimit_in.fs),
																									(uint32_t)(overLimit_in.comm_pick_off_delay*overLimit_in.fs),	
																									&(overLimit_out->comm_pick_counter));

		
		overLimit_out->trip   			 	=on_delay (			overLimit_out->pick_up, 
																									overLimit_out->trip, 
																									overLimit_in.delay * overLimit_in.fs,
																									&(overLimit_out->trip_counter));
		

		if (overLimit_out->trip == 1)
		{
			overLimit_out->trip_latch = 1;
		}
		
		
		
		
		if(overLimit_out->initial_pick_up==0 && reset==1){
		
			overLimit_out->trip_latch=0;
		
		}
		
	}
		
}


