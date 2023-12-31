#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"

#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/HAL/Com/com.h"

extern COM_GET_struct g_GET_DataStructure;

static const char *TAG = "HAL PROXIMITY SENSOR";

/*******************************************************************************
 *  Function name    : PROX_vRequest
 *
 *  Description      : Send a pulse on the trigger pin
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void PROX_vRequest(void)
{
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
	ets_delay_us(2);
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, HIGH_LEVEL);
	ets_delay_us(10);
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
}

/*******************************************************************************
 *  Function name    : PROX_u16Read
 *
 *  Description      : Measure echo time and convert it to distance
 *
 *  List of arguments: -
 *
 *  Return value     : uint16_t -> Distance in cm
 *
 *******************************************************************************/
uint16_t PROX_u16Read(void)
{
	PROX_vRequest();
	uint16_t count = 0;
	bool ok = 1;

	while (GPIO_iGetLevel(HC_SR04_ECHO_PIN) == 0 && ok){
		count++;
		if(count >65534){
			ok = 0;
		}
	}

	int64_t echo_start = esp_timer_get_time();
	if(ok){
		count = 0;
	}
	while (GPIO_iGetLevel(HC_SR04_ECHO_PIN) && ok){
		count++;
		if(count >65534){
			ok = 0;
		}
	}
	if(ok){
		g_GET_DataStructure.u8Distance = (((esp_timer_get_time() - echo_start) * 0.0343) / 2);
		return (uint16_t) (((esp_timer_get_time() - echo_start) * 0.0343) / 2);
	}
	else{
		return 0;
	}
	
}
