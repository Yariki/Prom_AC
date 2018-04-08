


#if !defined(_SUBJECT_H)
#define _SUBJECT_H

#include "Observer.h"

class Subject {
public:
	void Attach(Observer o);
	void Detach(Observer o);
	void Notify();
	Observer *observers;
};

#endif  //_SUBJECT_H
