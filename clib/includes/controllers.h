#ifndef __controllers_h
#define __controllers_h

#include <stdint.h>

typedef struct piInit{
	
	struct{
		
		double Kp;
		double Ki;
		double ts;
		double atRest;

	}parameter;


	struct{
		
		double refLimitUp;
		double refLimitDown;
		
		double antiWindUp_Up;
		double antiWindUp_Down;
		
		double outputLimitUp;
		double outputLimitDown;

	}limit;
	
	
	struct{
		
		
		uint32_t refLimitEnable:1;
		uint32_t outputLimitEnable:1;

		uint32_t feedBackReversal:1;
		uint32_t outputReversal:1;
		
		uint32_t rem:28;
		
	}flag;


}piInit;



typedef struct piData{

	struct{	

		double ref;
		double feedback;	
		double controllerOutput;
		double atRestOutput;

	}signal;

	struct{
		
		double error;
		double Pout;
		double Iout;

	}state;


	struct{
		
		double Kp;
		double Ki;
		double ts;

	}parameter;


	struct{
		
		double refLimitUp;
		double refLimitDown;
		
		double antiWindUp_Up;
		double antiWindUp_Down;
		
		double outputLimitUp;
		double outputLimitDown;

	}limit;
	

	struct{
		
		uint32_t enable:1;
		
		uint32_t refLimitEnable:1;
		uint32_t outputLimitEnable:1;
		
		uint32_t outputLimiting:1;
		uint32_t refLimiting:1;

		
		uint32_t feedBackReversal:1;
		uint32_t outputReversal:1;
		uint32_t rem:25;
		
	}flag;


}piData;



void piControllerInitialization(piData* pi,piInit init);
void piControllerImplementaiton(piData* pi);





#endif


