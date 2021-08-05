#ifndef __initialization_H__
#define __initialization_H__

void initAdc(void);
void initDac(void);
void initComp(void);

void overCurrentInit(void);
void voltageProtectionsInit(void);
void ntcProtectionsInit(void);

void initControlRoutines(void);
void init_references(void);

void initialization(void);


#endif