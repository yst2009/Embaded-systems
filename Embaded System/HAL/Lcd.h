#ifndef LCD_H
#define LCD_H

#include "STD_TYPES.h"
#include "GPIO_INTERFACE.h"

/* --- التوصيلات --- */
#define LCD_DATA_PORT    GPIO_PORTB
#define LCD_CTRL_PORT    GPIO_PORTC
#define LCD_RS_PIN       GPIO_PIN0
#define LCD_RW_PIN       GPIO_PIN1  // إضافة الـ RW
#define LCD_E_PIN        GPIO_PIN2  // عدلنا الترتيب عشان الـ RW أخد الـ PIN1

/* --- الأوامر --- */
#define LCD_CLEAR        0x01
#define LCD_FUNCTION_SET 0x38
#define LCD_DISPLAY_ON   0x0C

/* --- الدوال --- */
void LCD_vidInit(void);
void LCD_vidSendCmd(u8 copy_u8Cmd);
void LCD_vidSendData(u8 copy_u8Data);
void LCD_vidClear(void);
void LCD_vidSendString(u8* copy_u8String);
void LCD_vidSetCursor(u8 copy_u8Row, u8 copy_u8Col);

#endif