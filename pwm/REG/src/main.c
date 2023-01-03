#include "stm32f4xx.h"                  // Device header

#define sbi(reg, bit) (reg) |= (1 << (bit))
#define cbi(reg, bit) (reg) &= ~(1 << (bit))
#define tbi(reg, bit) (reg) ^= (1 << (bit))

void _GPIO_Init(void);
void Timer_Init(void);
void PWM_Init(void);
void delay(uint32_t u32msDelay);
uint32_t pulse_width = 0;
int16_t fade = 1;

int main(void) 
{		
		_GPIO_Init();
		Timer_Init();
		PWM_Init();
		while (1) 
		{
				pulse_width += fade;
				if ((10u == pulse_width) || (0u == pulse_width)) fade = -fade;
				TIM4->CCR1 = pulse_width;
				delay(100u);
		}
}

void _GPIO_Init(void) 
{
		/* GPIOD for built-in led */
		/* GPIOD clock */
		RCC->AHB1ENR 	|= 	(1u << 3);
		/* GPIOD config */
		GPIOD->MODER 	&= 	~(3u << (2 * 12));
		GPIOD->MODER 	|= 	(2u << (2 * 12));
		GPIOD->OTYPER &= 	~(1u << 12);
		GPIOD->AFR[1] &= 	~(15u << (4 * 4));
		GPIOD->AFR[1] |= 	(2u << (4 * 4));
}

void Timer_Init(void) 
{
		/* Timer 6 for delay and Timer 4 for PWM */
		/* Timer 6 clock */
		RCC->APB1ENR 	|= 	(1 << 4);
		/* Timer 6 config */
		TIM6->CR1 		|= 	(1 << 1);
		TIM6->PSC 		=		(84 - 1);
		TIM6->CR1 		&= 	~(1 << 1);
		TIM6->EGR 		= 	1;
		TIM6->CR1 		|= 	(1 << 0);
		/* Timer 4 clock */
		RCC->APB1ENR 	|= 	(1 << 2);
		/* Timer 4 config */
		TIM4->CR1 		|= 	(1 << 1);
		TIM4->CR1 		&= 	~(1 << 1);
		TIM4->PSC 		= 	(8400 - 1);
		TIM4->EGR 		|= 	1;
		TIM4->ARR 		= 	10;
		TIM4->CR1 		|= 	(1 << 0);
}

void PWM_Init(void) 
{
		/* PWM config */
		TIM4->CCMR1 	&= 	~(7u << 4);
		TIM4->CCMR1 	|= 	(6u << 4);
		TIM4->CCER 		&= 	~(1u << 1);
		TIM4->CCER 		|= 	1u;
		TIM4->CCR1 		= 	0u;
}

void delay(uint32_t u32msDelay) 
{
		while (u32msDelay) {
				TIM6->CNT = 0u;
				while (TIM6->CNT < 1000u) 
				{
						/* waiting */
				}
				-- u32msDelay;
		}
}
