#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "libraries/UART_1_AVR128DA64.h"
#include "libraries/ADC_AVR128DA64.h"

int main (void)
{
	int samples = 0;   
	int total_samples = 100; //Total samples of adc values
	
	uint32_t adc_value = 0; // A variable to store the adc value
	
	float analog_ref_volt = 3.3; //Analog reference voltage
	float battery_volt, avg;
	
	USART1_init(9600);  //initializing the USART
	ADC0_init();        //initializing the ADC
	
	while (1)
	{				
		//Voltage calculation
		for (samples=0; samples<total_samples; samples++)
		{
			adc_value = adc_value + ADC0_read(channel_1); //reading the adc channel 0	
//			USART1_sendInt(adc_value);
			_delay_ms(10);			
		}
 		
// 		USART1_sendInt(adc_value);
// 		USART1_sendFloat(adc_value, 4);
		
		avg = adc_value / total_samples;
		battery_volt = (avg * analog_ref_volt * 1000)/4095.0;  // Equation to calculate battery voltage in mV
		adc_value = 0;             // Reset the value to zero             
		
		USART1_sendString("Battery Voltage:");
		USART1_sendFloat(battery_volt, 2);
	}
}