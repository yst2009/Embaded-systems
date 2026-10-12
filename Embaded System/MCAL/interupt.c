#include "GPIO_REG.h"
#include "GPIO_INTERFACE.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <avr/interrupt.h> // ???? ?????? ??? ISR ???????
#include "interupt.h"
#include <stddef.h>          // ??? ???? ??? NULL
#define ISC00_BIT GPIO_PIN0
#define ISC01_BIT GPIO_PIN1
#define INT0_BIT GPIO_PIN0
/* Pointer ??? Callback ???? ???? ??? ISR ???? Application */
static void (*EXT_INT0_Callback)(void) = NULL;

void EXT_INT0_Init(u8 sense) {
    /* 1. ??? ???? ?? Input (???????? ??? GPIO driver ?????) */
    switch (sense) {
        case LOW_LEVEL:
            CLR_BIT(EICRA, ISC00_BIT);
            CLR_BIT(EICRA, ISC01_BIT);
            break;
        case ANY_CHANGE:
            SET_BIT(EICRA, ISC00_BIT);
            CLR_BIT(EICRA, ISC01_BIT);
            break;
        case FALLING_EDGE:
            CLR_BIT(EICRA, ISC00_BIT);
            SET_BIT(EICRA, ISC01_BIT);
            break;
        case RISING_EDGE:
            SET_BIT(EICRA, ISC00_BIT);
            SET_BIT(EICRA, ISC01_BIT);
            break;
        default:
            break;
    }
}



void EXT_INT0_Enable(void) {
    SET_BIT(EIMSK, INT0_BIT);
}

void EXT_INT_GlobalEnable(void) {
    SET_BIT(SREG, GPIO_PIN7);
}

void EXT_INT0_SetCallback(void (*ptr)(void)) {
    EXT_INT0_Callback = ptr;
}

/* ??? ISR ???????? ???? ?????? ??? Callback */
ISR(INT0_vect) {
    if (EXT_INT0_Callback != NULL) {
        EXT_INT0_Callback();
    }
}