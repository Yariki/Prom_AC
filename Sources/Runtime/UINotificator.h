


#if !defined(_UINOTIFICATOR_H)
#define _UINOTIFICATOR_H

#include "INotificator.h"

class UINotificator : public INotificator {
public:
	void Notify(IObject* input);
	void Attach(IObserver* observer);
	void Deattach(IObserver* observer);
};

#endif  //_UINOTIFICATOR_H
