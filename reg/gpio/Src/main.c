#include "stm32f4xx.h"                  // Device header

#define sbi(reg, bit) (reg) |= (1 << (bit))
#define cbi(reg, bit) (reg) &= ~(1 << (bit))
#define tbi(reg, bit) (reg) ^= (1 << (bit))

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
		if (1u == (GPIOA->IDR & 1u))
		{
			delay(50u);
			if (1u == (GPIOA->IDR & 1u))
			{
				while (1u == (GPIOA->IDR & 1u))
				{
					/* waiting */
				}
				GPIOD->ODR ^= (1u << 12);
			}
		}
	}
}

void _GPIO_Init(void) 
{
	/* GPIOD for built-in led and GPIOA for built-in user button */
	/* GPIOD Clock */
	RCC->AHB1ENR	|= 	(1u << 3);
	/* GPIOD config */
	GPIOD->MODER	&= 	~(3u << 24);
	GPIOD->MODER	|= 	(1u << 24);
	GPIOD->OTYPER	&= 	~(1u << 12);
	/* GPIOA Clock */
	RCC->AHB1ENR	|= 	(1u << 0);
	/* GPIOA config */
	GPIOA->MODER	&= 	~(3u << 0);
	GPIOA->PUPDR	&= 	~(3u << 0);
}

void Timer_Init(void) 
{
	/* Timer 6 for delay */
	/* Timer 6 Clock */
	RCC->APB1ENR	|= (1u << 4);
	/* Timer 6 config */
	TIM6->CR1		|= 	(1u << 1);
	TIM6->PSC		= 	(84u - 1u);
	TIM6->CR1		&= 	~(1u << 1);
	TIM6->EGR		= 	(1u << 0);
	TIM6->CR1		|= 	(1u << 0);
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

