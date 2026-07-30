#include "motor.h"

/* 
 * 【极度警告】：
 * 下面的 htim3, htim4, htim5, htim8 只是我根据你 main.c 里的初始化瞎猜的。
 * 你必须把这里替换成你真正在 CubeMX 里给这四个电机分配的定时器句柄！
 */
extern TIM_HandleTypeDef htim2; 
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

/**
 * @brief  初始化所有电机，开启所有 PWM 通道并默认锁死
 */
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1); // 左前电机脉冲
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); // 右前电机脉冲
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // 左后电机脉冲
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // 右后电机脉冲
}

/**
 * @brief  控制单个电机的方向
 * @note   这里的 M1_DIR_GPIO_Port 等宏定义，需要你在 CubeMX 里给引脚打上对应的 User Label！
 *         如果没有打标签，请直接填入真实的端口如 GPIOA, GPIO_PIN_1
 */
void Motor_Set_Dir(Motor_ID_t motor, Motor_Dir_t dir)
{
    // 这里的逻辑根据你驱动板的实际情况，可能高电平是正转，也可能低电平是正转
    GPIO_PinState pin_state = (dir == DIR_FORWARD) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    switch (motor)
    {
        case MOTOR_LF:
            HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, pin_state);
            break;
        case MOTOR_RF:
            HAL_GPIO_WritePin(FR_GPIO_Port, FR_Pin, pin_state);
            break;
        case MOTOR_LR:
            HAL_GPIO_WritePin(RL_GPIO_Port, RL_Pin, pin_state);
            break;
        case MOTOR_RR:
            HAL_GPIO_WritePin(RR_GPIO_Port, RR_Pin, pin_state);
            break;
    }
}

/**
 * @brief  测试函数：让四个电机同时朝一个方向转动
 */
void Motor_Test_All(Motor_Dir_t dir)
{
    Motor_Set_Dir(MOTOR_LF, dir);
    Motor_Set_Dir(MOTOR_RF, dir);
    Motor_Set_Dir(MOTOR_LR, dir);
    Motor_Set_Dir(MOTOR_RR, dir);
}