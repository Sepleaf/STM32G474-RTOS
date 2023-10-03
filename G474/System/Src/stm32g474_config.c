#include "stm32g474_config.h"

/*
 * 外部中断配置
 * GPIOx：GPIOA ~ GPIOG -> 0x0 ~ 0x6
 * BITx： 0x0 ~ 0xF
 * TRIM：0x1->下降沿  2->上升沿 3->电平触发
 */
void ex_nvic_config(uint8_t GPIOx, uint8_t BITx, uint8_t TRIM)
{
    uint8_t EXTOFFSET = (BITx % 4) * 4;
    RCC->APB2ENR |= 0x01UL << 0;                        // enable system clock
    SYSCFG->EXTICR[BITx / 4] &= ~(0x000F << EXTOFFSET); // clear configuration
    SYSCFG->EXTICR[BITx / 4] |= GPIOx << EXTOFFSET;     // EXTI.BITx映射到GPIOx.BITx
    // 自动设置
    EXTI->IMR1 |= 0x01UL << BITx; // 开启line BITx上的中断(如果要禁止中断，则反操作即可)
    if (TRIM & 0x01UL)
        EXTI->FTSR1 |= 0x01UL << BITx; // line BITx上事件下降沿触发
    if (TRIM & 0x02UL)
        EXTI->RTSR1 |= 0x01UL << BITx; // line BITx上事件上升降沿触发
}

/**
 **********************************************************
 * @brief  Set the priority of an interrupt.
 * @param  IRQn: External interrupt number.
 *         This parameter can be an enumerator of IRQn_Type enumeration
 *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32g4xxxx.h))
 * @param  PreemptPriority: The pre-emption priority for the IRQn channel.
 *         This parameter can be a value between 0 and 15
 *         A lower priority value indicates a higher priority
 * @param  SubPriority: the subpriority level for the IRQ channel.
 *         This parameter can be a value between 0 and 15
 *         A lower priority value indicates a higher priority.
 * @retval None
 **********************************************************
 **/
void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct)
{
    uint32_t priority_group;
    priority_group = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(NVIC_InitStruct->IRQChannel,
                     NVIC_EncodePriority(priority_group,
                                         NVIC_InitStruct->IRQPreemptionPriority,
                                         NVIC_InitStruct->IRQSubPriority));

    if (NVIC_InitStruct->IRQCmd == 1)
    {
        NVIC_EnableIRQ(NVIC_InitStruct->IRQChannel);
    }
    else
    {
        NVIC_DisableIRQ(NVIC_InitStruct->IRQChannel);
    }
}

/**
 **********************************************************
 * @brief   initialize the GPIOx
 *
 * @param   GPIOx:  GPIOA ~ GPIOG
 * @param   BITx:   0 ~ 15
 * @param   MODE:   0x0->Input/ 0x1->General purpose output /0x2->Alternate function /0x3->Analog
 * @param   OTYPE:  0x0->Output push-pull /0x1->Output open-drain
 * @param   OSPEED: 0x0->Low speed /0x1->Medium speed /0x2->High speed /0x3->Very high speed
 * @param   PUPD:   0x0->No PUPD /0x1-> Pull-up /0x2->pull-down /0x3->Reserved
 *
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void gpio_set(GPIO_TypeDef *GPIOx, uint32_t BITx, uint32_t MODE, uint32_t OTYPE, uint32_t OSPEED, uint32_t PUPD)
{
    GPIOx->MODER &= ~(0x03UL << BITx * 2);
    GPIOx->MODER |= (MODE << BITx * 2);

    GPIOx->OTYPER &= ~(0x01UL << BITx);
    GPIOx->OTYPER |= (OTYPE << BITx);

    GPIOx->OSPEEDR &= ~(0x03UL << BITx * 2);
    GPIOx->OSPEEDR |= (OSPEED << BITx * 2);

    GPIOx->PUPDR &= ~(0x03UL << BITx * 2);
    GPIOx->PUPDR |= (PUPD << BITx * 2);
}

/**
 **********************************************************
 * @brief   alternate set
 * @param   GPIOx:  GPIOA ~ GPIOG
 * @param   BITx:   0 ~ 15
 * @param   AFx:    alternate number
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void gpio_af_set(GPIO_TypeDef *GPIOx, uint8_t BITx, uint8_t AFx)
{
    GPIOx->AFR[BITx >> 3] &= ~(0XF << ((BITx & 0X7) * 4));
    GPIOx->AFR[BITx >> 3] |= (uint32_t)AFx << ((BITx & 0X07UL) * 4);
}

/**
 **********************************************************
 * @brief   pull up the pin
 * @param   GPIOx:  GPIOA ~ GPIOG
 * @param   BITx:   0 ~ 15
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void gpio_set_bit(GPIO_TypeDef *GPIOx, uint8_t BITx)
{
    GPIOx->ODR |= (0x01UL << BITx);
}

/**
 **********************************************************
 * @brief   pull down the pin
 * @param   GPIOx:  GPIOA ~ GPIOG
 * @param   BITx:   0 ~ 15
 * @retval  none
 * @version 2023.09.24
 **********************************************************
 **/
void gpio_reset_bit(GPIO_TypeDef *GPIOx, uint8_t BITx)
{
    GPIOx->ODR &= ~(0x01UL << BITx);
}
