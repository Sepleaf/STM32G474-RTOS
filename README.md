# STM32G474VET6 寄存器模板



[更新说明](#更新说明)

[模板说明](#模板说明)

[工程内容](#工程内容)



## 更新说明

2023.10.4

---

* 基础GPIO配置

* 中断配置
* RT-Thread 配置文件修改

> 当开发的项目对实时性要求不高时，裸机和移植RTOS的区别不大。使用RTOS发生错误是，排查将会变得非常困难。可自行判断是否需要移植RTOS。



## 模板说明

- 使用的RTOS为[RT-Thread](https://www.rt-thread.org/)
- 适用芯片[STM32G474VET6](https://www.st.com/zh/microcontrollers-microprocessors/stm32g474ve.html)
- 线程创建使用动态栈



## 工程内容

### 初始化

```c
void rt_hw_board_init()
{
    /* System Clock Update */
    SystemCoreClockUpdate();

    /* System Tick Configuration */
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    SYSCLK_170MHz();
    usart_init(115200);
    led_init();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}
```

> 所有外设初始化都放在board.c 的`void rt_hw_board_init()`函数。



### LED测试

```c
static void led1_thread_entry(void *parameter)
{
    while (1)
    {
        led_on(1);

        rt_thread_delay(100);
    }
}
```



### USART测试













