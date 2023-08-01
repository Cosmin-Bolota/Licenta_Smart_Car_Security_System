#ifndef COMPONENTS_VITAL_BSW_MCAL_ADC_H
#define COMPONENTS_VITAL_BSW_MCAL_ADC_H

#include "global.h"

/*******************************************************************************
 *  Function name    : ADC_vInit
 *
 *  Description      : Initial configuration of MCAL ADC
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void ADC_vInit(void);

/*******************************************************************************
 *  Function name    : ADC_u16Read
 *
 *  Description      : Read of ADC value
 *
 *  List of arguments: -
 *
 *  Return value     : uint16_t -> ADC value
 *
 *******************************************************************************/
uint16_t ADC_u16Read(void);

#endif
