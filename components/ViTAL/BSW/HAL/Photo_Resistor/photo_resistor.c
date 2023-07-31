#include "BSW/HAL/Photo_Resistor/photo_resistor.h"

#include "BSW/MCAL/ADC/adc.h"

#include "BSW/HAL/Com/com.h"

#include "ASW/Headlights/headlights.h"

extern COM_GET_struct g_GET_DataStructure;

static const char *TAG = "HAL PHOTO RESISTOR";

/*******************************************************************************
 *  Function name    : PHRES_u16Read
 *
 *  Description      : Get the ADC value for the Photo Resistor
 *
 *  List of arguments: -
 *
 *  Return value     : uint16_t -> Photo resistor value
 *
 *******************************************************************************/
uint16_t PHRES_u16Read(void)
{
	return ADC_u16Read()*100/8191;
}

/*******************************************************************************
 *  Function name    : PHRES_vTaskCalculate
 *
 *  Description      : Calculate and update PHRES value
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void PHRES_vTaskCalculate(void)
{
	uint16_t u8PhResData = PHRES_u16Read();

	// Calcul /15 ?
	g_GET_DataStructure.u16PhotoRes = PHRES_u16Read();

	// Send the photoresistor value in monitor terminal
	ESP_LOGI(TAG, "Checksum: %d%%", u8PhResData);
}
	
