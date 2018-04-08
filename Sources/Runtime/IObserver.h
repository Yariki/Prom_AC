


#if !defined(_IOBSERVER_H)
#define _IOBSERVER_H
#include "IObject.h"


__interface IObserver {
public:
	virtual void Update(IObject* input) = 0;
};

#endif  //_IOBSERVER_H
