
#include "clib.h"
#include "mlib.h"
#include "plib.h"
#include "measurement.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "testBenches.h"

pll_parameters pll={0};

static delay_parameters syncCheck={0,2000,0};
static delay_parameters startupTimeout={0,100000,0};

static double fofCoefficents5em1[2]={

0.999968585060383,
-0.999937170120766

};



void pllHandling(void){
	
	
		pll_parameters resetPLL={0};
	
		static double vf=0,vz=0;
	
		FOF(adc.ch.Van,vz,vf,fofCoefficents5em1); 
		vz=-vz; // for hp handling
		
		
		on_delay(1,&startupTimeout);
		
		if(startupTimeout.output){
			
			

			if(tRMS[rms_Van].out>5.0){ 

				PLL(0.8*0.707*vf/tRMS[rms_Van].out,&pll);
				
			}else{
			
			pll=resetPLL;
			
			}
			
			//pllTest();

			on_delay(pll.qf<0.5,&syncCheck);
			
			if(syncCheck.output){faultWord.bit.synchronization=1;}
		
	}else{
	
	
		pll=resetPLL;
	
	}
		

}