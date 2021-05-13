/*
* Uvod2.cpp
*
* Created: 13.5.2020 21:22:25
* Author : hugob
*/

#include "Led.h"
#include "Button.h"
#include "Display.h"
#include "Uart.h"
#include "Buzzer.h"
#include "DHT.h"

int main(void)
{
	Led rgb;
	rgb.set(1,0,0); // Led rouge

	Button btn;
	Display dsp;
	Uart serial;
	DHT dht;
	Buzzer buzz;
	
	dsp.show(0); // Set display to default
	printf ("Initialize :) \r\n");
	//printf ("*********************************\r\n");
	printf("AT+CWMODE=1\r\n");
	_delay_ms(200);
	//printf("AT+CWJAP=\"Livebox-49F0\",\"*lescarottessontcuites*\"\r\n");
	printf("AT+CWJAP=\"reseau_partage\",\"123unedeuxtrois\"\r\n");

	_delay_ms(6000);
	printf("AT+CIPMUX=1\r\n");
	_delay_ms(200);
	rgb.set(0,1,0); // Led verte
	buzz.setBuzz(1000); // Buzz indicates the connection is Ok
	
	while (1)
	{
		
		//_delay_ms(60000);	
		while(!btn.isPressed()){}
		rgb.set(1,1,0);	// yellow The led indicates that the module is sending first request
		
		/// FIRST REQUEST
		dsp.show(1); // Set display for first step(humidity)
		uint8_t hum = dht.getHum(); // Get humidity
		printf("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");
		_delay_ms(200);
		printf("AT+CIPSEND=0,49\r\n");
		_delay_ms(200);
		printf("GET /update?api_key=7IQV2A0JQYCOPDL0&field2=%d\n\r", hum); // Send to Thingspeak API
		
				/// FIRST REQUEST END

		printf("First request end\r\n");
		_delay_ms(3000);
		
		
				/// SECOND REQUEST
		printf("Second request start\r\n");
		rgb.set(1,0,1);	// purple The led indicates that the module is sending second request
		buzz.setBuzz(500);
		printf("AT+CIPMUX=1\r\n");
		_delay_ms(1000);
		dsp.show(2); // Set display for second step(temperature)
		uint8_t temp = dht.getTemp(); // Get temperature
		
		_delay_ms(1000);
		printf("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");
		_delay_ms(200);
		printf("AT+CIPSEND=0,49\r\n");
		_delay_ms(200);
		printf("GET /update?api_key=7IQV2A0JQYCOPDL0&field1=%d\n\r", temp); // Send to Thingspeak API 		
		
		printf("Second request end");
		_delay_ms(3000);
		
		rgb.set(0,0,1); // blue when it's done
		dsp.show(0); // Set display to default	
	}
};