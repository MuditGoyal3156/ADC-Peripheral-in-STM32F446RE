/*
 * ADC.h
 *
 *  Created on: Dec 29, 2025
 *      Author: mudit
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <Addresses.h>

#define GPIOAEN          (1U << 0)

void ADC_Init(void);
void ADC_Start(void);

uint16_t ADC_value(void);

#endif /* ADC_H_ */
