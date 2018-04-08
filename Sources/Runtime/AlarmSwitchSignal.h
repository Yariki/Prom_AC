


#if !defined(_ALARMSWITCHSIGNAL_H)
#define _ALARMSWITCHSIGNAL_H

#include "BaseSignal.h"
#include "SignalState.h"

class AlarmSwitchSignal : public BaseSignal {
public:
	virtual void configureSignal();
};

#endif  //_ALARMSWITCHSIGNAL_H
