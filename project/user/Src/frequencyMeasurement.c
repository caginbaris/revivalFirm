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

void frequencyMeasurement(double input,double *output,double samplingFrequency){



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


void frequency(void){


fSignal=sos_implementation(adc.ch.Ia ,fSignal,coeffs, &bp);
frequencyMeasurement(fSignal,&fundamentalFrequency,50000.0);
	
if(fundamentalFrequency>40.0)	{

	HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_SET);

}else{


	HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);

}


}

