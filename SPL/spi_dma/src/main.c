#include "stm32f4xx.h"                  // Device header

//const uint32_t SPI1_NSS_Pin 	= GPIO_Pin_7;
const uint32_t SPI1_SCK_Pin 	= GPIO_Pin_5;
const uint32_t SPI1_MISO_Pin 	= GPIO_Pin_6;
const uint32_t SPI1_MOSI_Pin 	= GPIO_Pin_7;
//const uint32_t SPI2_NSS_Pin 	= GPIO_Pin_7;
const uint32_t SPI2_SCK_Pin 	= GPIO_Pin_13;
const uint32_t SPI2_MISO_Pin 	= GPIO_Pin_14;
const uint32_t SPI2_MOSI_Pin 	= GPIO_Pin_15;

const uint16_t SPI1_SCK_PinSource 	= GPIO_Pin_5;
const uint16_t SPI1_MISO_PinSource 	= GPIO_Pin_6;
const uint16_t SPI1_MOSI_PinSource 	= GPIO_Pin_7;
const uint16_t SPI2_SCK_PinSource 	= GPIO_Pin_13;
const uint16_t SPI2_MISO_PinSource 	= GPIO_Pin_14;
const uint16_t SPI2_MOSI_PinSource 	= GPIO_Pin_15;

//GPIO_TypeDef* SPI1_NSS_Port 	= GPIOB;
GPIO_TypeDef* SPI1_Port 	= GPIOA;
//GPIO_TypeDef* SPI2_NSS_Port 	= GPIOB;
GPIO_TypeDef* SPI2_Port 	= GPIOB;

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
		GPIO_InitTypeDef SPI1_Init, SPI2_Init;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		SPI1_Init.GPIO_Mode 						= GPIO_Mode_AF;
		SPI1_Init.GPIO_OType 						= GPIO_OType_PP;
		SPI1_Init.GPIO_Pin 							= SPI1_SCK_Pin | SPI1_MISO_Pin | SPI1_MOSI_Pin;
		SPI1_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		SPI1_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(SPI1_Port, SPI1_SCK_PinSource, GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI1_Port, SPI1_MISO_PinSource, GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI1_Port, SPI1_MOSI_PinSource, GPIO_AF_SPI1);
		
		GPIO_Init(SPI1_Port, &SPI1_Init);
		/* **************************************************************** */
		SPI2_Init.GPIO_Mode 						= GPIO_Mode_AF;
		SPI2_Init.GPIO_OType 						= GPIO_OType_PP;
		SPI2_Init.GPIO_Pin 							= SPI2_SCK_Pin | SPI2_MISO_Pin | SPI2_MOSI_Pin;
		SPI2_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		SPI2_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(SPI2_Port, SPI2_SCK_PinSource, GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI2_Port, SPI2_MISO_PinSource, GPIO_AF_SPI1);
		GPIO_PinAFConfig(SPI2_Port, SPI2_MOSI_PinSource, GPIO_AF_SPI1);
		
		GPIO_Init(SPI2_Port, &SPI2_Init);
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

void _SPI_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
		SPI_InitTypeDef SPI_Master_Init, SPI_Slave_Init;
		SPI_Master_Init.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_64;
		SPI_Master_Init.SPI_CPHA								=	SPI_CPOL_High;
		SPI_Master_Init.SPI_CPOL								= SPI_CPHA_1Edge;
		SPI_Master_Init.SPI_CRCPolynomial				= 7;
		SPI_Master_Init.SPI_DataSize						=	SPI_DataSize_8b;
		SPI_Master_Init.SPI_Direction						= SPI_Direction_2Lines_FullDuplex;
		SPI_Master_Init.SPI_FirstBit						=	SPI_FirstBit_MSB;
		SPI_Master_Init.SPI_Mode								= SPI_Mode_Master;
		SPI_Master_Init.SPI_NSS									= SPI_NSS_Soft;
	
		SPI_Slave_Init.SPI_BaudRatePrescaler 		= SPI_BaudRatePrescaler_64;
		SPI_Slave_Init.SPI_CPHA									=	SPI_CPOL_High;
		SPI_Slave_Init.SPI_CPOL									= SPI_CPHA_1Edge;
		SPI_Slave_Init.SPI_CRCPolynomial				= 7;
		SPI_Slave_Init.SPI_DataSize							=	SPI_DataSize_8b;
		SPI_Slave_Init.SPI_Direction						= SPI_Direction_2Lines_FullDuplex;
		SPI_Slave_Init.SPI_FirstBit							=	SPI_FirstBit_MSB;
		SPI_Slave_Init.SPI_Mode									= SPI_Mode_Slave;
		SPI_Slave_Init.SPI_NSS									= SPI_NSS_Hard;
	
		SPI_Init(SPI1, &SPI_Master_Init);
		SPI_Init(SPI2, &SPI_Slave_Init);
		
		SPI_Cmd(SPI1, ENABLE);
		SPI_Cmd(SPI2, ENABLE);
		
		SPI_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
		SPI_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
}

void _DMA_Init(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
		DMA_InitTypeDef DMA2_S0_C3_Init, DMA1_S3_C0_Init;
	
		DMA2_S0_C3_Init.DMA_BufferSize 					= 18;
		DMA2_S0_C3_Init.DMA_Channel 						= DMA_Channel_3;
		DMA2_S0_C3_Init.DMA_DIR 								= DMA_DIR_PeripheralToMemory;
		DMA2_S0_C3_Init.DMA_Memory0BaseAddr 		= (uint32_t)(&u32buffer);
		DMA2_S0_C3_Init.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
		DMA2_S0_C3_Init.DMA_MemoryInc 					=	DMA_MemoryInc_Enable;
		DMA2_S0_C3_Init.DMA_Mode 								= DMA_Mode_Circular;
		DMA2_S0_C3_Init.DMA_PeripheralBaseAddr	= (uint32_t)(&TIM4->CCR1);
		DMA2_S0_C3_Init.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;
	
		DMA1_S3_C0_Init.DMA_BufferSize 					= 18;
		DMA1_S3_C0_Init.DMA_Channel 						= DMA_Channel_0;
		DMA1_S3_C0_Init.DMA_DIR 								= DMA_DIR_PeripheralToMemory;
		DMA1_S3_C0_Init.DMA_Memory0BaseAddr 		= (uint32_t)(&u32buffer);
		DMA1_S3_C0_Init.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
		DMA1_S3_C0_Init.DMA_MemoryInc 					=	DMA_MemoryInc_Enable;
		DMA1_S3_C0_Init.DMA_Mode 								= DMA_Mode_Circular;
		DMA1_S3_C0_Init.DMA_PeripheralBaseAddr	= (uint32_t)(&TIM4->CCR1);
		DMA1_S3_C0_Init.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;
		
		DMA_Init(DMA2_Stream0, &DMA2_S0_C3_Init);
		DMA_Cmd(DMA2_Stream0, ENABLE);
		
		DMA_Init(DMA1_Stream3, &DMA1_S3_C0_Init);
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
