#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

/* 定义电机 ID 枚举 (契合麦轮底盘的四个方位) */
typedef enum {
    MOTOR_LF = 0,   // Left Front  (左前)
    MOTOR_RF,       // Right Front (右前)
    MOTOR_LR,       // Left Rear   (左后)
    MOTOR_RR        // Right Rear  (右后)
} Motor_ID_t;

/* 定义电机运行方向枚举 */
typedef enum {
    DIR_FORWARD = 0, // 正转
    DIR_REVERSE      // 反转
} Motor_Dir_t;

/* 函数声明 */
void Motor_Init(void);                                      // 初始化所有电机(开启PWM)
void Motor_Set_Dir(Motor_ID_t motor, Motor_Dir_t dir);      // 设置单个电机的转向
void Motor_Test_All(Motor_Dir_t dir);                       // 测试：所有电机同向运转

#endif /* __MOTOR_H */