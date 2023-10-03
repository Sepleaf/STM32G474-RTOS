#ifndef __USART_H
#define __USART_H
#include "stm32g474_config.h"

void usart_init(uint32_t baudrate);
void usart_send(uint8_t data);
uint8_t usart_receive(void);

#endif
