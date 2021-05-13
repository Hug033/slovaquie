/* 
* UvSensor.cpp
*
* Created: 11.5.2021 23:18:51
* Author: lukas
*/


#include "UvSensor.h"

// default constructor
UvSensor::UvSensor()
{
} //UvSensor

// default destructor
UvSensor::~UvSensor()
{
} //~UvSensor

int UvSensor::getValue(void)
{
	this->init(4, false);				//divider 16, one conversion
	this->setRef(3);					// 1....AVcc, 3.3 V    3....1.1V = 1023
	this->setChannel(6);
	_delay_ms(1);
	return( this->getAdc());
}