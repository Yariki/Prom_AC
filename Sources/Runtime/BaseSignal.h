


#if !defined(_BASESIGNAL_H)
#define _BASESIGNAL_H

#include "ISignal.h"
#include "SignalInfo.h"
#include "ObjectNotificator.h"
#include "SignalState.h"
#include "baseport.h"

class BaseSignal : public ISignal, public ObjectNotificator {
public:

	BaseSignal();
	~BaseSignal();

	virtual void checkSignal();
	virtual void checkSignal(SignalInfo* signalInfo);
	virtual void configureSignal();
	virtual SignalState getSignalState();
	virtual void setDeviceId(int id = -1);
	virtual int getSignalId();

private:
	SignalState checkValues();

protected:
	int _currentValue;
	int _value;
	BasePort* _port;
	int _deviceId;
	int _signalId;
	SignalState _state;
};

#endif  //_BASESIGNAL_H
