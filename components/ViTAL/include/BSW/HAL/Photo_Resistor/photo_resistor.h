/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/

#ifndef COMPONENTS_VITAL_BSW_HAL_PHOTO_RESISTOR_H
#define COMPONENTS_VITAL_BSW_HAL_PHOTO_RESISTOR_H

#include "global.h"

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
uint16_t PHRES_u16Read(void);

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
void PHRES_vTaskCalculate(void);

#endif
