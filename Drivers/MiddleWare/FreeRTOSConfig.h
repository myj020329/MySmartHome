#ifndef __FREERTOSCONFIG_H
#define __FREERTOSCONFIG_H

#include "stm32f1xx_hal.h"

#define xPortPendSVHandler          PendSV_Handler
#define vPortSVCHandler             SVC_Handler
#define xPortSysTickHandler         SysTick_Handler

#define configUSE_PREEMPTION                     1//1表示抢占式内核，0代表协程式内核
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
#define configUSE_TICKLESS_IDLE                  0//默认是disabled, 0.可以设置为1或者2
#define configCPU_CLOCK_HZ                       ( 72000000 )//CPU时钟频率
#define configSYSTICK_CLOCK_HZ                   (8000000)
#define configTICK_RATE_HZ                       (1000  )//时钟节拍频率
#define configMAX_PRIORITIES                     ( 5 )//最大优先级IDLE，freertos会为每一个优先级建立链表，消耗RAM。
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)//空闲任务的堆栈大小
#define configMAX_TASK_NAME_LEN                  ( 16 )//任务名字的最大长度
#define configUSE_16_BIT_TICKS                   0//0是portTickType被指定为uint32_t；1时portTickType被指定为uint16_t
#define configIDLE_SHOULD_YIELD                  1//默认是enble,1。
#define configUSE_TASK_NOTIFICATIONS             1//默认是enabled, 1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES    3
#define configUSE_MUTEXES                        1//使用互斥量代码
#define configUSE_RECURSIVE_MUTEXES              0//默认是disenbled,0
#define configUSE_COUNTING_SEMAPHORES            0//默认是disenbled,0
#define configUSE_ALTERNATIVE_MUTEXES            0
#define configQUEUE_REGISTRY_SIZE                10//0不设置列队记录，其他代表设置列队记录，省RAM
#define configUSE_QUEUE_SETS                     0
#define configUSE_TIME_SLICING                   0
#define configUSE_NEWLIB_REENTRANT               0
#define configENABLE_BACKWARD_COMPATIBILITY      0//默认是enabled,2
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS  5
#define configSTACK_DEPTH_TYPE                   uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE         size_t

#define configSUPPORT_STATIC_ALLOCATION          0//1静态内存分配使能
#define configSUPPORT_DYNAMIC_ALLOCATION         1//1动态内存分配使能
#define configTOTAL_HEAP_SIZE                    (10240)//总的堆栈大小
#define configAPPLICATION_ALLOCATED_HEAP         0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0

#define configUSE_IDLE_HOOK                         0//不使用空闲钩子函数
#define configUSE_TICK_HOOK                         0//不使用滴答时间钩子函数
#define configCHECK_FOR_STACK_OVERFLOW              0//堆栈溢出钩子函数
#define configUSE_MALLOC_FAILED_HOOK                0//
#define configUSE_DAEMON_TASK_STARTUP_HOOK          0

#define configGENERATE_RUN_TIME_STATS               0//为1时启用运行时间统计功能
#define configUSE_TRACE_FACILITY                    0//为1启用可视化跟踪调试
#define configUSE_STATS_FORMATTING_FUNCTIONS        0//与宏configUSE_TRACE_FACILITY同时为1时会编译下面3个函数

#define configUSE_CO_ROUTINES                       0//不使用协程代码
#define configMAX_CO_ROUTINE_PRIORITIES             1//协程代码优先级数目

#define configUSE_TIMERS                            1//为1时启用软件定时器
#define configTIMER_TASK_PRIORITY                   3//软件定时器优先级
#define configTIMER_QUEUE_LENGTH                    10//软件定时器队列长度
#define configTIMER_TASK_STACK_DEPTH                configMINIMAL_STACK_SIZE//软件定时器任务堆栈大小

#define configKERNEL_INTERRUPT_PRIORITY             255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY        191
#define configMAX_API_CALL_INTERRUPT_PRIORITY       191

//#define configASSERT( ( x ) ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS  0
#define configTOTAL_MPU_REGIONS                                 8
#define configTEX_S_C_B_FLASH                                   0x07UL
#define configTEX_S_C_B_SRAM                                    0x07UL
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY             1
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS              1

#define secureconfigMAX_SECURE_CONTEXTS                         5

#define INCLUDE_vTaskDelete                                     1
#define INCLUDE_vTaskSuspend                                    1
#define INCLUDE_xResumeFromISR                                  1
#define INCLUDE_vTaskDelayUntil                                 1
#define INCLUDE_vTaskDelay                                      1
#define INCLUDE_xTaskGetSchedulerstate                          1
#define INCLUDE_xTaskGetCurrentTaskHandle                       1
#define INCLUDE_uxTaskGetstackHighWaterMark                     0
#define INCLUDE_xTaskGetIdleTaskHandle                          0
#define INCLUDE_eTaskGetState                                   0
#define INCLUDE_xEventGroupSetBitFromISR                        1
#define INCLUDE_xTimerPendFunctionCall                          0
#define INCLUDE_xTaskAbortDelay                                 0
#define INCLUDE_xTaskGetHandle                                  0
#define INCLUDE_xTaskResumeFromISR                              1

#endif /* __FREERTOSCONFIG_H */
