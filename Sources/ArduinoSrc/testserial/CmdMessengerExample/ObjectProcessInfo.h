
#ifndef OBJECTPROCESSINFO
#define OBJECTPROCESSINFO

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <HashMap.h>
#include "IndicatorProcessObject.h"
#include "SignalProcessInfo.h"

#define MAX_SIGNAL_COUNT 5


class ObjectProcessInfo {
public:
	ObjectProcessInfo(void);
	~ObjectProcessInfo(void);

private:
	uint8_t _counter;
	uint8_t _isWorking;
	uint8_t _id;
	HashType<uint8_t,SignalProcessInfo*> _internalRawArray[MAX_SIGNAL_COUNT];
	HashMap<uint8_t,SignalProcessInfo*>* _internalMap;
	IndicatorProcessObject* _indicator;

public:
	void setInfo(uint8_t id, uint8_t initWorking, uint8_t portIndicator);
	void addSignal(SignalProcessInfo* signal);
	String checkSignals();
	boolean isWorking();
	void setWorking(uint8_t val);
	void indicate(bool valueIndicator);
};

#endif //OBJECTPROCESSINFO