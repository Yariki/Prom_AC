


#if !defined(_ICONFIGURATIONREADER_H)
#define _ICONFIGURATIONREADER_H

#include "QDomElement"

__interface IConfigurationReader {
public:
	virtual void readConfiguration(QDomElement* xmlEl) = 0;
};

#endif  //_ICONFIGURATIONREADER_H
