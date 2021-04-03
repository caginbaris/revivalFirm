#ifndef __adcHandling_H
#define __adcHandling_H

typedef enum adcSeq_Type {  seq_Van=0,
                            seq_Vbn=1,
                            seq_Vcn=2,  
                            seq_Vdc=3,
                            seq_Ia=0,  
                            seq_Ib=1,
                            seq_Ic=2,
  
                            seq_NTCa=0,
                            seq_NTCb=1,  
                            seq_NTCc=2,
	
                            seq_v5=3,
                            seq_vTemp=4,
                        
}adcSeq_Type;



typedef enum adcChannel_Type {  ch_Van=0,
																ch_Vbn=1,
																ch_Vcn=2,  
																ch_Vdc=3,
																ch_Ia=4,  
																ch_Ib=5,
																ch_Ic=6,
  
																ch_NTCa=7,
																ch_NTCb=8,  
																ch_NTCc=9,
	
																ch_v5=10,
																ch_vTemp=11,
                        
}adcChannel_Type;


typedef union adcData_Type{

	struct{
		
		double Van;
		double Vbn;
		double Vcn;
		
		double Vdc;
		
		double Ia;
		double Ib;
		double Ic;
		
		double NTCa;
		double NTCb;
		double NTCc;
		double v5;
		double vTemp;
		

	}ch;
	
	
	double all[12];

}adcData_Type;


extern adcData_Type adc;

#endif


