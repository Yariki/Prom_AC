#ifndef _INDICATORPROCESSOBJECT_H_
#define _INDICATORPROCESSOBJECT_H_

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class IndicatorProcessObject
{
private:
	uint8_t _port;
	bool _value;

public:
	IndicatorProcessObject(void);
	~IndicatorProcessObject(void);

	void setIndicator(bool valueIndicate);
	uint8_t getPort();
	void  setPort(uint8_t port);

private:
	void portChanged(uint8_t port);
};

#endif //_INDICATORPROCESSOBJECT_H_