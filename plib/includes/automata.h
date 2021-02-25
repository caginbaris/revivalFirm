
#ifndef __automata_h
#define __automata_h

#include <stdint.h>

uint8_t on_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count);
uint8_t off_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count);
uint8_t on_off_delay (uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count);
uint8_t on_off_delay2(uint8_t input, uint8_t mem, uint32_t onSample,uint32_t offSample, uint32_t *count);
void pulseGen(uint32_t prd, uint32_t duty,uint8_t EN,uint8_t* out,uint8_t* latch,uint32_t* prdCount);
uint32_t fToggle(uint32_t out,uint32_t sample, uint32_t* tCount);


void f_limiter(float* parameter,float downLimit,float upLimit);
void d_limiter(double* parameter,double downLimit,double upLimit);


//macros

#define ON_DELAY(in,out,qual,count) 				out=on_delay(in,out,qual,&count)
#define OFF_DELAY(in,out,qual,count) 				out=off_delay(in,out,qual,&count)
#define ON_OFF_DELAY(in,out,qual,count) 		out=on_off_delay(in,out,qual,count)
#define ON_OFF_DELAY2(in,out,on,off,count)  out=on_off_delay2(in,out,on,off,&count)
#define fTOGGLE(out,qual,count)             out=fToggle(out,qual,&count);

#define f_LIMITER(x,down,up)								f_limiter(&x,down,up)
#define d_LIMITER(x,down,up)								d_limiter(&x,down,up)

#endif

