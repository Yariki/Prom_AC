


#if !defined(_OBJECTOBSERVER_H)
#define _OBJECTOBSERVER_H

#include "IObject.h"
#include "BaseObserver.h"
#include "IObserver.h"

class ObjectObserver : public BaseObserver, public IObserver
{
public:
	void Update(IObject* input);
};

#endif  //_OBJECTOBSERVER_H
