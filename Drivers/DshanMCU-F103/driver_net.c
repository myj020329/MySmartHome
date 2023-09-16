#include "driver_net.h"
#include "driver_buffer.h"
#include <string.h>
#include <stdio.h>

static void HAL_UART2_MspInit(UART_HandleTypeDef *huart);

static UART_HandleTypeDef  huart2;
static RingBuffer CmdRetBuffer;
static RingBuffer NetDataBuffer;

static int NET_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    
    HAL_UART2_MspInit(&huart2);
    
    if(HAL_UART_Init(&huart2) != HAL_OK)
    {
        return -1;
    }
    
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
    
    return 0;
}

static void HAL_UART2_MspInit(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        HAL_NVIC_SetPriority(USART2_IRQn, 1 , 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}

void USART2_IRQHandler(void)
{
    uint8_t rx_data = 0;
    
    if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == SET)
    {
        __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);
        rx_data = USART2->DR;
        Buffer_Write(&CmdRetBuffer, rx_data);
        NetDataProcess_Callback(rx_data);
    }
}

//发送指令
static int Net_TransmitCmd(const char *cmd, const char *reply, uint16_t timeout)
{
    uint8_t i = 0;
    char buf[128] = {0};
    strcat(buf, cmd);
    if(strstr(buf, "\r\n") == NULL)
    {
        strcat(buf, "\r\n");
    }
    Buffer_Clean(&CmdRetBuffer);
    HAL_UART_Transmit(&huart2,(uint8_t *) buf, strlen(buf), 500);
    memset(buf, 0, 128);
    while(timeout != 0)
    {
        if(Buffer_Read(&CmdRetBuffer, (uint8_t*)&buf[i]) == 0)
        {
            i = (i+1)%128;
            
            if(strstr(buf, reply) != 0)
            {
                return 0;
            }
        }
        else
        {
            timeout--;
            HAL_Delay(1);
        }
    }
    return -1;
}

//发送数据
int Net_TransmitSocket(const char *socket, int len, int timeout)
{
    uint8_t i = 0;
    char buf[64] = {0};
    char cmd[16] = {0};
    sprintf(cmd, "AT+CIPSEND=%d\r\n", len);
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd), 500);
    HAL_Delay(1);
    Buffer_Clean(&CmdRetBuffer);
    HAL_UART_Transmit(&huart2, (uint8_t *)socket, len, 500);
    while(timeout != 0)
    {
        if(Buffer_Read(&CmdRetBuffer, (uint8_t*)&buf[i]) == 0)
        {
            i = (i+1)%64;
            if(strstr(buf, "SEND OK") != 0)
            {
                return 0;
            }
        }
        else
        {
            timeout--;
            HAL_Delay(1);
        }
    }
    return -1;
}

int Net_RecvSocket(char *buf, int len, int timeout)
{
    int tmp = 0;
    while(timeout != 0)
    {
        tmp += Buffer_ReadBytes(&NetDataBuffer, (uint8_t *)&buf[tmp],len);
        if(tmp == len)  return  0;
        timeout--;
        HAL_Delay(1);
    }
    return -1;
}

//连接WIFI
int Net_ConnectWiFi(const char *ssid, const char *pwd, int timeout)
{
    char buf[50] = "AT+CWJAP_CUR=\"";
    strcat(buf, ssid);
    strcat(buf, "\",\"");
    strcat(buf, pwd);
    strcat(buf, "\"");
    return Net_TransmitCmd(buf, "GOT IP\r\n", timeout);
}

//断开WiFi
int Net_DisconnectWiFi(void)
{
    return Net_TransmitCmd("AT+CWOAP", "OK\r\n", 500);
}

//连接TCP
int Net_ConnectTCP(const char *ip, int port, int timeout)
{
    char buf[128] = "AT+CIPSTART=\"TCP\",\"";
    sprintf(&buf[19], "%s\", %d", ip, port);
    return Net_TransmitCmd(buf, "OK\r\n", timeout);
}

//断开TCP
int Net_Disconnect_TCP_UDP(void)
{
    return Net_TransmitCmd("AT+CIPCLOSE", "OK\r\n", 500);
}

enum AT_STATUS {
    INIT_STATUS,
    LEN_STATUS,
    DATA_STATUS,
};
static uint8_t g_DataBuff[256] = {0};

void NetDataProcess_Callback(uint8_t data)
{
    uint8_t *buf = g_DataBuff;
    static enum AT_STATUS g_status = INIT_STATUS;
    static int g_DataBuffIndex = 0;
    static int g_DataLen = 0;
    int i = g_DataBuffIndex;
    int m = 0;
    
    buf[i] = data;
    g_DataBuffIndex++;
    
    switch(g_status)
    {
        case INIT_STATUS:
        {
            if(buf[0] !='+')
            {
                g_DataBuffIndex = 0;
            }
            else if (i == 4)
            {
                if(strncmp((char*)buf, "+IPD,", 5) == 0)
                {
                    g_status = LEN_STATUS;
                }
                g_DataBuffIndex = 0;
            }
            break;
        }
        
        case LEN_STATUS:
        {
            if(buf[i] == ':')
            {
                for(m = 0; m < i; m++)
                {
                    g_DataLen = g_DataLen * 10 + buf[m] - '0';
                }
                g_status = DATA_STATUS;
                g_DataBuffIndex = 0;
            }
            else if (i >= 9)  /* ESP8266数据buffer大小是2920,  4位数: +IPD,YYYY:xxxxxx */
            {
                /* 都没有接收到':' */
                g_status = INIT_STATUS;
                g_DataBuffIndex = 0;
            }
            break;
        }
        
        case DATA_STATUS:
        {
            if(g_DataBuffIndex == g_DataLen)
            {
                Buffer_WriteBytes(&NetDataBuffer, buf, g_DataLen);
                
                g_status = INIT_STATUS;
                g_DataBuffIndex = 0;
                g_DataLen = 0;
            }
            break;
        }
        default:
            break;
    }
}


int Net_Init(void)
{
    if(NET_UART_Init() != 0)
        return -1;
    
    Buffer_Init(&CmdRetBuffer, 128);
    Buffer_Init(&NetDataBuffer, 1024);
    
    Net_TransmitCmd("AT+RST", "OK\r\n", 10000);
    HAL_Delay(500);
    Net_TransmitCmd("AT+CWMODE_CUR=1", "OK\r\n", 500);
    
    return 0;
}
