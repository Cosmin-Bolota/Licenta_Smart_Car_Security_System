#include "BSW/HAL/Servo_Motor/servo_motor.h"

#include "BSW/MCAL/PWM/pwm.h"
uint16_t contor = 0;
int lastangle=0;
static const char *TAG = "HAL SERVO MOTOR";

/*******************************************************************************
 *  Function name    : SERVO_vChangeAngle
 *
 *  Description      : Change the Servo Motor angle
 *
 *  List of arguments: u32ServoAngle -> PWM duty cycle for this angle
 *
 *  Return value     : -
 *
 *******************************************************************************/
void SERVO_vChangeAngle(uint32_t ServoAngle)
{
    if(ServoAngle == SERVO_MOTOR_0_DEG)
    {
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_0_DEG);
        ESP_LOGI(TAG, "ServoAngle == 0");
    }
        
    else if(ServoAngle == SERVO_MOTOR_90_DEG)
    {
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_90_DEG);
        vTaskDelay(11);
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, 0);
        ESP_LOGI(TAG, "ServoAngle == 90");
    }
    else if(ServoAngle == SERVO_MOTOR_180_DEG)
    {
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_180_DEG);
        vTaskDelay(25);
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, 0);
        ESP_LOGI(TAG, "ServoAngle == 180");
    }
    else
        ESP_LOGI(TAG, "Invalid value");

}