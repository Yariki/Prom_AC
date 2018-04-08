


#if !defined(_CONCRETEOBSERVER_H)
#define _CONCRETEOBSERVER_H

#include "Observer.h"
#include "ConcreteSubject.h"

class ConcreteObserver : public Observer {
public:
	ConcreteSubject *subject;
};

#endif  //_CONCRETEOBSERVER_H
