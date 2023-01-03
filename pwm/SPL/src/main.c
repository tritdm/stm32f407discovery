#include "stm32f4xx.h"                  // Device header

const uint32_t LED_D12_Pin = GPIO_Pin_12;
const uint32_t User_Button_Pin = GPIO_Pin_0;

GPIO_TypeDef* LED_D12_Port = GPIOD;
GPIO_TypeDef* User_Button_Port = GPIOA;
uint32_t pulse_width = 0;
int16_t fade = 1;

void _GPIO_Init(void);
void Timer_Init(void);
void PWM_Init(void);
void delay(uint32_t u32msDelay);

int main(void) 
{		
		_GPIO_Init();
		Timer_Init();
		PWM_Init();
		while (1) 
		{
				pulse_width += fade;
				if ((10u == pulse_width) || (0u == pulse_width)) fade = -fade;
				TIM_SetCompare1(TIM4, pulse_width);
				delay(100u);
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
		TIM_TimeBaseInitTypeDef TIM6_Init, TIM4_Init;
		/* Timer 6 clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
		/* Timer 6 config */
		TIM6_Init.TIM_Prescaler 					= 84u - 1u;
		TIM6_Init.TIM_Period 							= 0xffff;
		TIM_TimeBaseInit(TIM6, &TIM6_Init);
		TIM_Cmd(TIM6, ENABLE);
		/* Timer 4 clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		/* Timer 4 config */
		TIM4_Init.TIM_Prescaler	 					= 8400u - 1u;
		TIM4_Init.TIM_Period 							= 10u;
		TIM_TimeBaseInit(TIM4, &TIM4_Init);
		TIM_Cmd(TIM4, ENABLE);
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
