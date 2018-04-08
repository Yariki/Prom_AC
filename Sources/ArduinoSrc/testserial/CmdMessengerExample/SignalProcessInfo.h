#ifndef SIGNALPROCESSINFO
#define SIGNALPROCESSINFO

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEFAULT_SIGNAL_VALUE 0;

class SignalProcessInfo{
public:
	SignalProcessInfo(void);
	~SignalProcessInfo(void);

private:
	uint8_t _id;
	uint8_t _value;
	uint8_t _port;

public:
	void setInfo(uint8_t id,uint8_t port);
	uint8_t getId() {return _id;}
	uint8_t checkSignal();
	uint8_t& getValue();
	String getSignalValue();
};

#endif //SIGNALPROCESSINFO
