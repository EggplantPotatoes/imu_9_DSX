#include "stdio.h"
#include "debug.h"
#include "math.h"
#include "stdarg.h"
#include "usbd_cdc_if.h"

extern UART_HandleTypeDef huart1;

uint8_t StaMessages[4] = {0x11, 0x22, 0x33, 0x44};
uint8_t RxBuffer[20];

/**
 * 函数功能: 重定向c库函数printf到DEBUG_USARTx
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}


//重写printf函数
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
	HAL_UART_Transmit(&huart1, ptr, len, HAL_MAX_DELAY);
  return len;
}

/**
 * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}

void uart_debug_init(void)
{

  HAL_UART_Transmit_IT(&huart1, (uint8_t *)StaMessages, sizeof(StaMessages));
  HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuffer, 1); // 调用中断接收函数，接收长度设为1，接收一个字节进一次中断
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
  HAL_UART_Transmit(&huart1, (uint8_t *)RxBuffer, 1, 0xFFFF); // 发送接收到的数据
  HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuffer, 1);       // 再开启接收中断（因为里面中断只会触发一次，因此需要再次开启）
}

// 本协议是CSV风格的字符串流，直观简洁，编程像printf简单
void vofa_FireWater_output(float s1, float s2, float s3)
{
  	printf("simples:%f,%f,%f\n", s1, s2,s3);
}

// 本协议是纯十六进制浮点传输
void vofa_JustFloat_output(float s1, float s2, float s3, float s4)
{
  float data[4];
  uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
  // 发送数据
  data[0] = s1;
  data[1] = s2;
  data[2] = s3;
  data[3] = s4;
  HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(float) * 4, 100); // 发送数据
  // 发送帧尾
  HAL_UART_Transmit(&huart1, tail, 4, 100);
}

void usb_printf(const char *format, ...)
{
    va_list args;
    uint32_t length;
    uint8_t buf[APP_TX_DATA_SIZE];

    va_start(args, format);
    length = vsnprintf((char *)buf, APP_TX_DATA_SIZE, (char *)format, args);
    va_end(args);
    CDC_Transmit_FS(buf, length);
}


void usb_send_data(uint8_t* Buf, uint16_t Len)
{
	CDC_Transmit_FS(Buf,Len);

}


// USB输出 本协议是纯十六进制浮点传输
void vofa_JustFloat_USB_output(float s1, float s2, float s3, float s4)
{
  float data[4];
  uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
  uint8_t mergedArray[sizeof(data) + sizeof(tail)];

  // 发送数据
  data[0] = s1;
  data[1] = s2;
  data[2] = s3;
  data[3] = s4;
  //合并数组，发送出去
  memcpy(mergedArray, data, sizeof(data));
  memcpy(mergedArray + sizeof(data), tail, sizeof(tail));

  CDC_Transmit_FS((uint8_t *)mergedArray, sizeof(data) + sizeof(tail)); // 发送数据

}

// 本协议是CSV风格的字符串流，直观简洁，编程像printf简单
void vofa_FireWater_USB_output(float s1, float s2, float s3,float s4)
{
	usb_printf("simples:%f,%f,%f,%f\n", s1, s2,s3,s4);
}
