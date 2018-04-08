#ifndef _IUILOGGER_H_
#define _IUILOGGER_H_

#include <qstring.h>


__interface IUILogger{
public:
	virtual void Log(QString message) = 0;
};


#endif //_IUILOGGER_H_