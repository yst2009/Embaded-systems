#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H
#include "std_types.h"
#define ADC_REF_AREF 0
#define ADC_REF_AVCC 1
#define ADC_INTERNAL_REF 2 //1.1
#define ADC_PRESCALER_32 5 
#define ADC_PRESCALER_64 6 
#define ADC_PRESCALER_128 7
#define ADC_PRESCALER_2     1
#define ADC_PRESCALER_4     2
#define ADC_PRESCALER_8     3
#define ADC_PRESCALER_16    4
#define ADC_RESOLUTION_8BIT 0
#define ADC_RESOLUTION_10BIT 1
#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 5
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7


void Vid_ADC_Init(u8 Copy_u8Ref, u8 Copy_u8Prescaler, u8 Copy_u8Resolution);
u16 U16_ADC_Read(u8 Copy_u8Channel);
u8 U8_ADC_Read(u8 Copy_u8Channel);
void ADC_VidEnableInterrupt(void);
void ADC_VidDisableInterrupt(void);
void ADC_VidSetCallBack(void (*Copy_Ptr)(void));

#endif 
