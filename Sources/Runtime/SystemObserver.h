


#if !defined(_SYSTEMOBSERVER_H)
#define _SYSTEMOBSERVER_H

#include "BaseObserver.h"
#include "IObserver.h"

class SystemObserver : public BaseObserver, public IObserver {
public:
	void Update(IObject* input);
};

#endif  //_SYSTEMOBSERVER_H
