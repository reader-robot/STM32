#ifndef __MYI2C_H
#define __MYI2C_H
 
void MyI2C_Init(void);
void MyI2C_start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte();
void MyI2C_SendCk(uint8_t AckBit);
uint8_t MyI2C_ReceiveCk();
#endif