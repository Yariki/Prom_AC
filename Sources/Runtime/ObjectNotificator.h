


#if !defined(_OBJECTNOTIFICATOR_H)
#define _OBJECTNOTIFICATOR_H

#include "IObject.h"
#include "BaseNotificator.h"
#include "INotificator.h"

class ObjectNotificator : public BaseNotificator, public INotificator
{
public:
	void Notify(IObject* input);
	void Attach(IObserver* observer);
	void Deattach(IObserver* observer);
};

#endif  //_OBJECTNOTIFICATOR_H
