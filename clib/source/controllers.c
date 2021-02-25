
#include "clib.h"





void piControllerInitialization(piData* pi,piInit init){
	
	

	pi->parameter.Ki=init.parameter.Ki;
	pi->parameter.Kp=init.parameter.Kp;
	pi->parameter.ts=init.parameter.ts;
	
	pi->limit.refLimitUp=init.limit.refLimitUp;
	pi->limit.refLimitDown=init.limit.refLimitDown;
	
	pi->limit.antiWindUp_Up=init.limit.antiWindUp_Up;
	pi->limit.antiWindUp_Down=init.limit.antiWindUp_Down;
	
	pi->limit.outputLimitUp=init.limit.outputLimitUp;
	pi->limit.outputLimitDown=init.limit.outputLimitDown;
	
	pi->flag.refLimitEnable=init.flag.refLimitEnable;
	pi->flag.outputLimitEnable=init.flag.outputLimitEnable;
	pi->flag.feedBackReversal=init.flag.feedBackReversal;
	pi->flag.outputReversal=init.flag.outputReversal;

}


void piControllerImplementaiton(piData* pi){
	
double q=1.0;
	
if(pi->flag.enable){
	
	//reference limiting
	
	if(pi->flag.refLimitEnable){
		
	pi->flag.refLimiting=passive;
		
	if((pi->signal.ref)>(pi->limit.refLimitUp))  {(pi->signal.ref)=(pi->limit.refLimitUp)  ; (pi->flag.refLimiting)=active;}
	if((pi->signal.ref)<(pi->limit.refLimitDown)){(pi->signal.ref)=(pi->limit.refLimitDown); (pi->flag.refLimiting)=active;}		
	
	}

	//feedbback signal reversal
	
	if(pi->flag.feedBackReversal){pi->signal.feedback=-pi->signal.feedback;}

	//controller operation
	
	pi->state.error=((pi->signal.ref)-(pi->signal.feedback));
	
	pi->state.Pout=(pi->parameter.Kp)*(pi->state.error);
	
	//anti-windup
	
	q=1.0;
	
	if(pi->state.error>pi->limit.antiWindUp_Up)  {q=0.0f;}
	if(pi->state.error<pi->limit.antiWindUp_Down){q=0.0f;}
	
	pi->state.Iout+=(pi->parameter.ts)*(pi->parameter.Ki*q)*(pi->state.error);
	
	//integral limiting
	
		
	if((pi->state.Iout)>(pi->limit.outputLimitUp))  {(pi->state.Iout)=(pi->limit.outputLimitUp)  ;}
	if((pi->state.Iout)<(pi->limit.outputLimitDown)){(pi->state.Iout)=(pi->limit.outputLimitDown);}		
	
	
	//output calculation
	
	pi->signal.controllerOutput=(pi->state.Pout)+(pi->state.Iout);
	
	//output signal reversal
	
	if(pi->flag.outputReversal){pi->signal.controllerOutput=-pi->signal.controllerOutput;}
	
	//output limiting
	
	if(pi->flag.outputLimitEnable){
		
	pi->flag.outputLimiting=passive;
		
	if((pi->signal.controllerOutput)>(pi->limit.outputLimitUp))  {(pi->signal.controllerOutput)=(pi->limit.outputLimitUp)  ; (pi->flag.outputLimiting)=active;}
	if((pi->signal.controllerOutput)<(pi->limit.outputLimitDown)){(pi->signal.controllerOutput)=(pi->limit.outputLimitDown); (pi->flag.outputLimiting)=active;}		
	
	}
	
	}else{
		
  pi->state.Iout=pi->signal.atRestOutput;
	pi->signal.controllerOutput=pi->signal.atRestOutput;

 }
}


