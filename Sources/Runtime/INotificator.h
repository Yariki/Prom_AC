


#if !defined(_INOTIFICATOR_H)
#define _INOTIFICATOR_H

#include "IObject.h"
#include "IObserver.h"

__interface INotificator {
public:
	virtual void Notify(IObject* input) = 0;
	virtual void Attach(IObserver* observer) = 0;
	virtual void Deattach(IObserver* observer) = 0;
};

#endif  //_INOTIFICATOR_H
