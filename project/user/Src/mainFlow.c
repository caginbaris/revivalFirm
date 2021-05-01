#include "main.h"
#include "mlib.h"
#include "plib.h"
#include "adcHandling.h"
#include "tim.h"
#include "pwmGeneration.h"
#include "testBenches.h"
#include "measurement.h"
#include "LEDs.h"
#include "ios.h"

#define samplinfFrequency 50000

uint32_t cycleCount;
double cpuLoading;


delay_parameters mainFlowSecondCounter={0,samplinfFrequency,0};



void mainFlow(void){
	

	
	
	  // mainflow function start 
		cycleCount=htim2.Instance->CNT;
		
		

		
		//frequencyMeasurement();
		rmsMeasurement();
		ios();
		switchingTest();

		
		fToggle(1,&mainFlowSecondCounter); 
		
		
		cycleCount=htim2.Instance->CNT-cycleCount;
		cpuLoading=100.0*(double)(cycleCount)/(double)(htim2.Init.Period);
		
		
		// mainflow function end


}