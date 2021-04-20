#include "stm32h7xx_hal.h"
#include "tim.h"
#include "pwmGeneration.h"
#include "plib.h"





uint16_t sw_count_a=300;
uint16_t sw_count_b=600;
uint16_t sw_count_c=600;



void modulatorDisable(void){

	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
	
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
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
	
	/*
	sw_count_a=wscale*(final.a+ref.Vdc*0.5)/ref.Vdc;
	sw_count_b=wscale*(final.b+ref.Vdc*0.5)/ref.Vdc;
	sw_count_c=wscale*(final.c+ref.Vdc*0.5)/ref.Vdc;
	*/
	
	ui_LIMITER(sw_count_a,0,wscale);
	ui_LIMITER(sw_count_b,0,wscale);
	ui_LIMITER(sw_count_c,0,wscale);
	
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, sw_count_a);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, sw_count_b);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3, sw_count_c);	
	
	
}


