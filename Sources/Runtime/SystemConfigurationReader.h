#if !defined(_SYSTEMCONFIGURATIONREADER_H_)
#define _SYSTEMCONFIGURATIONREADER_H_

#include "basesystemconfigurationreader.h"



class SystemConfigurationReader :
	public BaseSystemConfigurationReader
{
public:
	SystemConfigurationReader(void);
	SystemConfigurationReader(QString& filename);
	virtual ~SystemConfigurationReader(void);

	virtual bool Parse();

protected:

	virtual bool ParseTypes(QDomElement* root);
	virtual bool ParseModels(QDomElement* root);
	virtual bool ParseConnectios(QDomElement* root);


private:
	bool ParseFile(QFile* file);

};

#endif