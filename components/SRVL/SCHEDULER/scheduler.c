#include "SRVL/SCHEDULER/scheduler.h"

#include "BSW/MCAL/ADC/adc.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/MCAL/PWM/pwm.h"
#include "BSW/MCAL/WIFI/wifi.h"

#include "BSW/HAL/Com/com.h"
#include "BSW/HAL/Photo_Resistor/photo_resistor.h"
#include "BSW/HAL/Temp_Sensor/temp_sensor.h"
#include "BSW/HAL/RFID/rc522.h"

#include "RTE/rte.h"

#include "BSW/HAL/Shift_Register/shift_register.h"
#include "ASW/Ambient_Light/ambient_light.h"
#include "ASW/Climate_Control_System/climate_control_system.h"
#include "ASW/Headlights/headlights.h"
#include "ASW/Horn/horn.h"
#include "ASW/Locking_System/locking_system.h"
#include "ASW/Security/security.h"
#include "ASW/Trunk/trunk.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"


#include "nvs_flash.h"

static const char *TAG = "SRVL SCHEDULER";
static httpd_handle_t server = NULL;

uint8_t sk1[5] = {0xe9, 0xe5, 0x97, 0xc1, 0x5a};
uint8_t sk2[5] = {0xc6, 0xa1, 0xbe, 0x2b, 0xf2};

void tag_handler(uint8_t* sn) { // serial number is always 5 bytes long
    ESP_LOGI(TAG, "KEY ID : %#x %#x %#x %#x %#x",
        sn[0], sn[1], sn[2], sn[3], sn[4]
    );
	bool ok = 1;
	for(uint8_t i=0;i<5;i++){
		if(sn[i]!=sk1[i])
			ok = 0;
	}
	if(!ok){
		ok = 1;
		for(uint8_t i=0;i<5;i++){
		if(sn[i]!=sk2[i])
			ok = 0;
		}
		if(ok){
			ESP_LOGI(TAG, "Access GRANTED! Key card indentified");
			RTE_vSet_Locked(0);
		}
		else{
			ESP_LOGI(TAG, "Access DENIED! Key UNKNOWN");
		}
	}
	else{
		ESP_LOGI(TAG, "Access GRANTED! Key ring indentified");
		RTE_vSet_Locked(0);
	}
}

void SYSTEM_vInit(void)
{
    /* Call these functions only when specific HW parts are connected */
    
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);


	/* Initialize All periferials */
	ADC_vInit();

	GPIO_vInit();

	PWM_vInit();
	
	WIFI_vInit(&server);

	const rc522_start_args_t start_args = {
        .miso_io = 37,
        .mosi_io = 35,
        .sck_io  = 36,
        .sda_io  = 34,
        .callback = &tag_handler,

        // Uncomment next line for attaching RC522 to SPI2 bus. Default is VSPI_HOST (SPI3)
        .spi_host_id = HSPI_HOST
    };

    rc522_start(start_args);
}

void vTask100ms(void)
{	
	/* Send and receive data to the HTML interface -- get and post functions*/
	COM_vTaskProcessServer();
}
 
void vTask200ms(void)
{

}

void vTask500ms(void)
{
	ASW_vTaskBuzzer();	//Honk
	
	/* Call proximity sensor functionality */
	PROX_u16Read();			//Distance
	
	ASW_vTaskTrunkCheck();
}

void vTask800ms(void)
{
	ASW_vTaskAmbientalLight();
	
	/* Call Find my car functionality */
	ASW_vTaskFindMyCar();
} 

void vTask1000ms(void)
{
	/* Calculate the photoresistor returned value */
	PHRES_vTaskCalculate();
	
	ASW_vTaskHeadLightControl();
	
	ASW_vTaskFanTempTreshold();
	
	ASW_vTaskDoorLockCheck();
} 

void vTask2000ms(void)
{
	/* Call CheckDriver seat  */
	ASW_vTaskCheckDriver();
}

void vTask5000ms(void)
{
	/* Calculate the temperature from DHT 11 Sensor */
	DHT11_vTaskTempAndHumCalculate();
}

void SYSTEM_vTaskScheduler(void)
{
	uint16_t u16TickCount = 0;
	while (1)
	{

		if (u16TickCount % TASK_100MS == 0)
		{
			vTask100ms();
			
			
		}

		if (u16TickCount % TASK_200MS == 0)
		{
			vTask200ms();
			
			
		}

		if (u16TickCount % TASK_500MS == 0)
		{
			vTask500ms();	
			
		}
		
		if (u16TickCount % TASK_800MS == 0)
		{
			vTask800ms();
			
		}

		if (u16TickCount % TASK_1000MS == 0)
		{
			vTask1000ms();
			
		}

		if (u16TickCount % TASK_2000MS == 0)
		{
			vTask2000ms();	
			
		}

		if (u16TickCount % TASK_5000MS == 0)
		{
			vTask5000ms();
			
		}

		u16TickCount++;
		if (u16TickCount >= TASK_5000MS)
		{
			u16TickCount = 0;
		}
			
		vTaskDelay(100); // 1 sec 
		
	}
}
