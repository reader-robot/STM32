#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
	
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);

}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t Bit;
	Bit=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return Bit;
}


void MyI2C_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOA的时钟
		/*GPIO初始化*/
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
		/*设置GPIO初始化后的默认电平*/
		GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_10);	
		
}

void MyI2C_start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}


void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte&0x80>>i);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}


uint8_t MyI2C_ReceiveByte()
{
	uint8_t i,Byte=0x00;
	MyI2C_W_SDA(1);
	for(i=0;i<8;i++)
	{
			MyI2C_W_SCL(1);
			if(MyI2C_R_SDA()==1)
			{
				Byte |= (0x80>>i);
			}
			MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendCk(uint8_t AckBit)
{
	
		MyI2C_W_SDA(AckBit);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	
}


uint8_t MyI2C_ReceiveCk()
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit=	MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	
	return AckBit;
}















