
#ifndef _DRIVER_ACTIVE_BUZZER_H
#define _DRIVER_ACTIVE_BUZZER_H


/**********************************************************************
 * 函数名称： ActiveBuzzer_Init
 * 功能描述： 有源蜂鸣器的初始化函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void ActiveBuzzer_Init(void);

/**********************************************************************
 * 函数名称： ActiveBuzzer_Control
 * 功能描述： 有源蜂鸣器控制函数
 * 输入参数： on - 1-响, 0-不响
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void ActiveBuzzer_Control(int on);

/**********************************************************************
 * 函数名称： ActiveBuzzer_Test
 * 功能描述： 有源蜂鸣器测试程序
 * 输入参数： 无
 * 输出参数： 无
 *            无
 * 返 回 值： 无
 * 修改日期        版本号     修改人        修改内容
 * -----------------------------------------------
 * 2023/08/04        V1.0     韦东山       创建
 ***********************************************************************/
void ActiveBuzzer_Test(void);


#endif /* _DRIVER_ACTIVE_BUZZER_H */

