#include "BSW/MCAL/ADC/adc.h"

#include "driver/adc.h"

static const char *TAG = "MCAL ADC";

void ADC_vInit(void)
{
	ESP_ERROR_CHECK(adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_0));
}

uint16_t ADC_u16Read(void)
{
	return (uint16_t)adc1_get_raw(ADC_CHANNEL_0);
}
