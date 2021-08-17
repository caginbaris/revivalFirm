#ifndef __references_h
#define __references_h


typedef struct reference{

double Q;
double I;	
double Iline;	
	

	
double Vdc;
double Vdc_opt; 	
double Vdc_final; 
	
double dTermD;	
double dTermQ;	
	

}reference;


extern reference ref;


void references(void);

#endif


