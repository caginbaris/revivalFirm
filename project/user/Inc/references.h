#ifndef __references_h
#define __references_h


typedef struct reference{

double Q;
double I;	
	
double Vdc;
double Vdc_initial; 	
double Vdc_final; 
	
double dTermD;	
double dTermQ;	
	

}reference;


extern reference ref;


void references(void);

#endif


