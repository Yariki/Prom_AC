#ifndef _IOMODELSETTINGS_H_
#define _IOMODELSETTINGS_H_

#include "IOName.h"
#include "IConfigurationReader.h"

class IOModelSettings : public IConfigurationReader
{
public:
	IOModelSettings(void);
	virtual ~IOModelSettings(void);

	virtual void readConfiguration( QDomElement* xmlEl );

	IOName getName() const;
	int getPriority() const;
	QString getSourceName() const;
	QString getDestinationName() const;

private:
	IOName _name;
	int _priority;
	QString _sourceName;
	QString _destinationName;

};


#endif //_IOMODELSETTINGS_H_



