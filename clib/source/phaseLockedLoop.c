
#include "clib.h"


#define fo_lp_a 0.997489878867098 //fc=20 for 50e3
#define fo_lp_b 0.001255060566451 //fs/2=>fc/2

#define Kp 100.0
#define Ki 100.0

#define _2pi 6.283185307179586476925286766559
#define wt (_2pi*50.0)


void PLL_initialization(pll_parameters* pll, double ts){

	pll->ts=ts;

}


double PLL_theta (double Vpll,double Vrms , double theta,pll_parameters* pll){

	double Vd_pll;

	Vd_pll=(Vrms>1.0)?(Vpll*cos(theta)/Vrms):(0.0);
	 
	
	pll->Vdf=pll->Vdf*(fo_lp_a)+(Vd_pll + pll->Vd)*fo_lp_b;
	pll->Vd=Vd_pll;
	
	pll->Pout =pll->Vdf*Kp;
	pll->Iout+=pll->ts*pll->Vdf*Ki;
	pll->PIout=pll->Pout+pll->Iout;

	if(pll->Iout>wt){pll->Iout = wt;}
	if(pll->Iout<-wt){pll->Iout = -wt;}
		
	pll->out+=(pll->PIout+wt)*pll->ts;
	
	if(pll->out>_2pi){pll->out   -= _2pi;}
	if(pll->out<0.0)   {pll->out += _2pi;}

	return pll->out;

}


