

#include "pllHandling.h"
#include "main.h"

#define _pi 3.14159

void pllTest(void){

	
	if(pll.theta_comp >0 && pll.theta_comp<_pi){
	
		HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,(GPIO_PinState)1);
	
	}else{
	
		HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,(GPIO_PinState)0);
		
	}
	
	
	//HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);


}