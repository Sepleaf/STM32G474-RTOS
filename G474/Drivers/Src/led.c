#include "led.h"

/**
 **********************************************************
 * @brief   Initialize the LED
 * @param   none
 * @retval  none
 * @date 2023.09.24
 **********************************************************
 **/
void led_init(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	gpio_set(GPIOE, 0, GPIO_MODE_OUT, GPIO_OTYPE_PP, HIGH_SPEED, GPIO_PULL_UP);
	gpio_set(GPIOE, 1, GPIO_MODE_OUT, GPIO_OTYPE_PP, HIGH_SPEED, GPIO_PULL_UP);
	gpio_set(GPIOE, 2, GPIO_MODE_OUT, GPIO_OTYPE_PP, HIGH_SPEED, GPIO_PULL_UP);

	led_off(0);
	led_off(1);
	led_off(2);
}

/**
 **********************************************************
 * @brief   turn on the LED
 * @param   n: select LED -> 0 ~ 1
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void led_off(uint8_t n)
{
	GPIOE->ODR &= ~(0x1UL << n);
	GPIOE->ODR |= (0x1UL << n);
}

/**
 **********************************************************
 * @brief   turn off the LED
 * @param   n: select LED -> 0 ~ 1
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void led_on(uint8_t n)
{
	GPIOE->ODR &= ~(0x1UL << n);
}
