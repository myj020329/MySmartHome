#include "driver_dht11.h"
#include "driver_lcd.h"
#include "driver_timer.h"
#include "stm32f1xx_hal.h"


/* 控制GPIO读取DHT11的数据 
 * 1. 主机发出至少18MS的低脉冲: start信号
 * 2. start信号变为高, 20-40us之后, dht11会拉低总线维持80us
      然后拉高80us: 回应信号
 * 3. 之后就是数据, 逐位发送
 *    bit0 : 50us低脉冲, 26-28us高脉冲
 *    bit1 : 50us低脉冲, 70us高脉冲
 * 4. 数据有40bit: 8bit湿度整数数据+8bit湿度小数数据
                   +8bit温度整数数据+8bit温度小数数据
                   +8bit校验和
 */



//把DHT11的数据引脚配置为输出
static void DHT11_PinCfgAsOutput(void)
{
    /* 对于STM32F103, 已经把DHT11的引脚配置为"open drain, pull-up" */
}

//把DHT11的数据引脚配置为输入
static void DHT11_PinCfgAsInput(void)
{
    /* 对于STM32F103, 已经把DHT11的引脚配置为"open drain, pull-up" 
	* 让它输出1就不会驱动这个引脚, 并且可以读入引脚状态
     */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
}

//设置DHT11的数据引脚的输出值
static void DHT11_PinSet(int val)
{
	if (val)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

//读取DHT11的数据引脚
static int DHT11_PinRead(void)
{
    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
		return 1;
	else
		return 0;
}


//再来实现DHT11的读操作 */
//给DHT11发出启动信号 
static void DHT11_Start(void)
{
	DHT11_PinSet(0);
	mdelay(20);
	DHT11_PinCfgAsInput();
}


//等待DHT11的回应信号
static int DHT11_Wait_Ack(void)
{
	udelay(60);
	return DHT11_PinRead();
}

//在指定时间内等待数据引脚变为某个值
static int DHT11_WaitFor_Val(int val, int timeout_us)
{
	while (timeout_us--)
	{
		if (DHT11_PinRead() == val)
			return 0; /* ok */
		udelay(1);
	}
	return -1; /* err */
}

//读取DH11 1byte数据
static int DHT11_ReadByte(void)
{
	int i;
	int data = 0;
	
	for (i = 0; i < 8; i++)
	{
		if (DHT11_WaitFor_Val(1, 1000))
		{
			//printf("dht11 wait for high data err!\n\r");
			return -1;
		}
		udelay(40);
		data <<= 1;
		if (DHT11_PinRead() == 1)
			data |= 1;
		
		if (DHT11_WaitFor_Val(0, 1000))
		{
			//printf("dht11 wait for low data err!\n\r");
			return -1;
		}
	}
	
	return data;
}


//DHT11的初始化函数
void DHT11_Init(void)
{
	DHT11_PinCfgAsOutput();
	DHT11_PinSet(1);
	//mdelay(2000);
}


//读取DHT11的温度/湿度
int DHT11_Read(int *hum, int *temp)
{
	unsigned char hum_m, hum_n;
	unsigned char temp_m, temp_n;
	unsigned char check;	
	
	DHT11_Start();
	
	if (0 != DHT11_Wait_Ack())
	{
		//printf("dht11 not ack, err!\n\r");
		return -1;
	}

	if (0 != DHT11_WaitFor_Val(1, 1000))  /* 等待ACK变为高电平, 超时时间是1000us */
	{
		//printf("dht11 wait for ack high err!\n\r");
		return -1;
	}

	if (0 != DHT11_WaitFor_Val(0, 1000))  /* 数据阶段: 等待低电平, 超时时间是1000us */
	{
		//printf("dht11 wait for data low err!\n\r");
		return -1;
	}

	hum_m  = DHT11_ReadByte();
	hum_n  = DHT11_ReadByte();
	temp_m = DHT11_ReadByte();
	temp_n = DHT11_ReadByte();
	check  = DHT11_ReadByte();

	DHT11_PinCfgAsOutput();
	DHT11_PinSet(1);

	if (hum_m + hum_n + temp_m + temp_n == check)
	{
		*hum  = hum_m;
		*temp = temp_m;
		return 0;
	}
	else
	{
		//printf("dht11 checksum err!\n\r");
		return -1;
	}

}


//DHT11测试程序
void DHT11_Test(void)
{
	int hum, temp;
    int len;
	
	DHT11_Init();
	
	while (1)
	{
		if (DHT11_Read(&hum, &temp) !=0 )
		{
			//printf("\n\rdht11 read err!\n\r");
			DHT11_Init();
		}
		else
		{
			LCD_PrintString(0, 0, "DHT11:");
            LCD_PrintString(0, 2, "Humidity Temp");
            len = LCD_PrintSignedVal(0, 5, hum);
            LCD_PutChar(len, 5, '%');
            LCD_PrintSignedVal(11, 5, temp);
		}
		mdelay(2000);  /* 读取周期是2S, 不能读太频繁 */
	}
}



