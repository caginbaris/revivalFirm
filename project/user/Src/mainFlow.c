#include "main.h"
#include "mlib.h"
#include "plib.h"
#include "adcHandling.h"
#include "tim.h"
#include "pwmGeneration.h"
#include "testBenches.h"
#include "measurement.h"
#include "protection.h"
#include "LEDs.h"
#include "ios.h"
#include "states.h"
#include "faultHandling.h"
#include "pllHandling.h"

#define samplinfFrequency 50000

int32_t cycleCount;
double cpuLoading;


delay_parameters mainFlowSecondCounter={0,samplinfFrequency,0};

void controlRoutines(void);

void mainFlow(void){
	

	
	
	  // mainflow function start 
		cycleCount=htim2.Instance->CNT;
		
		
		//state_chart();
	
		measurement();
		pllHandling();
		protection();
	
		faultHandling();
	
		

		controlRoutines();
		
		ios();
		
		fToggle(1,&mainFlowSecondCounter);
		LED.out._1=mainFlowSecondCounter.output;
		
		
		cycleCount=htim2.Instance->CNT-cycleCount;
		cpuLoading=100.0*(double)(cycleCount)/(double)(htim2.Init.Period);
		
		
		// mainflow function end


}