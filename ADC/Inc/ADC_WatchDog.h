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

void LED_Init(void);


void ADC_Init(void);
void ADC_Start(void);
void ADC_Interruptconfig(void);
void ADC_Watchdog(void);
void ADC_IRQ_Handler(uint16_t *Data);

#endif /* ADC_H_ */
