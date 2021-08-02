#include "references.h"
#include "controlRoutines.h"
#include "measurement.h"

#define dc2ac 0.612 // no 3rd
#define idc2ac (1.0/dc2ac) 
#define Lvalue 0.001
#define Xvalue (Lvalue*2*3.14159*50)
#define ratedCurrent 10.0
#define requiredVoltage (ratedCurrent*Xvalue)
#define sqrt3 1.732050807568877


reference ref={0};

static double ref_iz=0,ref_fz=0,Vdf=1.0,Vdz=0;

static double fofCoefficents1e0[2]={

0.0000628279055607806,
-0.999874344188878

};
	
void init_references(void){


ref.Vdc=560;
ref.Vdc_initial=560;
ref.Vdc_final=560;	
	
ref.Q=0;
ref.I=0;		
ref.dTermD=0;
ref.dTermQ=0;


}	
	

void references(void){
	
	
	FOF(pV.d,Vdz,Vdf,fofCoefficents1e2);
	
	ref.I = (Vdf > 10.0) ? ref.Q/Vdf : ref.I;
	
	//FOF((tRMS[rms_Vab].out*1.414),ref_iz,ref.Vdc_initial,fofCoefficents1e0);
	//FOF((tRMS[rms_Van].out+requiredVoltage)*sqrt3*idc2ac,ref_fz,ref.Vdc_final,fofCoefficents1e0);
	
	//cau decoupling terms should be added
								
	

}