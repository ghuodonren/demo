#include "gyroscope.h"

// 引入 main.c 中已经被 CubeMX 初始化好的 I2C1 硬件句柄
extern I2C_HandleTypeDef hi2c1;

/**
 * @brief  JY901P Z轴偏航角归零 (校准)
 * @note   包含完整的 解锁 -> 发令 -> 保存 流程
 */
void JY901P_Zero_Yaw(void)
{
    uint8_t unlock_cmd = 0x88; // 维特解锁密钥
    uint8_t zero_cmd   = 0x04; // Z轴归零指令
    uint8_t save_cmd   = 0x00; // 保存指令

    // 1. 写入解锁指令到 KEY 寄存器
    HAL_I2C_Mem_Write(&hi2c1, JY901P_I2C_ADDR, JY901P_REG_KEY, I2C_MEMADD_SIZE_8BIT, &unlock_cmd, 1, 100);
    HAL_Delay(50); // 留出响应时间

    // 2. 写入归零指令到 CALSW 寄存器
    HAL_I2C_Mem_Write(&hi2c1, JY901P_I2C_ADDR, JY901P_REG_CALSW, I2C_MEMADD_SIZE_8BIT, &zero_cmd, 1, 100);
    HAL_Delay(50);

    // 3. 写入保存指令到 SAVE 寄存器
    HAL_I2C_Mem_Write(&hi2c1, JY901P_I2C_ADDR, JY901P_REG_SAVE, I2C_MEMADD_SIZE_8BIT, &save_cmd, 1, 100);
    
    // 留足时间让芯片内部 Flash 擦写保存，防止后续立刻读取时总线冲突
    HAL_Delay(100); 
}

/**
 * @brief  读取 JY901P 陀螺仪 Z轴角度(偏航角 Yaw)
 * @retval 角度值 (浮点数，范围 -180.0 到 180.0)
 */
float JY901P_Read_Yaw(void)
{
    uint8_t buffer[2] = {0};
    short raw_yaw = 0;

    // 连续读取 2 个字节的偏航角数据
    HAL_I2C_Mem_Read(&hi2c1, JY901P_I2C_ADDR, JY901P_REG_YAW, I2C_MEMADD_SIZE_8BIT, buffer, 2, 100);

    // 数据拼接：buffer[0]是低八位(L)，buffer[1]是高八位(H)
    raw_yaw = (short)((buffer[1] << 8) | buffer[0]);

    // 官方换算公式：角度 = 原始值 / 32768 * 180
    return (float)raw_yaw / 32768.0f * 180.0f;
}

/**
 * @brief  读取 JY901P 陀螺仪 Z轴角速度(wz)
 * @retval 角速度值 (浮点数，单位: 度/秒)
 */
float JY901P_Read_WZ(void)
{
    uint8_t buffer[2] = {0};
    short raw_wz = 0;

    // 连续读取 2 个字节的 Z 轴角速度数据
    HAL_I2C_Mem_Read(&hi2c1, JY901P_I2C_ADDR, JY901P_REG_WZ, I2C_MEMADD_SIZE_8BIT, buffer, 2, 100);

    raw_wz = (short)((buffer[1] << 8) | buffer[0]);

    // 官方换算公式：角速度 = 原始值 / 32768 * 2000 (默认量程 2000度/秒)
    return (float)raw_wz / 32768.0f * 2000.0f;
}