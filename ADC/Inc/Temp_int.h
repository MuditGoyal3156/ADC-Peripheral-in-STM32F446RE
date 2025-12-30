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

#define ADC_IRQ_NO		18

#define VREF        3.3f
#define V25         0.76f
#define AVG_SLOPE   0.0025f   // V/°C

void ADC_Init(void);
void ADC_Start(void);
void ADC_Interruptconfig(void);
float Compute_temp(uint16_t data);
int32_t Compute_temp_x100(uint16_t adc);
void ADC_IRQ_Handler(uint16_t *Data);

#endif /* ADC_H_ */
