#include "timer_interface.h"
#include <stddef.h>          // ??? ???? ??? NULL

// ??? Macros ??? Registers (??????? ??? ?????? ?? ???? ?? ?? ???? ??? C)
#define TCCR0A  *((volatile u8*)0x44)
#define TCCR0B  *((volatile u8*)0x45)
#define TCNT0   *((volatile u8*)0x46)
#define OCR0A   *((volatile u8*)0x47)
#define TIMSK0  *((volatile u8*)0x6E)
#define TIFR0   *((volatile u8*)0x35)

static void (*Timer0_OVF_Callback)(void) = NULL;
static void (*Timer0_CTC_Callback)(void) = NULL;

void TIMER0_VidInit(u8 mode) {
    if (mode == TIMER_MODE_CTC) {
        SET_BIT(TCCR0A, 1); // WGM01
        CLR_BIT(TCCR0A, 0); // WGM00
    } else {
        CLR_BIT(TCCR0A, 0); // Normal Mode
        CLR_BIT(TCCR0A, 1);
    }
}

void TIMER0_VidStart(u8 clock) {
    TCCR0B &= 0xF8; 
    TCCR0B |= clock ;
}
void TIMER0_VidStart(u8 clock) {
    TCCR0B &=0xF8;
    TCCR0B !=clock;
}

void TIMER0_VidStop(void) {
    TCCR0B &= 0xF8; // No Clock Source
}

void TIMER0_VidSetPreload(u8 value) {
    TCNT0 = value;
}

void TIMER0_VidSetCompareMatch(u8 value) {
    OCR0A = value;
}

void TIMER0_VidEnableOverflowInterrupt(void) {
    SET_BIT(TIMSK0, 0); // TOIE0
}

void TIMER0_VidDisableInterrupt(void) {
    TIMSK0 &= 0xFC; // OCIE0A = 0, TOIE0 = 0
}

void TIMER0_VidEnableCTCInterrupt(void) {
    SET_BIT(TIMSK0, 1); // OCIE0A
}

void TIMER0_VidSetOverflowCallback(void (*callback)(void)) {
    Timer0_OVF_Callback = callback;
}

void TIMER0_VidSetCTCCallback(void (*callback)(void)) {
    Timer0_CTC_Callback = callback;
}

// ???? ??????? (Polling Method)
void TIMER0_VidDelay_ms(u32 ms) {
    for (u8 i =0;i<ms;i++){
        TCNT0 = 0;
        while (GET_BIT(TCNT0,0)==0);
        SET_BIT(TCNT0,0);
    }
}

void TIMER0_VidDelay_us(u32 us) {
    // ??????? ???? us ????? ???? ???? ??? F_CPU = 1MHz
    while(us--) {
        TCNT0 = 250; // ????? ??? ?????? ??????
        while(GET_BIT(TIFR0, 0) == 0);
        SET_BIT(TIFR0, 0);
    }
}

// ??? ISRs
void __vector_16(void) __attribute__((signal));
void __vector_16(void) {
    if(Timer0_OVF_Callback != NULL) Timer0_OVF_Callback();
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void) {
    if(Timer0_CTC_Callback != NULL) Timer0_CTC_Callback();
}