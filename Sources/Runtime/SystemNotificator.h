


#if !defined(_SYSTEMNOTIFICATOR_H)
#define _SYSTEMNOTIFICATOR_H

#include "BaseNotificator.h"
#include "INotificator.h"

class SystemNotificator : public BaseNotificator, public INotificator
{
public:
	SystemNotificator();
	virtual ~SystemNotificator();
	void Notify(IObject* input);
	void Attach(IObserver* observer);
	void Deattach(IObserver* observer);
};

#endif  //_SYSTEMNOTIFICATOR_H
