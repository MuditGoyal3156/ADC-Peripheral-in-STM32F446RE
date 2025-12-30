/*
 * ADC.c
 *
 *  Created on: Dec 29, 2025
 *      Author: mudit
 */

#include "ADC.h"
void ADC_Init(void)
{
	//Configure ADC GPIO pin

	//Enable clock access to GPIOA
	RCC_AHB1ENR |= GPIOAEN;

	//Set PA0 Mode as Analog
	GPIOA_MODER &= ~(3 << 0);
	GPIOA_MODER |= (3 << 0);

	//Configure ADC registers

	//Enable ADC1 Clock
	RCC_APB2ENR |= ( 1 << 8);

	//Set conversion sequence start
	ADC1_SQR3 &= ~(0xF << 0);	//First 4 bits reset to 0

	//Set Conversion sequence length
	ADC1_SQR1 &= ~(0xF << 20);	//Bit 20-23 reset to 0

	// Set sampling time for channel 0 (PA0)
	ADC1_SMPR2 &= ~(7 << 0);
	ADC1_SMPR2 |=  (7 << 0);

	//Enable continuous conversion mode
	ADC1_CR2 |= (1 << 1);	//Bit 1

	//Enable ADC Module
	ADC1_CR2 |= (1 << 0);	//Bit 0

}

void ADC_Start(void)
{
	//Start conversion
	ADC1_CR2 |= (1 << 30);	//Bit 30
}


uint16_t ADC_value(void)
{
	//Wait for conversion to finish
	while(!(ADC1_SR & (0x2)));//Bit 1

	//Read Data register and return the value

	return (uint16_t)(ADC1_DR & 0x0FFF);
}
