/**
 ****************************************************************************************************
 * @file        atk_md0240_spi.h
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

#ifndef __ATK_MD0240_SPI_H
#define __ATK_MD0240_SPI_H

#include "main.h"

/* SPI�ӿڶ��� */
#define ATK_MD0240_SPI_INTERFACE                SPI1
#define ATK_MD0240_SPI_PRESCALER                SPI_BAUDRATEPRESCALER_2
#define ATK_MD0240_SPI_CLK_ENABLE()             do{ __HAL_RCC_SPI1_CLK_ENABLE(); }while(0)

/* ���Ŷ��� */
#define ATK_MD0240_SPI_SCK_GPIO_PORT            GPIOB
#define ATK_MD0240_SPI_SCK_GPIO_PIN             GPIO_PIN_3
#define ATK_MD0240_SPI_SCK_GPIO_AF              GPIO_AF5_SPI1
#define ATK_MD0240_SPI_SCK_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define ATK_MD0240_SPI_SDA_GPIO_PORT            GPIOB
#define ATK_MD0240_SPI_SDA_GPIO_PIN             GPIO_PIN_5
#define ATK_MD0240_SPI_SDA_GPIO_AF              GPIO_AF5_SPI1
#define ATK_MD0240_SPI_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* �������� */
void atk_md0240_spi_init(void);                         /* ATK-MD0240ģ��SPI�ӿڳ�ʼ�� */
void atk_md0240_spi_send(uint8_t *buf, uint16_t len);   /* ATK-MD0240ģ��SPI�ӿڷ������� */

#endif
