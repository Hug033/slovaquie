/* 
* UvSensor.h
*
* Created: 11.5.2021 23:18:51
* Author: lukas
*/


#ifndef __UVSENSOR_H__
#define __UVSENSOR_H__

#include "Board.h"
#include "Adc.h"

class UvSensor:Adc
{
//variables
public:
protected:
private:

//functions
public:
	UvSensor();
	~UvSensor();
	int getValue(void);
protected:
private:
	UvSensor( const UvSensor &c );
	UvSensor& operator=( const UvSensor &c );

}; //UvSensor

#endif //__UVSENSOR_H__
