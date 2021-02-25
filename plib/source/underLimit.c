
#include "plib.h"


void underLimitInitialization(underLimit_inputParameters *in,underLimit_inputParameters init, underLimit_outputParameters out){

	
	if( ( init.level>0.0f) &&
			( init.delay>0.0f) &&
			( (init.dropout_ratio>1.0f) && (init.dropout_ratio<=10.0f)) &&
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


void underLimit(float rms,underLimit_inputParameters underLimit_in, underLimit_outputParameters *underLimit_out,uint8_t inhibit,uint8_t reset)
{
	
	if (underLimit_in.enable){
		
		if (rms < underLimit_in.level)
		{
			underLimit_out->initial_pick_up = 1;
		}
		
		if (rms > (underLimit_in.level * underLimit_in.dropout_ratio) || inhibit==1)
		{
			underLimit_out->initial_pick_up = 0;
		}
		
		
		underLimit_out->pick_up 				=off_delay(		underLimit_out->initial_pick_up,
																									underLimit_out->pick_up, 
																									(uint32_t)(underLimit_in.dropout_time *underLimit_in.fs),
																									&(underLimit_out->dropout_counter));
		
		underLimit_out->comm_pick_up		=on_off_delay2(	underLimit_out->initial_pick_up,
																									underLimit_out->comm_pick_up,
																									(uint32_t)(underLimit_in.comm_pick_on_delay*underLimit_in.fs),
																									(uint32_t)(underLimit_in.comm_pick_off_delay*underLimit_in.fs),	
																									&(underLimit_out->comm_pick_counter));

		
		underLimit_out->trip   			 	=on_delay (			underLimit_out->pick_up, 
																									underLimit_out->trip, 
																									underLimit_in.delay * underLimit_in.fs,
																									&(underLimit_out->trip_counter));
		

		if (underLimit_out->trip == 1)
		{
			underLimit_out->trip_latch = 1;
		}
		
		
		
		
		if(underLimit_out->initial_pick_up==0 && reset==1){
		
			underLimit_out->trip_latch=0;
		
		}
		
	}
		
}
