/*
* Uvod2.cpp
*
* Created: 21.1.2020 13:19:25
* Author : Lukas
*/

#include "Led.h"
#include "Button.h"
#include "Display.h"
#include "Uart.h"
#include "DHT.h"

int main(void)
{
	Led rgb;
	rgb.set(1,0,0); // Led rouge

	Button btn;
	Display dsp;		
	Uart serial;		
	DHT dht;
	

	printf ("COUCOU :) \r\n");
	printf("AT+CWMODE=1\r\n");
	_delay_ms(200);
	printf("AT+CWJAP=\"reseau_partage\",\"123unedeuxtrois\"\r\n");
	_delay_ms(6000);
	printf("AT+CIPMUX=1\r\n");
	_delay_ms(200);	
	rgb.set(0,1,0); // Led verte
		
	while (1)
	{
	//printf(""+dht.getTemp());
	//dht.printValues();
	//printf("%d\r\n", dht.getTemp());
		_delay_ms(200);
		
		while(!btn.isPressed()){}	
		printf("button is pressed");
		printf("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");
		_delay_ms(200);
		printf("AT+CIPSEND=0,49\r\n");
		_delay_ms(200);
		printf("GET /update?api_key=8TWTRTQNRX8KX7EU&field1=120\n\r");

		printf("Should be entry");
		rgb.set(0,1,1);
// 		char str1[] = "GET /update?api_key=8TWTRTQNRX8KX7EU&field1=120\n\r";
// 		printf("AT+CIPSEND=0,%d\r\n", (unsigned)strlen(str1));
// 		_delay_ms(2000);
// 		printf("GET /update?api_key=8TWTRTQNRX8KX7EU&field1=120\n\r");
		//printf("" + dht.getTemp());
	}
}

;