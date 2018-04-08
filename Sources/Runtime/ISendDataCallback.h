#if !defined (_ISENDDATACALLBACK_H)
#define _ISENDDATACALLBACK_H

#include <QByteArray>

__interface ISendDataCallback {
public:
	virtual void sendData(QByteArray& data) = 0;
};


#endif