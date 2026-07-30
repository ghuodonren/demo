/**
 ****************************************************************************************************
 * @file        atk_md0240_spi.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0240ģ��SPI�ӿ���������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_md0240_spi.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi3;

/**
 * @brief       ATK-MD0240ģ��SPI�ӿڳ�ʼ��
 * @param       ��
 * @retval      ��
 */
void atk_md0240_spi_init(void)
{
   
}

/**
 * @brief       ATK-MD0240ģ��SPI�ӿڷ�������
 * @param       ��
 * @retval      ��
 */
void atk_md0240_spi_send(uint8_t *buf, uint16_t len)
{
    HAL_SPI_Transmit(&hspi3, buf, len, HAL_MAX_DELAY);
}
