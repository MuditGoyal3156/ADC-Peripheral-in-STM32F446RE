/*
 *
 *  Created on: Dec 29, 2025
 *      Author: mudit
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <Addresses.h>

#define GPIOAEN          (1U << 0)

void ADC_Scan_Init(void);
void ADC_Scan_Start(void);
uint16_t ADC_value(void);

#endif /* ADC_H_ */
