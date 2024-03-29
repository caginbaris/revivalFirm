#include "main.h"
#include "dac.h"

void initDac(void){
	
	
	
	  /*##-3- Set DAC Channel1 DHR register ######################################*/
  if (HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_8B_R, 150) != HAL_OK)
  {
    /* Setting value Error */
    Error_Handler();
  }

	
	  /*##-3- Set DAC Channel1 DHR register ######################################*/
  if (HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_8B_R, 184) != HAL_OK)
  {
    /* Setting value Error */
    Error_Handler();
  }

	
	
	  /*## Enable DAC Channel1 ################################################*/
  if (HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
	
	
	  /*## Enable DAC Channel1 ################################################*/
  if (HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }




	




}