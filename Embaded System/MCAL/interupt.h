#ifndef INTERUPT_INTERFACE_H
#define INTERUPT_INTERFACE_H
#include "STD_TYPES.h"

#include "GPIO_REG.h"
#include"GPIO_INTERFACE.h"




#define INT_0          0
#define INT_1          1

#define LOW_LEVEL      0
#define ANY_CHANGE     1
#define FALLING_EDGE   2
#define RISING_EDGE    3


void EXT_INT0_Init(u8 sense);
void EXT_INT1_Init(u8 sense);

void EXT_INT0_Enable(void);
void EXT_INT1_Enable(void);

void EXT_INT0_SetCallback(void (*ptr)(void));
void EXT_INT1_SetCallback(void (*ptr)(void));

void EXT_INT_GlobalEnable(void);
void EXT_INT_GlobalDisable(void);

#endif
