/*
 *
 *  Created on: Dec 29, 2025
 *      Author: mudit
 */

#include "ADC_WatchDog.h"

uint8_t LED_STATE = (1 << 5);
void LED_Init(void)
{
	//Enable clock access to GPIOA
	RCC_AHB1ENR |= GPIOAEN;

	//Set PA5 Mode as output
	GPIOA_MODER &= ~(3 << 10);
	GPIOA_MODER |= (1 << 10);
}


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
	ADC1_SQR3 &= ~(0x1F << 0);	//First 5 bits reset to 0(PA0)

	// Set sampling time for channel 0 (PA0)
	ADC1_SMPR2 &= ~(7 << 0);
	ADC1_SMPR2 |=  (7 << 0);

	//Enable continuous conversion mode
	ADC1_CR2 |= (1 << 1);	//Bit 1

	//Enable ADC Module
	ADC1_CR2 |= (1 << 0);

}

void ADC_Interruptconfig(void)
{
	NVIC_ISER0 |= (1 << 18); //Enable interrupt

	NVIC_IPR4 &= ~(0xFF << 16);   //Set priority as 0

	//Enable ADC Interrupts bits
	//Enable EOCIE
	ADC1_CR1 |= (1 << 5);

	//Enable OVRIE
	ADC1_CR1 |= (1 << 26);
}
void ADC_Start(void)
{
	//Start conversion
	ADC1_CR2 |= (1 << 30);
}

void ADC_Watchdog(void)
{
	//Enable WatchDog
	ADC1_CR1 |= (1 << 23);

	//Enable interrupt
	ADC1_CR1 |= (1 << 6);

	//Set Higher and Lower Threshold
	ADC1_LTR = 1000;
	ADC1_HTR = 3000;

	/* Needed only if Scan mode is enabled */
	//Enable Single channel mode
	ADC1_CR1 |= (1 << 9);

	//Configure channel to monitor
	// Select channel 0 (PA0)
	ADC1_CR1 &= ~(0x1F << 0);
}

void ADC_IRQ_Handler(uint16_t *Data)
{
	/* Analog WatchDog */
	if(ADC1_SR & (1 << 0))
	{
		ADC1_SR &= ~(1 << 0);
		GPIOA_ODR |= LED_STATE;
	}
	/*Overrun Error*/
	if(ADC1_SR & (1 << 5))
	{
		ADC1_SR &= ~(1 << 5);
	}

	/*EOC flag*/
	if(ADC1_SR & (1 << 1))
	{
		*Data = (ADC1_DR & 0x0FFF);
	}
}
