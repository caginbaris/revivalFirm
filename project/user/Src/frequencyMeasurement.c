#include "mlib.h"
#include "plib.h"
#include "adcHandling.h"
#include "main.h"
#include "faultHandling.h"

double fundamentalFrequency=0;
static delay_parameters p={0,100,0};
static delay_parameters freqCheck={0,4000,0};
static transition_parameters t={0,0};


static uint32_t pulseCount=0;


void frequencyDetect(double input,double *output,double samplingFrequency){



    on_off_delay(input>0,&p);
	
		low2highTransition(p.output, &t);
		
	
		if(t.output || pulseCount>20000){

			if(pulseCount!=0){
				
				*output=samplingFrequency/((double)(pulseCount));
				
				}
			
				pulseCount=0;
			}	
			

		pulseCount++;
 

}


void frequencyMeasurement(void){

	frequencyDetect(adc.ch.Van,&fundamentalFrequency,50000.0);
	on_delay((fundamentalFrequency<48.0 || fundamentalFrequency>52.0),&freqCheck);
	
	if(freqCheck.output){faultWord.bit.gridFrequency=1;}
	

}

