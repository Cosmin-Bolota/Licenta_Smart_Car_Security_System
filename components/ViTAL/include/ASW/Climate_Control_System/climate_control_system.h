#ifndef COMPONENTS_VITAL_ASW_CLIMATE_CONTROL_SYSTEM_H
#define COMPONENTS_VITAL_ASW_CLIMATE_CONTROL_SYSTEM_H

#include "global.h"

uint8_t u8CalculateComfort(uint8_t u8Temp, uint8_t u8Hum);

void ASW_vTaskDCMsTest(void);
void ASW_vTaskDCMdTest(void);
void ASW_vTaskFanTempTreshold();

#endif
