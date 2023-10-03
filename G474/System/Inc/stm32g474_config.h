#ifndef __STM32G474_CONFIG_H
#define __STM32G474_CONFIG_H
#include "stm32g474xx.h"

#define NVIC_PriorityGroup_0   ( 0x07UL ) /*!< 0 bit  for preemption priority, 4 bits for subpriority */
#define NVIC_PriorityGroup_1   ( 0x06UL ) /*!< 1 bit  for preemption priority, 3 bits for subpriority */
#define NVIC_PriorityGroup_2   ( 0x05UL ) /*!< 2 bit  for preemption priority, 2 bits for subpriority */
#define NVIC_PriorityGroup_3   ( 0x04UL ) /*!< 3 bit  for preemption priority, 3 bits for subpriority */
#define NVIC_PriorityGroup_4   ( 0x03UL ) /*!< 1 bit  for preemption priority, 1 bits for subpriority */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
    ENABLE          = 1,
    DISABLE         = !ENABLE
}GPIO_STATE;

typedef enum
{
    SET             = 0,
    RESET           = !SET
} FlagStatus, ITStatus;


/* GPIO register enum */
typedef enum
{
    /* MODER */
    GPIO_MODE_IN    = 0x0UL,  // Input mode
    GPIO_MODE_OUT   = 0x1UL,  // General purpose output mode
    GPIO_MODE_AF    = 0x2UL,  // Alternate function mode
    GPIO_MODE_AN    = 0x3UL,  // Analog mode

    /* OTYPER */
    GPIO_OTYPE_PP   = 0x0UL,  // Output push-pull
    GPIO_OTYPE_OD   = 0x1UL,  // Output open-drain

    /* OSPEEDR */
    LOW_SPEED       = 0x0UL,  // 25MHz
    MEDIUM_SPEED    = 0x1UL,  // 50MHz
    HIGH_SPEED      = 0x2UL,  // 100MHz
    VERY_HIGH_SPEED = 0x3UL,  // 170MHz

    /* PUPDR */
    GPIO_NOPULL     = 0x0UL,  // No pull-up /pull-down
    GPIO_PULL_UP    = 0x1UL,  // Pull-up
    GPIO_PULL_DOWM  = 0x2UL,  // Pull-down
    RESER           = 0x3UL   // Reserved
} GPIO_TYPE;

/*NVIC configuration structure*/
typedef struct 
{
    IRQn_Type IRQChannel;            /* 中断通道(向量) */
    uint8_t   IRQPreemptionPriority; /* 抢占优先级 */
    uint8_t   IRQSubPriority;        /* 响应优先级 */
    uint8_t   IRQCmd;                /* Enable / Disable */
}NVIC_InitTypeDef;

/* function */
void ex_nvic_config(uint8_t GPIOx, uint8_t BITx, uint8_t TRIM);
void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct);
void gpio_af_set(GPIO_TypeDef *GPIOx, uint8_t BITx, uint8_t AFx);
void gpio_set(GPIO_TypeDef *GPIOx, uint32_t BITx, uint32_t MODE, uint32_t OTYPE, uint32_t OSPEED, uint32_t PUPD);
void gpio_set_bit(GPIO_TypeDef *GPIOx, uint8_t BITx);
void gpio_reset_bit(GPIO_TypeDef *GPIOx, uint8_t BITx);

#endif
