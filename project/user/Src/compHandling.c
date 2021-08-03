#include "main.h"
#include "comp.h"
#include "faultHandling.h"

void initComp(void){


  /* Start COMP1 */
  if(HAL_COMP_Start_IT(&hcomp1) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
	
	
	  /* Start COMP1 */
  if(HAL_COMP_Start_IT(&hcomp2) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }



}



void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp){
	
	
	if(hcomp->Instance==COMP1){
		
		
		//cau faultWord.bit.comp_vdc=1;
	
	
	}
	
	
	if(hcomp->Instance==COMP2){
		
		
		faultWord.bit.comp_v5=1;
	
	
	}


}