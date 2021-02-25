#include "plib.h"


uint8_t on_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count)
{

	uint8_t out;

	out = mem;

	if (input == 1 && mem == 0)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 1;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 0)
	{
		out = 0;
		*count = 0;
	}

	return out;

}
uint8_t off_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count)
{

	uint8_t out;

	out = mem;

	if (input == 0 && mem == 1)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 0;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 1)
	{
		out = 1;
		*count = 0;
	}

	return out;

}
uint8_t on_off_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count)
{

	uint8_t out;

	out = mem;

	if (input ^ mem)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = input;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	return out;

}


uint8_t on_off_delay2( uint8_t input,  uint8_t mem, uint32_t onSample,uint32_t offSample, uint32_t *count){


	uint8_t out;

	out = mem;

	if (input == 1 && mem == 0)
	{
		*count = *count + 1;

		if ((*count) == onSample)
		{
			out = 1;
		}

	}



	if (input == 0 && mem == 1)
	{
		*count = *count + 1;

		if ((*count) == offSample)
		{
			out = 0;
		}

	}


	if(!(input^out)){*count=0;}


	


	return out;



}


void pulseGen(uint32_t prd, uint32_t duty,uint8_t EN,uint8_t* out,uint8_t* latch,uint32_t* prdCount){


if(EN==1 && *latch==0){*out=1;*latch=1;}

if(*latch==1){(*prdCount)=(*prdCount)+1;}

if((*prdCount)>duty){*out=0;}

if((*prdCount)==prd){*latch=0;*prdCount=0;}

}



uint32_t fToggle(uint32_t out,uint32_t sample, uint32_t* tCount){

(*tCount)++;

if(*tCount==sample){out^=1;*tCount=0;}

return out;

}






void f_limiter(float* parameter,float downLimit,float upLimit){


	if((*parameter)<downLimit){*parameter=downLimit;}
	if((*parameter)>  upLimit){*parameter=  upLimit;}


}


void d_limiter(double* parameter,double downLimit,double upLimit){


	if((*parameter)<downLimit){*parameter=downLimit;}
	if((*parameter)>  upLimit){*parameter=  upLimit;}


}

