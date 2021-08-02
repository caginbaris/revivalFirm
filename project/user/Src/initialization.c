#include "initialization.h"
#include "pwmGeneration.h" 	

void initialization(void){

initAdc();
initDac();	
initComp();
	
overCurrentInit();
voltageProtectionsInit();
ntcProtectionsInit();
	
initControlRoutines();
	
modulatorDisable();


}


