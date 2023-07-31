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

#ifndef COMPONENTS_VITAL_BSW_HAL_PROXIMITY_SENSOR_H
#define COMPONENTS_VITAL_BSW_HAL_PROXIMITY_SENSOR_H

#include "global.h"

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
void PROX_vRequest(void);

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
uint16_t PROX_u16Read(void);

#endif
