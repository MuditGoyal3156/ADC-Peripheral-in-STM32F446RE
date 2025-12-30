/*
 *
 *  Created on: Dec 30, 2025
 *      Author: mudit
 */

#include "Multi_ADC.h"

void ADC_CLOCK_EN(void)
{
	//Enable ADC1 Clock
	RCC_APB2ENR |= ( 1 << 8);

	//Enable ADC2 Clock
	RCC_APB2ENR |= ( 1 << 9);

	// Dummy read to force a delay for clock stabilization
	volatile uint32_t delay_clk = RCC_APB2ENR;
	(void)delay_clk;
}

void ADC_Init(void)
{
	//Configure ADC GPIO pin
	//Enable clock access to GPIOA
	RCC_AHB1ENR |= GPIOAEN;

	//Set PA0 and PA1 Mode as Analog
	GPIOA_MODER |= (3 << 0)|(3 << 2);


	//Configure ADC1 registers
	//Set conversion sequence start
	ADC1_SQR3 &= ~(0x1F << 0);	//First 5 bits reset to 0(PA0)

	// Set conversion sequence length
	ADC1_SQR1 &= ~(0xF << 20);

	// Set sampling time for channel 0 (PA0)
	ADC1_SMPR2 &= ~(7 << 0);
	ADC1_SMPR2 |=  (7 << 0);

	//Enable ADC Module
	ADC1_CR2 |= (1 << 0);



	//Configure ADC2 registers
	//Set conversion sequence start
	ADC2_SQR3 &= ~(0x1F << 0);	//First 5 bits reset to 0(PA1)
	ADC2_SQR3 |= (0x1 << 0);

	// Set conversion sequence length
	ADC2_SQR1 &= ~(0xF << 20);

	// Set sampling time for channel 1 (PA1)
	ADC2_SMPR2 &= ~(7 << 3);
	ADC2_SMPR2 |=  (7 << 3);

	//Enable ADC Module
	ADC2_CR2 |= (1 << 0);


	// Wait for internal ADC voltage regulator to stabilize
	for(volatile int i=0; i<10000; i++);

}

void ADC_Interruptconfig(void)
{
	NVIC_ISER0 |= (1 << 18); //Enable interrupt

	NVIC_IPR4 &= ~(0xFF << 16);   //Set priority as 0

	//Enable ADC1 Interrupts bits
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

void Multi_Mode(void)
{
	// Enable dual regular simultaneous mode (ADC1 + ADC2)
	ADC_CCR &= ~(0x1F);
	ADC_CCR |= 0x01;   // MULTI = 00001

	// ADC common prescaler = PCLK2 / 4
	ADC_CCR &= ~(3 << 16);
	ADC_CCR |=  (1 << 16);
}

void ADC_IRQ_Handler(uint16_t *Data1,uint16_t *Data2)
{

	/*Overrun Error*/
	if(ADC_CSR & ((1 << 5) | ( 1 << 13)))
	{
		ADC1_SR &= ~(1 << 5);
		ADC2_SR &= ~(1 << 5);
	}

	/*EOC flag*/
	if(ADC_CSR & (1 << 1) )
	{
		*Data1 = (uint16_t)(ADC1_DR & 0xFFFF);
		*Data2 = (uint16_t)(ADC2_DR & 0xFFFF); // ADC2 Data
		ADC1_SR &= ~(1 << 1);
	}
}
