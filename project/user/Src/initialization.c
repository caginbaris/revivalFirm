#include "initialization.h"


void initialization(void){

initAdc();
initDac();	
initComp();
	
overCurrentInit();
voltageProtectionsInit();
ntcProtectionsInit();
	
initControlRoutines(); 	

}


