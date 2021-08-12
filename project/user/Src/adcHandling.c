#include "adcHandling.h"
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "opamp.h"
#include "faultHandling.h"


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
adcData_Type offset={0};


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
	
	mainFlow();
	
	
	

	
	
	
	}
	
	
	
	
	if(hadc->Instance==ADC3){
		
		/* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer: 32 bytes */
	SCB_InvalidateDCache_by_Addr((uint32_t *) &aADC3ConvertedData[ADC3CONVERTEDVALUES_BUFFER_SIZE/2], 2*ADC3CONVERTEDVALUES_BUFFER_SIZE);	
		
	readAdc3();	
	
	
	}



}


void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc){

  if(hadc->Instance==ADC2){
		
		faultWord.bit.analogWatchDogFired=1;
	
	}
}





void initAdc(void){
	
	//****scalings--offset start
	
	scale.ch.Van=-0.022456*0.5; 
	scale.ch.Vbn=-0.022456*0.5;
	scale.ch.Vcn=-0.022456*0.5;
	scale.ch.Vdc=0.0101201771031;
	
	scale.ch.Ia=-0.00606; 
	scale.ch.Ib=0.005959;
	scale.ch.Ic=0.006049;
	
	scale.ch.NTCa=1.65/32767.0;
	scale.ch.NTCb=1.65/32767.0;
	scale.ch.NTCc=1.65/32767.0;
	scale.ch.v5=0.0001;
	
	
	offset.ch.Van=32943; 
	offset.ch.Vbn=32817;
	offset.ch.Vcn=32820;
	offset.ch.Vdc=10;
	
	offset.ch.Ia=32780; 
	offset.ch.Ib=32730;
	offset.ch.Ic=32755;
	
	offset.ch.NTCa=0;
	offset.ch.NTCb=0;
	offset.ch.NTCc=0;
	offset.ch.v5=0;
	
	//****scalings offset end

	



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
	
	
	if(HAL_OPAMP_Start(&hopamp2)!=HAL_OK)
  {
    Error_Handler();
  }  
	
	
	
	
	#if 1
	
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
	
	#endif

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


	adc.ch.Van=scale.ch.Van*((double)aADCxConvertedValues[seq_Van]-offset.ch.Van);
	adc.ch.Vbn=scale.ch.Vbn*((double)aADCxConvertedValues[seq_Vbn]-offset.ch.Vbn);
	adc.ch.Vcn=scale.ch.Vcn*((double)aADCxConvertedValues[seq_Vcn]-offset.ch.Vcn);
	adc.ch.Vdc=scale.ch.Vdc*((double)aADCxConvertedValues[seq_Vdc]-offset.ch.Vdc);
	
	adc.ch.Ia=scale.ch.Ia*((double)aADCyConvertedValues[seq_Ia]-offset.ch.Ia);
	adc.ch.Ib=scale.ch.Ib*((double)aADCyConvertedValues[seq_Ib]-offset.ch.Ib);
	adc.ch.Ic=scale.ch.Ic*((double)aADCyConvertedValues[seq_Ic]-offset.ch.Ic);
	
	
}


void readAdc3(void){


	adc.ch.NTCa=scale.ch.NTCa*((double)aADC3ConvertedData[seq_NTCa]);
	adc.ch.NTCb=scale.ch.NTCb*((double)aADC3ConvertedData[seq_NTCb]);
	adc.ch.NTCc=scale.ch.NTCc*((double)aADC3ConvertedData[seq_NTCc]);
	adc.ch.v5=scale.ch.v5*((double)aADC3ConvertedData[seq_v5]);



}
