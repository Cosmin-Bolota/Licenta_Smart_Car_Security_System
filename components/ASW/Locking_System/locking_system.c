#include "ASW/Locking_System/locking_system.h"
#include "BSW/HAL/RFID/rc522.h"
#include "RTE/rte.h"
#include "BSW/MCAL/GPIO/gpio.h"

static const char *TAG = "ASW LOCK";

void ASW_vTaskDoorLockCheck()
{
    if(RTE_bGet_ButtonDoorLockStatus())
    {
        RTE_vSet_Locked(true);
        if(RTE_bGet_ButtonSecurityStatus())
        {
            RTE_vSetShiftRegisterOutput(LOCK_RED, ON);
            RTE_vSetShiftRegisterOutput(LOCK_GREEN, ON);
        }
        else
        {
            RTE_vSetShiftRegisterOutput(LOCK_RED, ON);
            RTE_vSetShiftRegisterOutput(LOCK_GREEN, OFF);
        }
    }
    else{
        RTE_vSet_Locked(false);
        RTE_vSetShiftRegisterOutput(LOCK_RED, OFF);
        RTE_vSetShiftRegisterOutput(LOCK_GREEN, ON);
    }
}

//----------------------------------------------------------------------
uint8_t sk1[5] = {0xe9, 0xe5, 0x97, 0xc1, 0x5a};
uint8_t sk2[5] = {0xc6, 0xa1, 0xbe, 0x2b, 0xf2};

void tag_handler(uint8_t* sn) { // serial number is always 5 bytes long
    ESP_LOGI(TAG, "KEY ID : %#x %#x %#x %#x %#x",
        sn[0], sn[1], sn[2], sn[3], sn[4]
    );
    
	bool ok = 1;
    bool lockStatus = RTE_bGet_IsLocked();

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
            lockStatus = !lockStatus;
			ESP_LOGI(TAG, "Access GRANTED! Key card indentified! Car %s", lockStatus?"LOCKED":"UNLOCKED");
			RTE_vSet_Locked(lockStatus);
            RTE_bGet_vSet_ButtonDoorLockStatus(lockStatus);
		}
		else{
			ESP_LOGI(TAG, "Access DENIED! Key UNKNOWN");
		}
	}
	else{
        lockStatus = !lockStatus;
		ESP_LOGI(TAG, "Access GRANTED! Key ring indentified! Car %s", lockStatus?"LOCKED":"UNLOCKED");
		RTE_vSet_Locked(lockStatus);
        RTE_bGet_vSet_ButtonDoorLockStatus(lockStatus);
	}
}

void LOCK_vInit()
{
    const rc522_start_args_t start_args = {
        .miso_io = 37,
        .mosi_io = 35,
        .sck_io  = 36,
        .sda_io  = 34,
        .callback = &tag_handler,
        // Uncomment next line for attaching RC522 to SPI2 bus. Default is VSPI_HOST (SPI3)
        .spi_host_id = HSPI_HOST
    };
    // To reset the RFID
    GPIO_vSetDirection(RC522_RST_PIN, DIR_OUTPUT);
    GPIO_vSetLevel(RC522_RST_PIN, LOW_LEVEL);
    GPIO_vSetLevel(RC522_RST_PIN, HIGH_LEVEL);

    rc522_start(start_args);
}