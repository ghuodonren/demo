#ifndef __GYROSCOPE_H
#define __GYROSCOPE_H

#include "main.h"

/* JY901P 通信地址与寄存器定义 (维特智能标准 IIC 协议) */
#define JY901P_I2C_ADDR     0xA0    // IIC 写地址 (0x50 << 1)

// 控制与配置寄存器
#define JY901P_REG_SAVE     0x00    // 保存寄存器
#define JY901P_REG_CALSW    0x01    // 校准与配置寄存器
#define JY901P_REG_KEY      0x69    // 解锁/密钥寄存器

// 数据寄存器
#define JY901P_REG_WZ       0x39    // Z轴角速度(Gyro Z)首地址
#define JY901P_REG_YAW      0x3F    // Z轴偏航角(Yaw)首地址

/* 操作函数声明 */
void JY901P_Zero_Yaw(void);         // Z轴角度归零（初始化）
float JY901P_Read_Yaw(void);        // 读取 Z轴角度 (单位: 度)
float JY901P_Read_WZ(void);         // 读取 Z轴角速度 (单位: 度/秒)

#endif /* __GYROSCOPE_H */