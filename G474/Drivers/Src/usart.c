#include "usart.h"
#include <stdio.h>

#define USARTx USART1

/**
 **********************************************************
 * @brief   initialize the USART1
 * @param   baudrate: 9600 ~ 115200
 * @retval  none
 * @date 2023.09.24
 **********************************************************
 **/
void usart_init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    gpio_set(GPIOB, 6, GPIO_MODE_AF, GPIO_OTYPE_PP, MEDIUM_SPEED, GPIO_PULL_UP);
    gpio_set(GPIOB, 7, GPIO_MODE_AF, GPIO_OTYPE_PP, MEDIUM_SPEED, GPIO_PULL_UP);
    gpio_af_set(GPIOB, 6, 7); // AF7
    gpio_af_set(GPIOB, 7, 7);

    /* Set Baudrate */
    if (baudrate == 9600)
        USARTx->BRR = 0x452C;    // 600 Bps
    else if (baudrate == 19200)  //
        USARTx->BRR = 0x2296;    // 19200 Bps
    else if (baudrate == 38400)  //
        USARTx->BRR = 0x114B;    // 38400 Bps
    else if (baudrate == 57600)  //
        USARTx->BRR = 0xB87;     // 57600 Bps
    else if (baudrate == 115200) //
        USARTx->BRR = 0x5C4;     // 115200 Bps

    USARTx->CR1 &= ~USART_CR1_UE;    // disable usart
    USARTx->CR1 &= ~USART_CR1_OVER8; // oversampling by 16
    USARTx->CR1 |= USART_CR1_MME;    // mute mode enable
    USARTx->CR1 |= USART_CR1_RXNEIE; // receive data register not empty
    USARTx->CR1 |= USART_CR1_TE;     // transmitter enable
    USARTx->CR1 |= USART_CR1_RE;     // receiver enable
    USARTx->CR1 |= USART_CR1_UE;     // enable usart

    NVIC_InitTypeDef USART_NVIC_InitStruct;
    USART_NVIC_InitStruct.IRQChannel = USART1_IRQn;
    USART_NVIC_InitStruct.IRQPreemptionPriority = 1;
    USART_NVIC_InitStruct.IRQSubPriority = 0;
    USART_NVIC_InitStruct.IRQCmd = ENABLE;
    NVIC_Init(&USART_NVIC_InitStruct);
}

/**
 **********************************************************
 * @brief   USART sends messages
 * @param   data: the data to send
 * @retval  none
 * @date 2023.09.24
 **********************************************************
 **/
void usart_send(uint8_t data)
{
    while (!(USARTx->ISR &= USART_ISR_TXE_TXFNF))
        ;
    USARTx->TDR = data;
}

int fputc(int ch, FILE *f)
{
    usart_send((uint8_t)ch);
    return ch;
}

uint8_t usart_receive()
{
    uint8_t data;
    if ((USARTx->ISR & USART_ISR_RXNE_RXFNE))
    {
        data = (USARTx->RDR & 0xFF);
    }

    return data;
}

void USART1_IRQHandler()
{
    uint8_t data;
    if ((USARTx->ISR & USART_ISR_RXNE_RXFNE))
    {
        data = USARTx->RDR;
    }
}
