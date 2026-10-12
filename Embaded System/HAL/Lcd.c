#include "LCD.h"
#include <util/delay.h>

static void LCD_vidEnablePulse(void) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, GPIO_HIGH);
    _delay_ms(2);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, GPIO_LOW);
}

void LCD_vidSendCmd (u8 copy_u8Cmd) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_LOW); // RS=0 للأوامر
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW); // RW=0 للكتابة
    GPIO_VidSetPortValue(LCD_DATA_PORT, copy_u8Cmd);
    LCD_vidEnablePulse();
}

void LCD_vidSendData(u8 copy_u8Data) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_HIGH); // RS=1 للبيانات
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);  // RW=0 للكتابة
    GPIO_VidSetPortValue(LCD_DATA_PORT, copy_u8Data);
    LCD_vidEnablePulse();
}

void LCD_vidInit(void) {
    GPIO_VidSetPortDirection(LCD_DATA_PORT, 0xFF); 
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_E_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);
    _delay_ms(50); 
    LCD_vidSendCmd(LCD_FUNCTION_SET);
    _delay_ms(5); 
    LCD_vidSendCmd(LCD_DISPLAY_ON);
    _delay_ms(5); 
    LCD_vidClear();
    _delay_ms(5);
}

void LCD_vidClear(void) {
    LCD_vidSendCmd(LCD_CLEAR);
    _delay_ms(20);
}

void LCD_vidSendString(u8* copy_u8String) {
    u8 i = 0;
    while (copy_u8String[i]) {
        LCD_vidSendData(copy_u8String[i++]);
    }
}

void LCD_vidSetCursor(u8 copy_u8Row, u8 copy_u8Col) {
    _delay_ms(20);
    if (copy_u8Row == 0) {
        LCD_vidSendCmd(0x80 + copy_u8Col); 
    } else {
        LCD_vidSendCmd(0xC0 + copy_u8Col);
    }
}