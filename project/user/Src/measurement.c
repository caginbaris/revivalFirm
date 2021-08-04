
#include "measurement.h"

uint16_t calculationCounter=0;


void measurement(void){
	
if(++calculationCounter==10000){calculationCounter=0;}	

frequencyMeasurement();
rmsMeasurement();
csMeasurement();
dcMeasurement();
ntcMeasurements();
	
	



}