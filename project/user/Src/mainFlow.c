#include "main.h"
#include "mlib.h"
#include "adcHandling.h"

trueRMS_sampled_parameters rms1={0,0,1};
trueRMS_sampled_parameters rms2={0,0,2};
trueRMS_sampled_parameters rms3={0,0,3};
trueRMS_sampled_parameters rms4={0,0,4};
trueRMS_sampled_parameters rms5={0,0,5};
trueRMS_sampled_parameters rms6={0,0,6};

void frequency(void);

void mainFlow(void){
	
		static uint16_t periodCounter=0;
	
	
		if(HAL_GPIO_ReadPin(PWRGD_24v_GPIO_Port,PWRGD_24v_Pin) == 1){
	
			
		
		}
		
		
		if(++periodCounter==1000){periodCounter=0;}
		
		
		trueRMS_sampled(adc.ch.Ia,&rms1,periodCounter);
		trueRMS_sampled(adc.ch.Ia,&rms2,periodCounter);
		trueRMS_sampled(adc.ch.Ia,&rms3,periodCounter);


		frequency();



}