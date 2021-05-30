#ifndef __measurement_H__
#define __measurement_H__

#include "mlib.h"
#include "clib.h"


void frequencyMeasurement(void);
void rmsMeasurement(void);



typedef enum rmsChannel {   rms_Ia=0,
                            rms_Ib=1,
                            rms_Ic=2,
														rms_Van=3,
                            rms_Vbn=4,
                            rms_Vcn=5,
														rms_Vab=6,
                            rms_Vbc=7,
                            rms_Vca=8,
														rms_Vdc=9

                       
}rmsChannel_Type;

extern rmsChannel_Type rmsSeq;
extern trueRMS_sampled_parameters tRMS[17];
extern pll_parameters pll;
extern phase_cs_out cs_Aout,cs_Bout,cs_Cout;
extern sym_out sym;
extern double dcRipple, dcAverage,Vdcf;
extern double fofCoefficents1e2[2];

#endif