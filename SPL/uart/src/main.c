#include "stm32f4xx.h"                  // Device header

const uint32_t USART1_TX_Pin = GPIO_Pin_9;
const uint32_t USART1_RX_Pin = GPIO_Pin_10;
const uint32_t USART2_TX_Pin = GPIO_Pin_2;
const uint32_t USART2_RX_Pin = GPIO_Pin_3;

const uint16_t USART1_TX_PinSource = GPIO_PinSource9;
const uint16_t USART1_RX_PinSource = GPIO_PinSource10;
const uint16_t USART2_TX_PinSource = GPIO_PinSource2;
const uint16_t USART2_RX_PinSource = GPIO_PinSource3;

GPIO_TypeDef* USART1_Port = GPIOA;
GPIO_TypeDef* USART2_Port = GPIOA;

void _GPIO_Init(void);
void Timer_Init(void);
void _USART_Init(void);
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
		GPIO_InitTypeDef USART1_Init, USART2_Init;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		USART1_Init.GPIO_Mode 						= GPIO_Mode_AF;
		USART1_Init.GPIO_OType 						= GPIO_OType_PP;
		USART1_Init.GPIO_Pin 							= USART1_TX_Pin | USART1_RX_Pin;
		USART1_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		USART1_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(USART1_Port, USART1_TX_PinSource, GPIO_AF_USART1);
		GPIO_PinAFConfig(USART1_Port, USART1_RX_PinSource, GPIO_AF_USART1);
		
		GPIO_Init(USART1_Port, &USART1_Init);
		/* **************************************************************** */
		USART2_Init.GPIO_Mode 						= GPIO_Mode_AF;
		USART2_Init.GPIO_OType 						= GPIO_OType_OD;
		USART2_Init.GPIO_Pin 							= USART2_TX_Pin | USART2_RX_Pin;
		USART2_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		USART2_Init.GPIO_Speed 						= GPIO_High_Speed;
	
		GPIO_PinAFConfig(USART2_Port, USART2_TX_PinSource, GPIO_AF_USART2);
		GPIO_PinAFConfig(USART2_Port, USART1_RX_PinSource, GPIO_AF_USART2);
		
		GPIO_Init(USART2_Port, &USART2_Init);
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

void _USART_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
		USART_InitTypeDef USART_TX_Init, USART_RX_Init;
		USART_TX_Init.USART_BaudRate 						= 9600;
		USART_TX_Init.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
		USART_TX_Init.USART_Mode 								=	USART_Mode_Rx;
		USART_TX_Init.USART_Parity 							=	USART_Parity_No;
		USART_TX_Init.USART_StopBits 						= USART_StopBits_0_5;
		USART_TX_Init.USART_WordLength 					= USART_WordLength_8b;
	
		USART_RX_Init.USART_BaudRate 						= 9600;
		USART_RX_Init.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
		USART_RX_Init.USART_Mode 								=	USART_Mode_Tx;
		USART_RX_Init.USART_Parity 							=	USART_Parity_No;
		USART_RX_Init.USART_StopBits 						= USART_StopBits_0_5;
		USART_RX_Init.USART_WordLength 					= USART_WordLength_8b;
	
		USART_Init(USART1, &USART_TX_Init);
		USART_Init(USART2, &USART_RX_Init);
	
		USART_Cmd(USART1, ENABLE);
		USART_Cmd(USART2, ENABLE);
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
