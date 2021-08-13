#ifndef __measurement_H__
#define __measurement_H__

#include "mlib.h"
#include "clib.h"


void frequencyMeasurement(void);
void rmsMeasurement(void);
void csMeasurement(void);
void dcMeasurement(void);
void ntcMeasurements(void);


typedef enum rmsChannel {   rms_Ia=0,
                            rms_Ib=1,
                            rms_Ic=2,
														rms_Van=3,
                            rms_Vbn=4,
                            rms_Vcn=5,
														rms_Vab=6,
                            rms_Vbc=7,
                            rms_Vca=8,
														rms_Vdc=9,
                            rms_V0=10,
														rms_V1=11,
	                          rms_V2=12,
														rms_I0=13,
														rms_I1=14,
	                          rms_I2=15

                       
}rmsChannel_Type;

extern rmsChannel_Type rmsSeq;
extern trueRMS_sampled_parameters tRMS[23];
extern phase_cs_out cs_Aout,cs_Bout,cs_Cout;
extern sym_out sym;
extern double dcRipple, dcAverage,Vdcf;
extern double fofCoefficents1e2[2];


typedef struct ntcVariables{
	

		double R1;
		double R2;
		double R3;

		double T1;
		double T2;
		double T3;		

	
}ntcVariables; 


extern ntcVariables ntcVar;

void measurement(void);

extern uint16_t calculationCounter;


typedef struct recordedVariables{
	

		double rec_rmsIa;
		double rec_rmsIb;
		double rec_rmsIc;
	
		double rec_csIa;
		double rec_csIb;
		double rec_csIc;
	
		double rec_Ia;
		double rec_Ib;
		double rec_Ic;
	
		double rec_mIa;
		double rec_mIb;
		double rec_mIc;

		double rec_rmsVa;
		double rec_rmsVb;
		double rec_rmsVc;
	
		double rec_Vdc;
		
		piData rec_pid;
		piData rec_piq;
		piData rec_pidc;
		
		park rec_pV;
		park rec_pI;
		
		phase rec_final;
		phase rec_cOut;
		
	
}recordedVariables; 

void recorder();

extern double meanValueIa;
extern double meanValueIb;
extern double meanValueIc;


extern piData pidf,piqf,pidcf;
extern park  pV,pI;
extern phase  cOut,final;

#endif