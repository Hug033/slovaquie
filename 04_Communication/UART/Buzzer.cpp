/* 
* Buzzer.cpp
*
* Created: 13/05/2021 11:19:26
* Author: hugob
*/


#include "Buzzer.h"

// default constructor
Buzzer::Buzzer()
{
	sbi(DDRB,BUZZ);    //set PB2 as output
} //Buzzer

// default destructor
Buzzer::~Buzzer()
{
} //~Buzzer

void Buzzer::setBuzz(int time)
{
	for(int i=0; i<time; i++)
	{
		tbi(PORTB,BUZZ);                 //cycle duration cca 1ms
		_delay_us(300);
		tbi(PORTB,BUZZ);
		_delay_us(300);
	}
	cbi(PORTB,BUZZ);
}