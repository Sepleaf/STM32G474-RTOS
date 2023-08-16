#include "led.h"

#define GPIOx 			GPIOE
#define GPIO_CLK 		(1 << 4)
#define GPIO_PIN 		0

void led_init(void)
{
	RCC->AHB2ENR 	&= ~GPIO_CLK; 				// 清除原来的设置
	RCC->AHB2ENR 	|= GPIO_CLK;  				// 使能 PORTB 口时钟
	
	GPIOx->MODER 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->MODER 	|= 0x1 << (GPIO_PIN * 2); 	// 初始化PB11为输出模式
	GPIOx->OTYPER 	&= ~(0x1 << GPIO_PIN);   	// PB11输出推挽
	GPIOx->OSPEEDR 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->OSPEEDR 	|= 0x2 << (GPIO_PIN * 2); 	// PB11高速模式
	GPIOx->PUPDR 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->PUPDR 	|= 0x1 << (GPIO_PIN * 2); 	// PB11上拉
	GPIOx->ODR 		&= ~(0x1 << GPIO_PIN);		
	GPIOx->ODR 		|= 0x1 << GPIO_PIN; 		// PB11输出1（高电平）
}

void led_on()
{
	GPIOx->ODR &= ~(0x1 << GPIO_PIN);
	GPIOx->ODR |= 0x1 << GPIO_PIN;
}

void led_off()
{
	GPIOx->ODR &= ~(0x1 << GPIO_PIN);
}
