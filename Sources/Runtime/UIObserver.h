


#if !defined(_UIOBSERVER_H)
#define _UIOBSERVER_H

#include "IObserver.h"

class UIObserver : public IObserver {
public:
	virtual void Update(IObject* input);
};

#endif  //_UIOBSERVER_H
