#include "BSW/HAL/Buzzer/buzzer.h"

#include "BSW/MCAL/PWM/pwm.h"

static const char *TAG = "HAL BUZZER";

/*******************************************************************************
 *  Function name    : BUZZER_vChangeDutyCycle
 *
 *  Description      : Change the Buzzer sound
 *
 *  List of arguments: u32BuzzerDutyCycle -> PWM duty cycle for sound
 *
 *  Return value     : -
 *
 *******************************************************************************/
void BUZZER_vChangeDutyCycle(uint32_t u32BuzzerDutyCycle)
{
	if (u32BuzzerDutyCycle == BUZZER_PWM_STOP) //if the parameter is equal to the fill factor 0
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_STOP); //buzzer with a duty cycle of 0%
	}
	else if (u32BuzzerDutyCycle == BUZZER_PWM_START) //if the parameter is equal to the fill factor 20%
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_START); //buzzer with a duty cycle of 20%
	}
	else if (u32BuzzerDutyCycle == BUZZER_PWM_LVL2) //if the parameter is equal to the fill factor 40%
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_LVL2); //buzzer with a duty cycle of 40%
	}
	else if (u32BuzzerDutyCycle == BUZZER_PWM_LVL3) //if the parameter is equal to the fill factor 60%
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_LVL3); //buzzer with a duty cycle of 60%
	}
	else if (u32BuzzerDutyCycle == BUZZER_PWM_LVL4) //if the parameter is equal to the fill factor 80%
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_LVL4); //buzzer with a duty cycle of 80%
	}
	else if (u32BuzzerDutyCycle == BUZZER_PWM_LVL5) //if the parameter is equal to the fill factor 100%
	{
		PWM_vSetDutyCycle(BUZZER_PWM_CHANNEL, BUZZER_PWM_LVL5); //buzzer with a duty cycle of 100%
	}
	else
	{
		ESP_LOGW(TAG, "Invalid value");
	}
}
