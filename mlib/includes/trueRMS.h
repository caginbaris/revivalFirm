#ifndef __trueRMS_h
#define __trueRMS_h

#include <stdint.h>

double trueRMS_windowed(double rtInput, double *delayLineArray, uint16_t delayLineCounter, uint16_t arrayLength);

typedef struct trueRMS_sampled_parameters{

    double sum;
    double out;
    uint16_t  sequence;


}trueRMS_sampled_parameters;

#endif


