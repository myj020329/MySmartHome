#ifndef __FREERTOSCONFIG_H
#define __FREERTOSCONFIG_H

#include "stm32f1xx_hal.h"

#define xPortPendSVHandler          PendSV_Handler
#define vPortSVCHandler             SVC_Handler
#define xPortSysTickHandler         SysTick_Handler

#define configUSE_PREEMPTION                     1//1��ʾ��ռʽ�ںˣ�0����Э��ʽ�ں�
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
#define configUSE_TICKLESS_IDLE                  0//Ĭ����disabled, 0.��������Ϊ1����2
#define configCPU_CLOCK_HZ                       ( 72000000 )//CPUʱ��Ƶ��
#define configSYSTICK_CLOCK_HZ                   (8000000)
#define configTICK_RATE_HZ                       (1000  )//ʱ�ӽ���Ƶ��
#define configMAX_PRIORITIES                     ( 5 )//������ȼ�IDLE��freertos��Ϊÿһ�����ȼ�������������RAM��
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)//��������Ķ�ջ��С
#define configMAX_TASK_NAME_LEN                  ( 16 )//�������ֵ���󳤶�
#define configUSE_16_BIT_TICKS                   0//0��portTickType��ָ��Ϊuint32_t��1ʱportTickType��ָ��Ϊuint16_t
#define configIDLE_SHOULD_YIELD                  1//Ĭ����enble,1��
#define configUSE_TASK_NOTIFICATIONS             1//Ĭ����enabled, 1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES    3
#define configUSE_MUTEXES                        1//ʹ�û���������
#define configUSE_RECURSIVE_MUTEXES              0//Ĭ����disenbled,0
#define configUSE_COUNTING_SEMAPHORES            0//Ĭ����disenbled,0
#define configUSE_ALTERNATIVE_MUTEXES            0
#define configQUEUE_REGISTRY_SIZE                10//0�������жӼ�¼���������������жӼ�¼��ʡRAM
#define configUSE_QUEUE_SETS                     0
#define configUSE_TIME_SLICING                   0
#define configUSE_NEWLIB_REENTRANT               0
#define configENABLE_BACKWARD_COMPATIBILITY      0//Ĭ����enabled,2
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS  5
#define configSTACK_DEPTH_TYPE                   uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE         size_t

#define configSUPPORT_STATIC_ALLOCATION          0//1��̬�ڴ����ʹ��
#define configSUPPORT_DYNAMIC_ALLOCATION         1//1��̬�ڴ����ʹ��
#define configTOTAL_HEAP_SIZE                    (10240)//�ܵĶ�ջ��С
#define configAPPLICATION_ALLOCATED_HEAP         0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0

#define configUSE_IDLE_HOOK                         0//��ʹ�ÿ��й��Ӻ���
#define configUSE_TICK_HOOK                         0//��ʹ�õδ�ʱ�乳�Ӻ���
#define configCHECK_FOR_STACK_OVERFLOW              0//��ջ������Ӻ���
#define configUSE_MALLOC_FAILED_HOOK                0//
#define configUSE_DAEMON_TASK_STARTUP_HOOK          0

#define configGENERATE_RUN_TIME_STATS               0//Ϊ1ʱ��������ʱ��ͳ�ƹ���
#define configUSE_TRACE_FACILITY                    0//Ϊ1���ÿ��ӻ����ٵ���
#define configUSE_STATS_FORMATTING_FUNCTIONS        0//���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������

#define configUSE_CO_ROUTINES                       0//��ʹ��Э�̴���
#define configMAX_CO_ROUTINE_PRIORITIES             1//Э�̴������ȼ���Ŀ

#define configUSE_TIMERS                            1//Ϊ1ʱ���������ʱ��
#define configTIMER_TASK_PRIORITY                   3//�����ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH                    10//�����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH                configMINIMAL_STACK_SIZE//�����ʱ�������ջ��С

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
