


#if !defined(_ISIGNAL_H)
#define _ISIGNAL_H

#include "SignalState.h"
#include "SignalInfo.h"
#include "SignalIdentity.h"

__interface ISignal {
public:
	virtual void checkSignal() = 0;
	virtual void checkSignal(SignalInfo* signalInfo) = 0;
	virtual void configureSignal() = 0;
	virtual SignalState getSignalState() = 0;
	virtual void setDeviceId(int id = -1) = 0;
	virtual int getSignalId() = 0;
	virtual SignalIdentity getIdentity() = 0;
};

#endif  //_ISIGNAL_H
