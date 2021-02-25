
#include "clib.h"

void clarkeParkTransform(phase x, clarke* c, park* p ,double theta){
	
	c->alpha=sqrt_2over3_*(x.a-i2*(x.b+x.c));
	c->beta =sqrt_1over2_*(x.b-x.c);
	
	p->d=c->alpha*sin(theta)-c->beta*cos(theta);
	p->q=c->alpha*cos(theta)+c->beta*sin(theta);
	
}



void inverseClarkeParkTransform(park p, clarke* c, phase* x ,double theta){
	
	c->alpha =  sin(theta)*p.d +cos(theta)*p.q;
	c->beta  = -cos(theta)*p.d +sin(theta)*p.q;

	x->a  =  sqrt_2over3_ *c->alpha;
	x->b  = -sqrt_2over12_*c->alpha + sqrt_1over2_*c->beta;
	x->c  = -sqrt_2over12_*c->alpha - sqrt_1over2_*c->beta;
	
}



