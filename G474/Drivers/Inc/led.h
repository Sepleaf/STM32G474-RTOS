#ifndef __LED_H
#define __LED_H
#include "stm32g474_config.h"

void led_init(void);
void led_off(uint8_t n);
void led_on(uint8_t n);

#endif
