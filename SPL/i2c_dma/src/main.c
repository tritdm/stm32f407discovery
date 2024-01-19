#include "stm32f4xx.h"                  // Device header

const uint32_t I2C1_SCL_Pin = GPIO_Pin_6;
const uint32_t I2C1_SDA_Pin = GPIO_Pin_7;
const uint32_t I2C2_SCL_Pin = GPIO_Pin_10;
const uint32_t I2C2_SDA_Pin = GPIO_Pin_11;

const uint16_t I2C1_SCL_PinSource = GPIO_PinSource6;
const uint16_t I2C1_SDA_PinSource = GPIO_PinSource7;
const uint16_t I2C2_SCL_PinSource = GPIO_PinSource10;
const uint16_t I2C2_SDA_PinSource = GPIO_PinSource11;

GPIO_TypeDef* I2C1_Port = GPIOB;
GPIO_TypeDef* I2C2_Port = GPIOB;

void _GPIO_Init(void);
void Timer_Init(void);
void _DMA_Init(void);
uint32_t u32buffer[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
void delay(uint32_t u32msDelay);

int main(void) 
{		
		_GPIO_Init();
		Timer_Init();
		while (1) 
		{
				/*pulse_width += fade;
				if ((10u == pulse_width) || (0u == pulse_width)) fade = -fade;
				TIM_SetCompare1(TIM4, pulse_width);
				delay(100u);*/
		}
}

void _GPIO_Init(void) 
{
		GPIO_InitTypeDef I2C1_Init, I2C2_Init;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		I2C1_Init.GPIO_Mode 						= GPIO_Mode_AF;
		I2C1_Init.GPIO_OType 						= GPIO_OType_OD;
		I2C1_Init.GPIO_Pin 							= I2C1_SCL_Pin | I2C1_SDA_Pin;
		I2C1_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		I2C1_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(I2C1_Port, I2C1_SCL_PinSource, GPIO_AF_I2C1);
		GPIO_PinAFConfig(I2C1_Port, I2C1_SDA_PinSource, GPIO_AF_I2C1);
		
		GPIO_Init(I2C1_Port, &I2C1_Init);
		/* **************************************************************** */
		I2C2_Init.GPIO_Mode 						= GPIO_Mode_AF;
		I2C2_Init.GPIO_OType 						= GPIO_OType_OD;
		I2C2_Init.GPIO_Pin 							= I2C2_SCL_Pin;
		I2C2_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		I2C2_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(I2C2_Port, I2C2_SCL_PinSource, GPIO_AF_I2C2);
		GPIO_PinAFConfig(I2C2_Port, I2C2_SDA_PinSource, GPIO_AF_I2C2);
		
		GPIO_Init(I2C1_Port, &I2C2_Init);
}

void Timer_Init(void) 
{
		/* Timer 6 for delay and Timer 4 for PWM */
		TIM_TimeBaseInitTypeDef TIM6_Init, TIM4_Init;
		/* Timer 6 clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
		/* Timer 6 config */
		TIM6_Init.TIM_Prescaler 					= 84u - 1u;
		TIM6_Init.TIM_Period 							= 0xffff;
		TIM_TimeBaseInit(TIM6, &TIM6_Init);
		TIM_Cmd(TIM6, ENABLE);
}

void _I2C_Init(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
		I2C_InitTypeDef I2C_Master_Init, I2C_Slave_Init;
		I2C_Master_Init.I2C_Ack 								= I2C_Ack_Disable;
		I2C_Master_Init.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_10bit;
		I2C_Master_Init.I2C_ClockSpeed 					= 100000;
		I2C_Master_Init.I2C_DutyCycle						= I2C_DutyCycle_2;
		I2C_Master_Init.I2C_Mode								= I2C_Mode_I2C;
		I2C_Master_Init.I2C_OwnAddress1					= 3;
	
		I2C_Slave_Init.I2C_Ack 									= I2C_Ack_Disable;
		I2C_Slave_Init.I2C_AcknowledgedAddress 	= I2C_AcknowledgedAddress_10bit;
		I2C_Slave_Init.I2C_ClockSpeed 					= 100000;
		I2C_Slave_Init.I2C_DutyCycle						= I2C_DutyCycle_2;
		I2C_Slave_Init.I2C_Mode									= I2C_Mode_I2C;
		I2C_Slave_Init.I2C_OwnAddress1					= 3;
	
		I2C_Init(I2C1, &I2C_Master_Init);
		I2C_Init(I2C2, &I2C_Slave_Init);
	
		I2C_Cmd(I2C1, ENABLE);
		I2C_Cmd(I2C2, ENABLE);
		
		I2C_DMACmd(I2C1, ENABLE);
		I2C_DMACmd(I2C2, ENABLE);
}

void _DMA_Init(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
		DMA_InitTypeDef DMA1_S5_C1_Init, DMA1_S3_C7_Init;
	
		DMA1_S5_C1_Init.DMA_BufferSize 					= 18;
		DMA1_S5_C1_Init.DMA_Channel 						= DMA_Channel_1;
		DMA1_S5_C1_Init.DMA_DIR 								= DMA_DIR_PeripheralToMemory;
		DMA1_S5_C1_Init.DMA_Memory0BaseAddr 		= (uint32_t)(&u32buffer);
		DMA1_S5_C1_Init.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
		DMA1_S5_C1_Init.DMA_MemoryInc 					=	DMA_MemoryInc_Enable;
		DMA1_S5_C1_Init.DMA_Mode 								= DMA_Mode_Circular;
		DMA1_S5_C1_Init.DMA_PeripheralBaseAddr	= (uint32_t)(&TIM4->CCR1);
		DMA1_S5_C1_Init.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;
	
		DMA1_S3_C7_Init.DMA_BufferSize 					= 18;
		DMA1_S3_C7_Init.DMA_Channel 						= DMA_Channel_1;
		DMA1_S3_C7_Init.DMA_DIR 								= DMA_DIR_PeripheralToMemory;
		DMA1_S3_C7_Init.DMA_Memory0BaseAddr 		= (uint32_t)(&u32buffer);
		DMA1_S3_C7_Init.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
		DMA1_S3_C7_Init.DMA_MemoryInc 					=	DMA_MemoryInc_Enable;
		DMA1_S3_C7_Init.DMA_Mode 								= DMA_Mode_Circular;
		DMA1_S3_C7_Init.DMA_PeripheralBaseAddr	= (uint32_t)(&TIM4->CCR1);
		DMA1_S3_C7_Init.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;
		
		DMA_Init(DMA1_Stream5, &DMA1_S5_C1_Init);
		DMA_Cmd(DMA1_Stream5, ENABLE);
		
		DMA_Init(DMA1_Stream3, &DMA1_S3_C7_Init);
		DMA_Cmd(DMA1_Stream3, ENABLE);
		
}

void delay(uint32_t u32msDelay) 
{
		while (u32msDelay) 
		{
				TIM_SetCounter(TIM6, 0u);
				while (TIM_GetCounter(TIM6) < 1000u) 
				{
						/* waiting */
				}
				-- u32msDelay;
		}
}
