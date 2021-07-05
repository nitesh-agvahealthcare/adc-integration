#define F_CPU 4000000UL
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "libraries/UART_1_AVR128DA64.h"
#include "libraries/ADC_AVR128DA64.h"
#include "libraries/RTC_AVR128DA64.h"


int tempi = 0;
unsigned long currentmillis = 0, previousmillis = 0;

uint8_t ADC_selected_channel, upper_threshold;
uint16_t ADC_value;

int main(void)
{
	sei();
	
	USART1_init(9600); 
	
	ADC0.WINHT = 15;
	ADC0.INTCTRL |= (1 << 1);  // Window Comparator Interrupt Enable
	ADC0.CTRLE = 0x2;          //RESULT > WINHT
	ADC_selected_channel = channel_1;
	ADC0_init();
	set_millis();
    while (1) 
    {
		ADC_value = ADC0_read(ADC_selected_channel);
		//USART1_sendInt(ADC_value);
	}
}

ISR(ADC0_WCMP_vect)
{
	currentmillis = millis;
	if ((currentmillis - previousmillis) > 50)
	{
		tempi ++ ;
		USART1_sendInt(tempi);
	}
	previousmillis = millis;
	//ADC0.INTFLAGS |= (1 << 1);   // Bit 1 – WCMP Window Comparator Interrupt Flag
}