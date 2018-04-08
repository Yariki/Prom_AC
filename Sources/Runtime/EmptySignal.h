


#if !defined(_EMPTYSIGNAL_H)
#define _EMPTYSIGNAL_H

#include "BaseSignal.h"
#include "SignalState.h"

class EmptySignal : public BaseSignal {
public:
	
	virtual void configureSignal();
};

#endif  //_EMPTYSIGNAL_H
