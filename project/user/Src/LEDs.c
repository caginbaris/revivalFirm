#include "main.h"
#include "mainFlow.h"
#include "ios.h"

uint8_t firingStarted=0;


void LEDs(void){

HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,(GPIO_PinState)mainFlowSecondCounter.output);

HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,(GPIO_PinState)firingStarted);

firingStarted=0;
	
	
if(DI.bit.hb1_fault==0){

	HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,(GPIO_PinState)1);
	
}else{

	HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,(GPIO_PinState)0);

}	
	
// HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,(GPIO_PinState)1);	

}


