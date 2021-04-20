#include "mlib.h"
#include "plib.h"
#include "adcHandling.h"
#include "main.h"


double fSignal=0,fundamentalFrequency=0;

static double coeffs[5]={0.001881411443387,0,-0.001881411443387,-1.996193044584017,0.996237177113225};
static sos_parameters bp={0};
static delay_parameters p={0,100,0};
static transition_parameters t={0,0};


static uint32_t pulseCount=0;


//cau only for single invocation

void frequency(double input,double *output,double samplingFrequency){



    on_off_delay(input>0,&p);
	
		low2highTransition(p.output, &t);
		
	
		if(t.output || pulseCount>2000){

			if(pulseCount!=0){
				
				*output=samplingFrequency/((double)(pulseCount));
				
				}
			
				pulseCount=0;
			}	
			

		pulseCount++;
 

}


void frequencyMeasurement(void){


fSignal=sos_implementation(adc.ch.Ia ,fSignal,coeffs, &bp);
frequency(fSignal,&fundamentalFrequency,50000.0);
	

}

