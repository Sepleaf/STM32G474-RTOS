#include "led.h"

#define GPIOx 			GPIOE
#define GPIO_CLK 		(1 << 4)
#define GPIO_PIN 		0

void led_init(void)
{
	RCC->AHB2ENR 	&= ~GPIO_CLK; 				// ���ԭ��������
	RCC->AHB2ENR 	|= GPIO_CLK;  				// ʹ�� PORTB ��ʱ��
	
	GPIOx->MODER 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->MODER 	|= 0x1 << (GPIO_PIN * 2); 	// ��ʼ��PB11Ϊ���ģʽ
	GPIOx->OTYPER 	&= ~(0x1 << GPIO_PIN);   	// PB11�������
	GPIOx->OSPEEDR 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->OSPEEDR 	|= 0x2 << (GPIO_PIN * 2); 	// PB11����ģʽ
	GPIOx->PUPDR 	&= ~(0x3 << (GPIO_PIN * 2));
	GPIOx->PUPDR 	|= 0x1 << (GPIO_PIN * 2); 	// PB11����
	GPIOx->ODR 		&= ~(0x1 << GPIO_PIN);		
	GPIOx->ODR 		|= 0x1 << GPIO_PIN; 		// PB11���1���ߵ�ƽ��
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
