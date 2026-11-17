/*
 * GccApplication2.c
 *
 * Created: 11/17/2026 12:30:30 PM
 * Author : youssef mohamed
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void BUTTONS_INIT(){
	DDRD|=(1<<5)|(1<<6);
	DDRC|=(1<<1)|(1<<2)|(1<<3)|(1<<0);
	TCCR0B|=(1<<CS01);
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
	TCNT0=0;
	OCR0A=0;
	OCR0B=0;
}
void Motor_SetSpeed(uint8_t speedA,uint8_t speedB){
	OCR0A=speedA;
	OCR0B=speedB;
}
void Forward(){
	PORTC |= (1 << 0);
	PORTC &= ~(1 << 1);
	PORTC |= (1 << 2);
	PORTC &= ~(1 << 3);
}
void Backward(){
	PORTC |= (1 << 1);
	PORTC &= ~(1 << 0);
	PORTC |= (1 << 3);
	PORTC &= ~(1 << 2);
}
void Motor_Stop(void) {
	PORTC &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
	OCR0A = 0;
	OCR0B = 0;
}
int main(void)
{
	BUTTONS_INIT();
    while (1) 
    {
		
		Forward();
		Motor_SetSpeed(255,255);
		_delay_ms(1000);
		Motor_Stop();
		Backward();
		Motor_SetSpeed(255,255);
		_delay_ms(1000);
		Motor_Stop();

    }
}

