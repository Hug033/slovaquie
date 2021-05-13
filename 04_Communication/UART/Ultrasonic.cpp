/* 
* Ultrasonic.cpp
*
* Created: 11.5.2021 23:34:22
* Author: lukas
*/


#include "Ultrasonic.h"

// default constructor
Ultrasonic::Ultrasonic()
{
	sbi(DDRC,TRIG);				/* set TRIG pin as output, pin is shared with user BUTTON pin */
	cbi(PORTC,TRIG);			/* Clear pin */
	cbi(DDRC, ECHO);			/* Set ECHO pin as input */
} //Ultrasonic

// default destructor
Ultrasonic::~Ultrasonic()
{
} //~Ultrasonic

uint16_t Ultrasonic::getDistance()
{
	sbi(DDRC,TRIG);				/* set TRIG pin as output, pin is shared with user BUTTON pin */
	cbi(PORTC,TRIG);			/* Clear pin */
	
	uint16_t duration=0;
	sbi(PORTC,TRIG);			/* Set TRIG pin */
	_delay_us(10);				/* impulse */
	cbi(PORTC,TRIG);			/* Clear TRIG pin */
	
	//	printf("Impulse \r\n");
	uint16_t pom = 0;
	while((PINC & (1<<ECHO)) != (1<<ECHO)) /* waiting for response */
	{
		_delay_us(1);
		pom++;
		if (pom>2000)					  /* ERROR - not received response */	
			return 0;
	}
	
	while((PINC & (1<<ECHO)) == (1<<ECHO))
	{
		duration++;
		_delay_us(58);			/* 1cm = 58 us */
	}
	return duration;
}