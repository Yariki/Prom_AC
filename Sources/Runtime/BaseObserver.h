


#if !defined(_BASEOBSERVER_H)
#define _BASEOBSERVER_H

#include "IObject.h"

class BaseObserver 
{
public:
	BaseObserver();
	~BaseObserver();
	void Update(IObject* object);
};

#endif  //_BASEOBSERVER_H
