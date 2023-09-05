#include "BSW/HAL/DC_Motor/dc_motor.h"

#include "BSW/MCAL/PWM/pwm.h"

static const char *TAG = "HAL DC MOTOR";

/*******************************************************************************
 *  Function name    : DCMOT_vChangeSpeed
 *
 *  Description      : Change the DC Motor speed
 *
 *  List of arguments: u32DCMotorSpeed -> PWM duty cycle for speed
 *
 *  Return value     : -
 *
 *******************************************************************************/
void DCMOT_vChangeSpeed(uint32_t u32DCMotorSpeed)
{
	if (u32DCMotorSpeed == DC_MOTOR_STOP) //if the parameter is equal to the filling factor 0
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_STOP); //then change the fill factor to 0
	}
	else if (u32DCMotorSpeed == DC_MOTOR_LOW_SPEED) //if the parameter is equal to the low speed filling factor (filling factor 30)
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_LOW_SPEED); //then change the fill factor to 30
	}
	else if (u32DCMotorSpeed == DC_MOTOR_FULL_SPEED) //if the parameter is equal to 100% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_FULL_SPEED); //then change the fill factor to 100
	}
	else if (u32DCMotorSpeed == DC_MOTOR_20) //if the parameter is equal to 20% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_20); //then change the fill factor to 20
	}
	else if (u32DCMotorSpeed == DC_MOTOR_40) //if the parameter is equal to 40% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_40); //then change the fill factor to 40
	}
	else if (u32DCMotorSpeed == DC_MOTOR_60) //if the parameter is equal to 60% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_60); //then change the fill factor to 60
	}
	else if (u32DCMotorSpeed == DC_MOTOR_80) //if the parameter is equal to 80% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, DC_MOTOR_80); //then change the fill factor to 80
	}
	else
	{
		ESP_LOGE(TAG, "Invalid value");
	}
}

/*******************************************************************************
 *  Function name    : DCMOT_vChangeSpeedReverse
 *
 *  Description      : Change the DC Motor speed in the opposite direction
 *
 *  List of arguments: u32DCMotorSpeed -> PWM duty cycle for speed
 *
 *  Return value     : -
 *
 *******************************************************************************/
void DCMOT_vChangeSpeedReverse(uint32_t u32DCMotorSpeed)
{
	if (u32DCMotorSpeed == DC_MOTOR_STOP) //if the parameter is equal to the filling factor 0
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_STOP); //then change the fill factor to 0
	}
	else if (u32DCMotorSpeed == DC_MOTOR_LOW_SPEED) //if the parameter is equal to the low speed filling factor (filling factor 30)
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_LOW_SPEED); //then change the fill factor to 30
	}
	else if (u32DCMotorSpeed == DC_MOTOR_FULL_SPEED) //if the parameter is equal to 100% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_FULL_SPEED); //then change the fill factor to 100
	}
	else if (u32DCMotorSpeed == DC_MOTOR_20) //if the parameter is equal to 20% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_20); //then change the fill factor to 20
	}
	else if (u32DCMotorSpeed == DC_MOTOR_40) //if the parameter is equal to 40% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_40); //then change the fill factor to 40
	}
	else if (u32DCMotorSpeed == DC_MOTOR_60) //if the parameter is equal to 60% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_60); //then change the fill factor to 60
	}
	else if (u32DCMotorSpeed == DC_MOTOR_80) //if the parameter is equal to 80% of fill factor
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, DC_MOTOR_80); //then change the fill factor to 80
	}
	else
	{
		ESP_LOGE(TAG, "Invalid value");
	}
}