#include "stm32f4xx.h"                  // Device header

const uint32_t LED_D12_Pin = GPIO_Pin_12;
const uint32_t User_Button_Pin = GPIO_Pin_0;

GPIO_TypeDef* LED_D12_Port = GPIOD;
GPIO_TypeDef* User_Button_Port = GPIOA;

void _GPIO_Init(void);
void Timer_Init(void);
void PWM_Init(void);
void _DMA_Init(void);
uint16_t u16buffer[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int tmp;
void delay(uint32_t u32msDelay);

int main(void) 
{		
		_GPIO_Init();
		Timer_Init();
		PWM_Init();
		_DMA_Init();
		while (1) 
		{
				tmp = TIM4->CCR1;
		}
}

void _GPIO_Init(void) 
{
		/* GPIOD for built-in led */
		GPIO_InitTypeDef LED_D12_Init;
		/* GPIOD clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		/* GPIOD config */
		LED_D12_Init.GPIO_Mode 						= GPIO_Mode_AF;
		LED_D12_Init.GPIO_OType 					= GPIO_OType_PP;
		LED_D12_Init.GPIO_Pin 						= LED_D12_Pin;
		LED_D12_Init.GPIO_PuPd						= GPIO_PuPd_NOPULL;
		LED_D12_Init.GPIO_Speed 					= GPIO_High_Speed;
	
		GPIO_PinAFConfig(LED_D12_Port, GPIO_PinSource12, GPIO_AF_TIM4);
		
		GPIO_Init(LED_D12_Port, &LED_D12_Init);
}

void Timer_Init(void) 
{
		/* Timer 6 for delay and Timer 4 for PWM */
		TIM_TimeBaseInitTypeDef TIM4_Init;
		/* Timer 4 clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		/* Timer 4 config */
		TIM4_Init.TIM_Prescaler	 					= 8400u - 1u;
		TIM4_Init.TIM_Period 							= 10u;
		TIM_TimeBaseInit(TIM4, &TIM4_Init);
		TIM_Cmd(TIM4, ENABLE);
		TIM_DMACmd(TIM4, TIM_DMA_CC1, ENABLE);
}

void PWM_Init(void) 
{
		TIM_OCInitTypeDef PWM_TIM4_C1_Init;
		/* PWM config */
		PWM_TIM4_C1_Init.TIM_OCMode 			= TIM_OCMode_PWM1;
		PWM_TIM4_C1_Init.TIM_OCPolarity 	= TIM_OCPolarity_High;
		PWM_TIM4_C1_Init.TIM_OutputState 	= TIM_OutputState_Enable;
		PWM_TIM4_C1_Init.TIM_Pulse 				= 0u;
		
		TIM_OC1Init(TIM4, &PWM_TIM4_C1_Init);
}

void _DMA_Init(void)
{
		DMA_InitTypeDef DMA_S0_C2_Init;
		DMA_S0_C2_Init.DMA_BufferSize 				= 18;
		DMA_S0_C2_Init.DMA_Channel 						= DMA_Channel_2;
		DMA_S0_C2_Init.DMA_DIR 								= DMA_DIR_MemoryToPeripheral;
		DMA_S0_C2_Init.DMA_Memory0BaseAddr 		= (uint32_t)(&u16buffer);
		DMA_S0_C2_Init.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord;
		DMA_S0_C2_Init.DMA_MemoryInc 					=	DMA_MemoryInc_Enable;
		DMA_S0_C2_Init.DMA_Mode 							= DMA_Mode_Circular;
		DMA_S0_C2_Init.DMA_PeripheralBaseAddr	= (uint32_t)(&TIM4->CCR1);
		DMA_S0_C2_Init.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;
		DMA_Init(DMA1_Stream0, &DMA_S0_C2_Init);
		DMA_Cmd(DMA1_Stream0, ENABLE);
}
