
#if !defined(_ISYSTEMOBJECT_H)
#define _ISYSTEMOBJECT_H

#include "IObject.h"
#include "IOName.h"


__interface ISystemObject: public IObject {
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void EmergencyStop() = 0;
	virtual IOName getName() = 0;
	virtual int getPriority() = 0;
	virtual void setPriority(int priority) = 0;
};


#endif