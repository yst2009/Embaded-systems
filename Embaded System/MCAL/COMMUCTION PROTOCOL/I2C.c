#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include "I2C.h"

#ifndef I2C_OK
#define I2C_OK     1
#define I2C_ERROR  0
#endif

/* =========================================================
   MASTER INIT (100kHz @ 16MHz)
   ========================================================= */
void I2C_Master_Init(void)
{
    TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); // Prescaler = 1
    TWBR = 72;                              // SCL = 100kHz
    TWCR = (1 << TWEN);
}

void I2C_Slave_Init(uint8_t address)
{
    TWAR = (address << 1);
    TWCR = (1 << TWEN) | (1 << TWEA);
}

/* =========================================================
   START / REPEATED START
   ========================================================= */
uint8_t I2C_Start_condition(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    uint8_t status = (TWSR & 0xF8);
    if (status == 0x08 || status == 0x10)
    {
        return I2C_OK;
    }
    return I2C_ERROR;
}

uint8_t I2C_Repeated_Start(void)
{
    return I2C_Start_condition();
}

/* =========================================================
   SEND SLA + WRITE
   ========================================================= */
uint8_t I2C_Send_SLA_W(uint8_t address)
{
    TWDR = (address << 1); // ????? ????? 7-bit
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x18) // 0x18 = SLA+W ACK
    {
        return I2C_OK;
    }
    return I2C_ERROR;
}

/* =========================================================
   SEND SLA + READ
   ========================================================= */
uint8_t I2C_Send_SLA_R(uint8_t address)
{
    TWDR = (address << 1) | 1; // R/W = 1
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x40) // 0x40 = SLA+R ACK
    {
        return I2C_OK;
    }
    return I2C_ERROR;
}

/* =========================================================
   WRITE DATA
   ========================================================= */
uint8_t I2C_Write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x28) // 0x28 = Data transmitted, ACK received
    {
        return I2C_OK;
    }
    return I2C_ERROR;
}

/* =========================================================
   READ DATA + ACK
   ========================================================= */
uint8_t I2C_Read_ACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/* =========================================================
   READ DATA + NACK
   ========================================================= */
uint8_t I2C_Read_NACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/* =========================================================
   STOP CONDITION
   ========================================================= */
void I2C_Stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

/* =========================================================
   SLAVE RECEIVE
   ========================================================= */
uint8_t I2C_Slave_Receive(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}