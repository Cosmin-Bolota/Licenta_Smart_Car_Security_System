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

#ifndef COMPONENTS_VITAL_BSW_HAL_DC_MOTOR_H
#define COMPONENTS_VITAL_BSW_HAL_DC_MOTOR_H

#include "global.h"

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
void DCMOT_vChangeSpeed(uint32_t u32DCMotorSpeed);

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
void DCMOT_vChangeSpeedReverse(uint32_t u32DCMotorSpeed);

/* Motor PWMs for speeds */
#define DC_MOTOR_STOP 0
#define DC_MOTOR_LOW_SPEED 15000
#define DC_MOTOR_FULL_SPEED 20000

#define DC_MOTOR_20 4000
#define DC_MOTOR_40 8000
#define DC_MOTOR_60 12000
#define DC_MOTOR_80 16000

#endif