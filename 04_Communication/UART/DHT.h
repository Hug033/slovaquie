/*
* DHT.h
*
* Created: 11.5.2021 22:34:55
* Author: lukas
*/


#ifndef __DHT_H__
#define __DHT_H__

#include "Board.h"

class DHT
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
	DHT();
	~DHT();
	uint32_t getValue(void);
	void printValues();
	double getTemp(void);
	protected:
	private:
	DHT(const DHT& c);
	DHT& operator=(const DHT& c);

}; //DHT

#endif //__DHT_H__
