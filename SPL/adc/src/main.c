#include "stm32f4xx.h"                  // Device header

const uint32_t ADC_A1_Pin = GPIO_Pin_1;

GPIO_TypeDef* ADC_A1_Port = GPIOA;

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
		GPIO_InitTypeDef ADC_A1_Init;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		ADC_A1_Init.GPIO_Mode 						= GPIO_Mode_AN;
		ADC_A1_Init.GPIO_OType 						= GPIO_OType_PP;
		ADC_A1_Init.GPIO_Pin 							= ADC_A1_Pin;
		ADC_A1_Init.GPIO_PuPd							= GPIO_PuPd_NOPULL;
		ADC_A1_Init.GPIO_Speed 						= GPIO_High_Speed;
		
		GPIO_Init(ADC_A1_Port, &ADC_A1_Init);
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

void _ADC_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
		ADC_InitTypeDef ADC_A1_Init;
		ADC_A1_Init.ADC_ContinuousConvMode 		= DISABLE;
		ADC_A1_Init.ADC_DataAlign 						= ADC_DataAlign_Right;
		ADC_A1_Init.ADC_ExternalTrigConv 			= ADC_ExternalTrigConv_Ext_IT11;
		ADC_A1_Init.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
		ADC_A1_Init.ADC_NbrOfConversion 			= 10;
		ADC_A1_Init.ADC_Resolution 						= ADC_Resolution_12b;
		ADC_A1_Init.ADC_ScanConvMode 					= DISABLE;
		
		ADC_Init(ADC1, &ADC_A1_Init);
		ADC_Cmd(ADC1, ENABLE);
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
