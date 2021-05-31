#ifndef __controlRoutines_h
#define __controlRoutines_h

#include "clib.h"



extern pll_parameters pll;
extern phase V,I;
extern clarke cV,cI;
extern park  pV,pI;
extern double theta;

extern phase  cOut,final;

extern piInit pidInit,piqInit,pidcInit;
extern piData pidf,piqf,pidcf;



#endif


