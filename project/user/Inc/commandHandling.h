#ifndef __commandHandling_H__
#define __commandHandling_H__

#include <stdint.h>

typedef union commandInputs{
	
	struct{
	
		uint8_t start:1;
		uint8_t stop:1;
		uint8_t rem:6;
		
	}bit;
	
	uint8_t all;
	
}commandInputs; 

extern commandInputs command;

void commandHandling(void);


#endif
