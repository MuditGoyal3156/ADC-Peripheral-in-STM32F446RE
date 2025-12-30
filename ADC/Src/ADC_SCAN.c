/*
 *
 *  Created on: Dec 29, 2025
 *      Author: mudit
 */

#include "ADC_SCAN.h"
void ADC_Scan_Init(void)
{
	//Configure ADC GPIO pin

	//Enable clock access to GPIOA
	RCC_AHB1ENR |= GPIOAEN;

	//Set PA0 Mode as Analog
	GPIOA_MODER &= ~(3 << 0);
	GPIOA_MODER |= (3 << 0);

	//Set PA1 Mode as Analog
	GPIOA_MODER &= ~(3 << 2);
	GPIOA_MODER |= (3 << 2);

	//Configure ADC registers

	//Enable ADC1 Clock
	RCC_APB2ENR |= ( 1 << 8);

	//Set conversion sequence start
	ADC1_SQR3 &= ~(0x1F << 0);	//First 5 bits reset to 0(PA0)
	ADC1_SQR3 &= ~(0x1F << 5);	// 5 bits reset to 0(PA1)
	ADC1_SQR3 |=  (1 << 5);	    //5 bits set to 0001(PA1)

	//Set Conversion sequence length
	ADC1_SQR1 &= ~(0xF << 20);	//Bit 20-23 reset to 0
	ADC1_SQR1 |=  (1 << 20);	//Bit 20-23 set to 0001

	//Enable Scan Mode
	ADC1_CR1 |= ( 1 << 8 );

	// Set sampling time for channel 0 (PA0)
	ADC1_SMPR2 &= ~(7 << 0);
	ADC1_SMPR2 |=  (7 << 0);

	// Set sampling time for channel 1 (PA1)
	ADC1_SMPR2 &= ~(7 << 3);
	ADC1_SMPR2 |=  (7 << 3);


	//Enable EOCS
	ADC1_CR2 |= (1 << 10);

	//Enable ADC Module
	ADC1_CR2 |= (1 << 0);

}

void ADC_Scan_Start(void)
{
	//Start conversion
	ADC1_CR2 |= (1 << 30);
}


uint16_t ADC_value(void)
{
	//Wait for conversion to finish
	while(!(ADC1_SR & (0x2)));

	//Read Data register and return the value
	return (uint16_t)(ADC1_DR & 0x0FFF);
}
