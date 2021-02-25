
#include "mlib.h"


// True RMS half cycle
// delayLineArray contains full period circular data of input
// delayLineCounter global counter for true rms calculation
// length of delayLineArray - mult. inverse can be u

double trueRMS(double rtInput, double *delayLineArray, uint16_t delayLineCounter, uint16_t arrayLength){

	uint16_t i=0;
	double rms = 0.0, rms_sum = 0.0, rms_data=0.0;

	*(delayLineArray+delayLineCounter) = rtInput;

	for (i = 0; i < arrayLength; i++)
	{

		rms_data=*delayLineArray ++;
		rms_sum+=rms_data*rms_data;
		
	}

	rms = sqrt(rms_sum / arrayLength);

	return rms;

}

