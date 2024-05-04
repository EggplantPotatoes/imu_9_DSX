/*
 * @FilePath: \wifi_robot\src\tool\crc8_table.cpp
 * @brief: 
 * @author: liumingming
 * @Date: 2023-10-13 10:24:40
 * @Version: 1.0
 */
#include "crc8_table.h"


#define CRC8_MODE_X8_X5_x4_1 0X31
#define CRC8_MODE_X8_X2_x1_1 0X07 //X8+x2+x1+1
#define CRC8_MODE_X8_X6_x4_x3_x2_x1 0X5E

// 采用查表法，减少计算量
//static const uint8_t crc_table[] =
//{
//        0x00,
//        0x07,
//        0x0e,
//        0x09,
//        0x1c,
//        0x1b,
//        0x12,
//        0x15,
//        0x38,
//        0x3f,
//        0x36,
//        0x31,
//        0x24,
//        0x23,
//        0x2a,
//        0x2d,
//        0x70,
//        0x77,
//        0x7e,
//        0x79,
//        0x6c,
//        0x6b,
//        0x62,
//        0x65,
//        0x48,
//        0x4f,
//        0x46,
//        0x41,
//        0x54,
//        0x53,
//        0x5a,
//        0x5d,
//        0xe0,
//        0xe7,
//        0xee,
//        0xe9,
//        0xfc,
//        0xfb,
//        0xf2,
//        0xf5,
//        0xd8,
//        0xdf,
//        0xd6,
//        0xd1,
//        0xc4,
//        0xc3,
//        0xca,
//        0xcd,
//        0x90,
//        0x97,
//        0x9e,
//        0x99,
//        0x8c,
//        0x8b,
//        0x82,
//        0x85,
//        0xa8,
//        0xaf,
//        0xa6,
//        0xa1,
//        0xb4,
//        0xb3,
//        0xba,
//        0xbd,
//        0xc7,
//        0xc0,
//        0xc9,
//        0xce,
//        0xdb,
//        0xdc,
//        0xd5,
//        0xd2,
//        0xff,
//        0xf8,
//        0xf1,
//        0xf6,
//        0xe3,
//        0xe4,
//        0xed,
//        0xea,
//        0xb7,
//        0xb0,
//        0xb9,
//        0xbe,
//        0xab,
//        0xac,
//        0xa5,
//        0xa2,
//        0x8f,
//        0x88,
//        0x81,
//        0x86,
//        0x93,
//        0x94,
//        0x9d,
//        0x9a,
//        0x27,
//        0x20,
//        0x29,
//        0x2e,
//        0x3b,
//        0x3c,
//        0x35,
//        0x32,
//        0x1f,
//        0x18,
//        0x11,
//        0x16,
//        0x03,
//        0x04,
//        0x0d,
//        0x0a,
//        0x57,
//        0x50,
//        0x59,
//        0x5e,
//        0x4b,
//        0x4c,
//        0x45,
//        0x42,
//        0x6f,
//        0x68,
//        0x61,
//        0x66,
//        0x73,
//        0x74,
//        0x7d,
//        0x7a,
//        0x89,
//        0x8e,
//        0x87,
//        0x80,
//        0x95,
//        0x92,
//        0x9b,
//        0x9c,
//        0xb1,
//        0xb6,
//        0xbf,
//        0xb8,
//        0xad,
//        0xaa,
//        0xa3,
//        0xa4,
//        0xf9,
//        0xfe,
//        0xf7,
//        0xf0,
//        0xe5,
//        0xe2,
//        0xeb,
//        0xec,
//        0xc1,
//        0xc6,
//        0xcf,
//        0xc8,
//        0xdd,
//        0xda,
//        0xd3,
//        0xd4,
//        0x69,
//        0x6e,
//        0x67,
//        0x60,
//        0x75,
//        0x72,
//        0x7b,
//        0x7c,
//        0x51,
//        0x56,
//        0x5f,
//        0x58,
//        0x4d,
//        0x4a,
//        0x43,
//        0x44,
//        0x19,
//        0x1e,
//        0x17,
//        0x10,
//        0x05,
//        0x02,
//        0x0b,
//        0x0c,
//        0x21,
//        0x26,
//        0x2f,
//        0x28,
//        0x3d,
//        0x3a,
//        0x33,
//        0x34,
//        0x4e,
//        0x49,
//        0x40,
//        0x47,
//        0x52,
//        0x55,
//        0x5c,
//        0x5b,
//        0x76,
//        0x71,
//        0x78,
//        0x7f,
//        0x6a,
//        0x6d,
//        0x64,
//        0x63,
//        0x3e,
//        0x39,
//        0x30,
//        0x37,
//        0x22,
//        0x25,
//        0x2c,
//        0x2b,
//        0x06,
//        0x01,
//        0x08,
//        0x0f,
//        0x1a,
//        0x1d,
//        0x14,
//        0x13,
//        0xae,
//        0xa9,
//        0xa0,
//        0xa7,
//        0xb2,
//        0xb5,
//        0xbc,
//        0xbb,
//        0x96,
//        0x91,
//        0x98,
//        0x9f,
//        0x8a,
//        0x8d,
//        0x84,
//        0x83,
//        0xde,
//        0xd9,
//        0xd0,
//        0xd7,
//        0xc2,
//        0xc5,
//        0xcc,
//        0xcb,
//        0xe6,
//        0xe1,
//        0xe8,
//        0xef,
//        0xfa,
//        0xfd,
//        0xf4,
//        0xf3,
//};

uint8_t crc_high_first(uint8_t *ptr, uint32_t len)
{
    uint8_t i;
    uint8_t crc = 0x00; /* 计算的初始crc值 */

    while (len--)
    {
        crc ^= *ptr++;          /* 每次先与需要计算的数据异或,计算完指向下一数据 */
        for (i = 8; i > 0; --i) /* 下面这段计算过程与计算一个字节crc一样 */
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ CRC8_MODE_X8_X2_x1_1;
            else
                crc = (crc << 1);
        }
    }

    return (crc);
}
uint16_t crc16Calculate(uint8_t * pbuf, int cal_length)
{
    int i, j;
    uint16_t crc16 = 0xffff; //init
    uint16_t polynomial = 0x1021; //CCITT标准-0x1021
// unsigned int polynomial = 0x8005; //美国标准-0x8005
    uint16_t curVal;

    for(i = 0; i < cal_length; i++)
    {
        curVal = pbuf[i] << 8;

        for(j = 0; j < 8; j++)
        {
            if((crc16 ^ curVal) & 0x8000)
                crc16 = (crc16 << 1) ^ polynomial;
            else
                crc16 <<= 1;

            curVal <<= 1;
        }

    }

    return crc16;
}
/**
 * @brief: crc8 计算，采用查表，提高计算速度
 * @功能描述: 
 * @使用场景: 
 * @注意事项: 
 * @param {uint8_t} *ptr
 * @param {uint16_t} len
 * @return {*}
 * @note: 
 * CRC 计算网址  http://www.ip33.com/crc.html
 * X8+X2+X+1
 */
uint8_t Calc_CRC8(uint8_t *ptr, uint16_t len)
{
    uint8_t crc = 0x00;

    // while (len--)
    // {
    //     crc = crc_table[crc ^ *ptr++];
    // }
    crc = crc_high_first(ptr, len);
    return (crc);
}

#if 0
void create_crc_table(void)
{
    unsigned short i;
    unsigned char j;

    printf("create_crc_table\n");
    printf("\n");
    printf("\n");
    for (i = 0; i <= 0xFF; i++)
    {
        if (0 == (i % 16))
            printf("\n");

        j = i & 0xFF;
        printf("0x%.2x, ", crc_high_first(&j, 1)); /*依次计算每个字节的crc校验值*/
    }
}
#endif
