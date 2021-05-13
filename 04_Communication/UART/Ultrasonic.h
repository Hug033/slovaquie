/* 
* Ultrasonic.h
*
* Created: 11.5.2021 23:34:22
* Author: lukas
*/


#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include "Board.h"

class Ultrasonic
{
//variables
public:
protected:
private:

//functions
public:
	Ultrasonic();
	~Ultrasonic();
	uint16_t getDistance();
protected:
private:
	Ultrasonic( const Ultrasonic &c );
	Ultrasonic& operator=( const Ultrasonic &c );

}; //Ultrasonic

#endif //__ULTRASONIC_H__
