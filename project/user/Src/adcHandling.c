#include "adcHandling.h"
#include "main.h"
#include "adc.h"
#include "tim.h"


uint64_t c1=0,c2=0;

#define ADCCONVERTEDVALUES_BUFFER_SIZE ((uint32_t)  4)    /* Size of array containing ADC converted values */
#define ADC3CONVERTEDVALUES_BUFFER_SIZE ((uint32_t)  4)    /* Size of array containing ADC converted values */

/* Private macro -------------------------------------------------------------*/

/**
  * @brief  Computation of ADC master conversion result 
  *         from ADC dual mode conversion result (ADC master and ADC slave
  *         results concatenated on data register of ADC master).
  * @param  DATA: ADC dual mode conversion result
  * @retval None
  */
#define COMPUTATION_DUALMODEINTERLEAVED_ADCMASTER_RESULT(DATA)                 \
  ((DATA) & 0x0000FFFF)

/**
  * @brief  Computation of ADC slave conversion result 
  *         from ADC dual mode conversion result (ADC master and ADC slave
  *         results concatenated on data register of ADC master).
  * @param  DATA: ADC dual mode conversion result
  * @retval None
  */
#define COMPUTATION_DUALMODEINTERLEAVED_ADCSLAVE_RESULT(DATA)                  \
  ((DATA) >> 16)

ALIGN_32BYTES(volatile uint32_t   aADCDualConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE]);    /* ADC dual mode interleaved conversion results (ADC master and ADC slave results concatenated on data register 32 bits of ADC master). */
ALIGN_32BYTES(volatile uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE]);       /* For the purpose of this example, dispatch dual conversion values into arrays corresponding to each ADC conversion values. */
ALIGN_32BYTES(volatile uint16_t   aADCyConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE]);       /* For the purpose of this example, dispatch dual conversion values into arrays corresponding to each ADC conversion values. */
ALIGN_32BYTES(static uint32_t   aADC3ConvertedData[ADC3CONVERTEDVALUES_BUFFER_SIZE]);


adcChannel_Type ch=ch_Van;
volatile adcData_Type adc={0};
adcData_Type scale={0};


void readAdc12(void);
void readAdc3(void);

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){
	

	
	if(hadc->Instance==ADC1){
		
		/* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer: 32 bytes */ 
  SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCDualConvertedValues[0], 4*ADCCONVERTEDVALUES_BUFFER_SIZE/2);	


  uint32_t tmp_index = 0;
  
  /* For the purpose of this example, dispatch dual conversion values         */
  /* into 2 arrays corresponding to each ADC conversion values.               */
  for (tmp_index = 0; tmp_index < (ADCCONVERTEDVALUES_BUFFER_SIZE/2); tmp_index++)
  {
    aADCxConvertedValues[tmp_index] = (uint16_t) COMPUTATION_DUALMODEINTERLEAVED_ADCMASTER_RESULT(aADCDualConvertedValues[tmp_index]);
    aADCyConvertedValues[tmp_index] = (uint16_t) COMPUTATION_DUALMODEINTERLEAVED_ADCSLAVE_RESULT(aADCDualConvertedValues[tmp_index]);
  }
	
	}
	
	if(hadc->Instance==ADC3){
		
		/* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer: 32 bytes */
  SCB_InvalidateDCache_by_Addr((uint32_t *) &aADC3ConvertedData[0], 2*ADC3CONVERTEDVALUES_BUFFER_SIZE);

	}
	


}



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	


	
	
	
	if(hadc->Instance==ADC1){
	
		/* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer: 32 bytes */ 
  SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCDualConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE/2], 4*ADCCONVERTEDVALUES_BUFFER_SIZE/2);
  
  uint32_t tmp_index = 0;
  
  /* For the purpose of this example, dispatch dual conversion values         */
  /* into 2 arrays corresponding to each ADC conversion values.               */
  for (tmp_index = (ADCCONVERTEDVALUES_BUFFER_SIZE/2); tmp_index < ADCCONVERTEDVALUES_BUFFER_SIZE; tmp_index++)
  {
    aADCxConvertedValues[tmp_index] = (uint16_t) COMPUTATION_DUALMODEINTERLEAVED_ADCMASTER_RESULT(aADCDualConvertedValues[tmp_index]);
    aADCyConvertedValues[tmp_index] = (uint16_t) COMPUTATION_DUALMODEINTERLEAVED_ADCSLAVE_RESULT(aADCDualConvertedValues[tmp_index]);
  }

 
	//****
	
	
	readAdc12();
	HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,GPIO_PIN_SET);
	mainFlow();
	HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,GPIO_PIN_RESET);
	
	
	c1++;	
	
	
	
	}
	
	
	
	
	if(hadc->Instance==ADC3){
		
		/* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer: 32 bytes */
	SCB_InvalidateDCache_by_Addr((uint32_t *) &aADC3ConvertedData[ADC3CONVERTEDVALUES_BUFFER_SIZE/2], 2*ADC3CONVERTEDVALUES_BUFFER_SIZE);	
		

	readAdc3();	
	c2++;		
	
	}



}


void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc){
  /* Set variable to report analog watchdog out of window status to main      */
  /* program.                                                                 */
  if(hadc->Instance==ADC2){
	

	
	
	}
}
void initAdc(void){
	
	//****scalings start
	
	scale.ch.Van=1; //cau --neg sign
	scale.ch.Vbn=1;
	scale.ch.Vcn=1;
	scale.ch.Vdc=1;
	
	scale.ch.Ia=0.00621664*0.991; //cau not 3.3v , 3.27v act
	scale.ch.Ib=0.00621664;;
	scale.ch.Ic=0.00621664;;
	
	scale.ch.NTCa=1.65/32767.0;
	scale.ch.NTCb=1;
	scale.ch.NTCc=1;
	scale.ch.v5=1;
	
	//****scalings end

	



	if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK){
    /* Calibration Error */
    Error_Handler();
  }
	
	
	if (HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_DIFFERENTIAL_ENDED) != HAL_OK){
    /* Calibration Error */
    Error_Handler();
  }
	
	
	if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK){
    /* Calibration Error */
    Error_Handler();
  }
	
	
	
	
	/* Start TIM2*/
	HAL_TIM_Base_Start_IT(&htim2);
  /* Start ADCx and ADCy multimode conversion on regular group with transfer by DMA */
  if (HAL_ADCEx_MultiModeStart_DMA(&hadc1,
                                   (uint32_t *)aADCDualConvertedValues,
                                    ADCCONVERTEDVALUES_BUFFER_SIZE
                                  ) != HAL_OK){
    /* Start Error */
    Error_Handler();
  }
	

	HAL_TIM_Base_Start_IT(&htim4);
	
	#if 1
	

	/* Start TIM4*/
	
  if (HAL_ADC_Start_DMA(&hadc3,
                        (uint32_t *)aADC3ConvertedData,
                        ADC3CONVERTEDVALUES_BUFFER_SIZE
                       ) != HAL_OK){
    Error_Handler();
  }
	
	#endif

}



void readAdc12(void){


	adc.ch.Van=scale.ch.Van*((double)aADCxConvertedValues[seq_Van]);
	adc.ch.Vbn=scale.ch.Vbn*((double)aADCxConvertedValues[seq_Vbn]);
	adc.ch.Vcn=scale.ch.Vcn*((double)aADCxConvertedValues[seq_Vcn]);
	adc.ch.Vdc=scale.ch.Vdc*((double)aADCxConvertedValues[seq_Vdc]);
	
	adc.ch.Ia=scale.ch.Ia*((double)aADCyConvertedValues[seq_Ia]-32768);
	adc.ch.Ib=scale.ch.Ib*((double)aADCyConvertedValues[seq_Ib]);
	adc.ch.Ic=scale.ch.Ic*((double)aADCyConvertedValues[seq_Ic]);
	
	
}


void readAdc3(void){


	adc.ch.NTCa=scale.ch.NTCa*((double)aADC3ConvertedData[seq_NTCa]);
	adc.ch.NTCb=scale.ch.NTCb*((double)aADC3ConvertedData[seq_NTCb]);
	adc.ch.NTCc=scale.ch.NTCc*((double)aADC3ConvertedData[seq_NTCc]);
	adc.ch.v5=scale.ch.v5*((double)aADC3ConvertedData[seq_v5]);



}
