/* 
* DHT.cpp
*
* Created: 11.5.2021 22:34:55
* Author: lukas
*/


#include "DHT.h"

// default constructor
DHT::DHT()
{
} //DHT

// default destructor
DHT::~DHT()
{
} //~DHT

uint32_t DHT::getValue(void)
{
	//************************** Sampling period > 1s ****************

	uint8_t Hum1 = 0;							 //  Hum1.Hum2
	uint8_t Hum2 = 0;
	uint8_t Temp1 = 0;							//  Temp1.Temp2
	uint8_t Temp2 = 0;
	uint8_t Parita = 0;
	
	sbi(PORTB,DHTV);							// H
	sbi(DDRB,DHTV);								//DHT set output
	_delay_us(50);								// stab
	cbi(PORTB,DHTV);							//start transmission
	_delay_ms(22);								// min 18 ms
	cbi(DDRB,DHTV);								//DHT set input
	_delay_us(2);
	while((PINB & 0x1) == 1);					//wait for response DHT L 80us
	_delay_us(2);
	while((PINB & 0x1) == 0);					// wait for H  (20 - 40 us)
	_delay_us(2);
	while((PINB & 0x1) == 1);					//wait for response DHT L 80us
	_delay_us(2);								// start trans. first bit

	/**************************************************************RH****/
	for(uint8_t i = 0; i<8; i++)
	{
		while((PINB & 0x1) == 0);				// wait for H
		_delay_us(53);
		Hum1 = Hum1 | (PINB & 0x1);
		if((Hum1 & 0x1) == 1) _delay_us(37);   //if H wait 37us
		if (i !=7 ) Hum1 = Hum1<<1;
	}

	for(uint8_t i = 0; i<8; i++)
	{
		while((PINB & 0x1) == 0);				// wait for H
		_delay_us(53);
		Hum2 = Hum2 | (PINB & 0x1);
		if((Hum2 & 0x1) == 1) _delay_us(37);   //if H wait 37us
		if (i !=7 ) Hum2 = Hum2<<1;
	}

	/**********************************************************TEMP****/
	for(uint8_t i = 0; i<8; i++)
	{
		while((PINB & 0x1) == 0);				// wait for H
		_delay_us(53);
		Temp1 = Temp1 | (PINB & 0x1);
		if((Temp1 & 0x1) == 1) _delay_us(37);   //if H wait 37us
		if (i !=7 ) Temp1 = Temp1<<1;
	}

	for(uint8_t i = 0; i<8; i++)
	{
		while((PINB & 0x1) == 0);				// wait for H
		_delay_us(53);
		Temp2 = Temp2 | (PINB & 0x1);
		if((Temp2 & 0x1) == 1) _delay_us(37);   //if H wait 37us
		if (i !=7 ) Temp2 = Temp2 << 1;
	}

	/*************************************************PARITA***********/
	for(uint8_t i = 0; i<8; i++)
	{
		while((PINB & 0x1) == 0);				// wait for H
		_delay_us(53);
		Parita = Parita | (PINB & 0x1);
		if((Parita & 0x1) == 1) _delay_us(37);	// if H wait 37us
		if (i !=7 ) Parita = Parita << 1;
	}
	
	if((Hum1+Hum2+Temp1+Temp2) != Parita) return 0;
	
	uint32_t x = Hum1;
	x = x << 8;									// x: Hum1 Hum2 Temp1 Temp2   32bit
	x = x | Hum2;	
	x = x << 8;
	x = x | Temp1;
	x = x << 8;
	x = x | Temp2;
	return x;
}

void DHT::printValues()
{
	uint8_t pom;
	uint32_t x = getValue();				//Hum1.Hum2 Temp1.Temp2
	
	if(x == 0)
		printf("ERROR\n\r"); 
	else
	{
		uint32_t y = x;
		y = y >> 24;
		pom = (uint8_t)y;
		printf("Humidity : %d.",pom);
		y = x;
		y = y >> 16;
		pom = (uint8_t)y;
		printf("%d %%\r\n",pom);

		y = x;
		y = y >>8;
		pom = (uint8_t)y;
		printf("Temp     : %d.",pom);
		pom = (uint8_t)x;
		printf("%d degrees Celsius\r\n",pom);
	}
	
}

uint8_t DHT::getTemp(void)
{
	uint32_t x = getValue();
	
	if(x != 0)
	{
		uint32_t y = x;
		y = y >>8;
		return (uint8_t)y;
	}
	return 0;
};


uint8_t DHT::getHum(void)
{
	uint32_t x = getValue();
	
	if(x != 0)
	{
		uint32_t y = x;
		y = y >> 24;
		return (uint8_t)y;
	}
	return 0;
};