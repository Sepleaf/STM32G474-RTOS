#include "thread.h"

/* 定义线程控制块指针 */
static rt_thread_t led1_thread = RT_NULL;

static void led1_thread_entry(void *parameter);

int rtt_init(void)
{
    led1_thread = rt_thread_create("led1",
                                   led1_thread_entry,
                                   RT_NULL,
                                   512,
                                   3,
                                   20);
    if (led1_thread != RT_NULL)
        rt_thread_startup(led1_thread);
    else
        return -1;

    return 0;
}

static void led1_thread_entry(void *parameter)
{
    while (1)
    {
        led_on(1);

        rt_thread_delay(100);
    }
}
