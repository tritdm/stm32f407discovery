#include "stm32f4xx.h"                  /* Device header */

const uint32_t LED_D12_Pin = GPIO_Pin_12;
const uint32_t User_Button_Pin = GPIO_Pin_0;

GPIO_TypeDef* LED_D12_Port = GPIOD;
GPIO_TypeDef* User_Button_Port = GPIOA;

void _GPIO_Init(void);
void Timer_Init(void);
void delay(uint32_t u32msDelay);

int main(void) 
{		
		_GPIO_Init();
		Timer_Init();
		while (1) 
		{
				/* Software Debounce */
				if (GPIO_ReadInputDataBit(User_Button_Port, User_Button_Pin)) 
				{
						delay(50u);
						if (GPIO_ReadInputDataBit(User_Button_Port, User_Button_Pin))
						{
								while (GPIO_ReadInputDataBit(User_Button_Port, User_Button_Pin)) 
								{
								}
								GPIO_ToggleBits(LED_D12_Port, LED_D12_Pin);
						}
				}
		}
}

void _GPIO_Init(void) 
{
		/* GPIOD for built-in led and GPIOA for built-in user button */
		GPIO_InitTypeDef LED_D12_Init, User_Button_Init;
		/* GPIOD clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		/* GPIOD config */
		LED_D12_Init.GPIO_Mode 			= GPIO_Mode_OUT;
		LED_D12_Init.GPIO_OType 		= GPIO_OType_PP;
		LED_D12_Init.GPIO_Pin 			= LED_D12_Pin;
		LED_D12_Init.GPIO_PuPd			= GPIO_PuPd_NOPULL;
		LED_D12_Init.GPIO_Speed 		= GPIO_High_Speed;
	
		GPIO_Init(LED_D12_Port, &LED_D12_Init);
		/* GPIOA clock*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		/* GPIOA config */
		User_Button_Init.GPIO_Mode 		= GPIO_Mode_IN;
		User_Button_Init.GPIO_OType 		= GPIO_OType_PP;
		User_Button_Init.GPIO_Pin 		= User_Button_Pin;
		User_Button_Init.GPIO_PuPd		= GPIO_PuPd_NOPULL;
		User_Button_Init.GPIO_Speed 		= GPIO_High_Speed;
	
		GPIO_Init(User_Button_Port, &User_Button_Init);
}

void Timer_Init(void) 
{
		/* Timer 6 for delay */
		TIM_TimeBaseInitTypeDef TIM6_Init;
		/* Timer 6 clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
		/* Timer 6 config */
		TIM6_Init.TIM_Prescaler 		= 84u - 1u;
		TIM6_Init.TIM_Period 			= 0xffff;
		TIM_TimeBaseInit(TIM6, &TIM6_Init);
		TIM_Cmd(TIM6, ENABLE);
}

void delay(uint32_t u32msDelay) 
{
		while (u32msDelay) {
				TIM_SetCounter(TIM6, 0u);
				while (TIM_GetCounter(TIM6) < 1000u) 
				{
						
				}
				-- u32msDelay;
		}
}
