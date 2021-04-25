#include "main.h"
#include "ios.h"
#include "plib.h"

#define inputNo 13
#define inputDelayFs 50000.0
#define inputDelayTime 0.1
#define inputDelayQualSample (int)(inputDelayFs*inputDelayTime)

digitalInputs DI={0};
digitalOutputs DO={0};


void ios(void){

//input parameter initialization
//init seq={output,qualSample,count}
	
static delay_parameters inputDelay[inputNo]={

{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0},
{0,inputDelayQualSample,0}

};
	
//inputs

on_off_delay(HAL_GPIO_ReadPin(HB1_FLT_GPIO_Port,HB1_FLT_Pin),&inputDelay[0]);
on_off_delay(HAL_GPIO_ReadPin(HB2_FLT_GPIO_Port,HB2_FLT_Pin),&inputDelay[1]);
on_off_delay(HAL_GPIO_ReadPin(HB3_FLT_GPIO_Port,HB3_FLT_Pin),&inputDelay[2]);

on_off_delay(HAL_GPIO_ReadPin(PWRGD_3v3_GPIO_Port,PWRGD_3v3_Pin),&inputDelay[3]);
on_off_delay(HAL_GPIO_ReadPin(PWRGD_24v_GPIO_Port,PWRGD_24v_Pin),&inputDelay[4]);
on_off_delay(HAL_GPIO_ReadPin(extInput_GPIO_Port,extInput_Pin),&inputDelay[5]);

on_off_delay(HAL_GPIO_ReadPin(MCB_in_check_GPIO_Port,MCB_in_check_Pin),&inputDelay[6]);
on_off_delay(HAL_GPIO_ReadPin(PBin_GPIO_Port,PBin_Pin),&inputDelay[7]);

on_off_delay(HAL_GPIO_ReadPin(HB1pIn_GPIO_Port,HB1pIn_Pin),&inputDelay[8]);
on_off_delay(HAL_GPIO_ReadPin(HB2pIn_GPIO_Port,HB2pIn_Pin),&inputDelay[9]);
on_off_delay(HAL_GPIO_ReadPin(HB3pIn_GPIO_Port,HB3pIn_Pin),&inputDelay[10]);

on_off_delay(HAL_GPIO_ReadPin(HB1nIn_GPIO_Port,HB1nIn_Pin),&inputDelay[11]);
on_off_delay(HAL_GPIO_ReadPin(HB2nIn_GPIO_Port,HB2nIn_Pin),&inputDelay[12]);
on_off_delay(HAL_GPIO_ReadPin(HB3nIn_GPIO_Port,HB3nIn_Pin),&inputDelay[13]);

//cau comparator outputs stiil waiting


//outputs

HAL_GPIO_WritePin(extOutputREL_GPIO_Port,extOutputREL_Pin,(GPIO_PinState)DO.bit.ext_REL);
HAL_GPIO_WritePin(extOutputSSR_GPIO_Port,extOutputSSR_Pin,(GPIO_PinState)DO.bit.ext_SSR);
HAL_GPIO_WritePin(HB_RST_GPIO_Port,HB_RST_Pin,(GPIO_PinState)DO.bit.rst);


HAL_GPIO_WritePin(MCB_in_GPIO_Port,MCB_in_Pin,(GPIO_PinState)DO.bit.mcb_in);


DI.bit.hb1_fault=inputDelay[0].output;


};


	
	


