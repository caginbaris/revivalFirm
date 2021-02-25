#ifndef __phaseLockedLoop_h
#define __phaseLockedLoop_h


typedef struct pll_parameters{

		double Vd;
		double Vdf;
		double Pout;
		double Iout;
	  double PIout;
		double out;
	
		double ts;	
		
}pll_parameters;


double PLL_theta (double Vpll,double Vrms , double theta,pll_parameters* pll);
void PLL_initialization(pll_parameters* pll, double ts);

#define PLL_THETA(Vpll,Vrms,theta,pll) theta=PLL_theta (Vpll,Vrms,theta,&pll)

#endif


