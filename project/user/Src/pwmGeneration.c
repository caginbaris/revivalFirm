#include "stm32h7xx_hal.h"
#include "tim.h"
#include "pwmGeneration.h"
#include "plib.h"
#include "controlRoutines.h"
#include "references.h"
#include "adcHandling.h"
#include "measurement.h"


uint16_t sw_count_a=wscale*0.5;
uint16_t sw_count_b=wscale*0.5;
uint16_t sw_count_c=wscale*0.5;



void modulatorDisable(void){

	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);


		
}


void modulatorEnable(void){

	
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
	

}


void modulator(void){
	
	
	//sw_count_a=wscale*(final.a+ref.Vdc*0.5)/ref.Vdc;
	//sw_count_b=wscale*(final.b+ref.Vdc*0.5)/ref.Vdc;
	//sw_count_c=wscale*(final.c+ref.Vdc*0.5)/ref.Vdc;
	
	
	//cau only for dummy check
	if(tRMS[3].out>1.0 && tRMS[4].out>1.0 && tRMS[5].out>1.0 ){
	
	sw_count_a=wscale*(adc.ch.Van/(tRMS[3].out*1.414)+1)*0.5;
	sw_count_b=wscale*(adc.ch.Vbn/(tRMS[4].out*1.414)+1)*0.5;
	sw_count_c=wscale*(adc.ch.Vcn/(tRMS[5].out*1.414)+1)*0.5;
	
	}
	
	ui_LIMITER(sw_count_a,0,wscale);
	ui_LIMITER(sw_count_b,0,wscale);
	ui_LIMITER(sw_count_c,0,wscale);
	
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, sw_count_a);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, sw_count_b);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3, sw_count_c);	
	
	
}


