#include "IndicatorProcessObject.h"


IndicatorProcessObject::IndicatorProcessObject()
{
}


IndicatorProcessObject::~IndicatorProcessObject(void)
{

}

void IndicatorProcessObject::portChanged(uint8_t port)
{
	_port = port;
	pinMode(_port,OUTPUT);
	setIndicator(_value);
}

void IndicatorProcessObject::setIndicator( bool valueIndicate )
{
	_value = valueIndicate;
	digitalWrite(_port, _value ? HIGH : LOW);
}

uint8_t IndicatorProcessObject::getPort()
{
	return _port;
}

void IndicatorProcessObject::setPort( uint8_t port )
{
	portChanged(port);
	setIndicator(_value);
}

