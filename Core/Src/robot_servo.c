#include "robot_servo.h"

extern UART_HandleTypeDef huart2;

/**
 * @brief  【官方协议版】简易单圈角度控制 (指令 0x08)
 * @param  id       舵机编号 (1-4)
 * @param  angle    目标角度 (例如 45.0f, -30.0f)
 * @param  time     运动时间 (ms)
 */
void Servo_Move_Angle(uint8_t id, float angle, uint16_t time)
{
    uint8_t buf[12]; // 官方协议总长度为 12 字节
    uint16_t checksum = 0;
    
    // 官方规定目标位置单位为 0.1°
    // 比如传入 45.0f，乘以 10 变成 450 发送
    int16_t position = (int16_t)(angle * 10.0f); 
    
    // 若 power=0，则按照默认功率保护阈值执行
    uint16_t power = 0; 

    buf[0] = 0x12; // 固定标识 Header 1
    buf[1] = 0x4C; // 固定标识 Header 2
    buf[2] = 0x08; // 简易单圈角度控制指令
    buf[3] = 0x07; // 数据长度 (7个字节)
    buf[4] = id;   // 舵机 ID

    // 目标位置 (2字节，低位在前)
    buf[5] = position & 0xFF;        
    buf[6] = (position >> 8) & 0xFF; 

    // 运动时间 (2字节，低位在前)
    buf[7] = time & 0xFF;            
    buf[8] = (time >> 8) & 0xFF;     
    
    // 执行功率 (2字节，低位在前)
    buf[9] = power & 0xFF;
    buf[10] = (power >> 8) & 0xFF;

    // 校验码：前 11 个字节累加和 对 256 取模
    for(int i = 0; i < 11; i++) {
        checksum += buf[i];
    }
    buf[11] = checksum & 0xFF; 

    // 发送 12 字节的数据包
    HAL_UART_Transmit(&huart2, buf, 12, 50);
}

/**
 * @brief 关键帧 0：折叠待机状态
 */
void Robot_Arm_Fold(void)
{
    Servo_Move_Angle(SERVO_BASE,       0.0f, 1500); 
    Servo_Move_Angle(SERVO_SHOULDER,   0.0f, 1500); 
    Servo_Move_Angle(SERVO_ELBOW,     45.0f, 1500); 
    Servo_Move_Angle(SERVO_GRIPPER,  -30.0f, 1500); 
}

/**
 * @brief 关键帧 1：展开并张开爪子瞄准
 */
void Robot_Arm_Expand(void)
{
    Servo_Move_Angle(SERVO_BASE,      45.0f, 1500); 
    Servo_Move_Angle(SERVO_SHOULDER,  60.0f, 1500); 
    Servo_Move_Angle(SERVO_ELBOW,      0.0f, 1500); 
    Servo_Move_Angle(SERVO_GRIPPER,   80.0f, 1500); 
}

/**
 * @brief 关键帧 2：下探并夹紧目标
 */
void Robot_Arm_Grab(void)
{
    Servo_Move_Angle(SERVO_BASE,      45.0f, 1000); 
    Servo_Move_Angle(SERVO_SHOULDER,  20.0f, 1000); 
    Servo_Move_Angle(SERVO_ELBOW,     25.0f, 1000); 
    Servo_Move_Angle(SERVO_GRIPPER,  -30.0f, 1000); 
}

/**
 * @brief 关键帧 3：拔地而起，高高举起
 */
void Robot_Arm_Lift(void)
{
    Servo_Move_Angle(SERVO_BASE,      45.0f, 1500); 
    Servo_Move_Angle(SERVO_SHOULDER, 100.0f, 1500); 
    Servo_Move_Angle(SERVO_ELBOW,    -20.0f, 1500); 
    Servo_Move_Angle(SERVO_GRIPPER,  -30.0f, 1500); 
}

/**
 * @brief 附加测试：全臂垂直状态
 */
void Robot_Arm_Vertical_Test(void)
{
    Servo_Move_Angle(SERVO_BASE,      90.0f, 2000); 
    Servo_Move_Angle(SERVO_SHOULDER, 140.0f, 2000); 
    Servo_Move_Angle(SERVO_ELBOW,    -45.0f, 2000); 
    Servo_Move_Angle(SERVO_GRIPPER,    0.0f, 2000); 
}