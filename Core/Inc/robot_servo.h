#ifndef __ROBOT_SERVO_H
#define __ROBOT_SERVO_H

#include "main.h"

/* 机械臂舵机 ID 宏定义 */
#define SERVO_BASE      1  // 底座
#define SERVO_SHOULDER  2  // 大臂
#define SERVO_ELBOW     3  // 小臂
#define SERVO_GRIPPER   4  // 夹爪

void Servo_Move_Angle(uint8_t id, float angle, uint16_t time);

void Robot_Arm_Fold(void);           // 关键帧 0：折叠待机
void Robot_Arm_Expand(void);         // 关键帧 1：展开瞄准
void Robot_Arm_Grab(void);           // 关键帧 2：下探抓取
void Robot_Arm_Lift(void);           // 关键帧 3：抬起悬空
void Robot_Arm_Vertical_Test(void);  // 附加测试：全臂垂直

#endif