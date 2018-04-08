#if !defined(_BASESYSTEMCONFIGURATIONREADER_H_)
#define _BASESYSTEMCONFIGURATIONREADER_H_


#include <QDomDocument>
#include <vector>

using std::vector;

class BaseSystemConfigurationReader
{
public:
	BaseSystemConfigurationReader(void);
	BaseSystemConfigurationReader(QString& filename);
	virtual ~BaseSystemConfigurationReader(void);

	virtual bool Parse() = 0;
	virtual vector<QString>* getTypes() const;
	virtual vector<QDomElement>* getModels() const;
	virtual vector<QDomElement>* getConnections() const;

protected:
	virtual bool ParseTypes(QDomElement* root) = 0;
	virtual bool ParseModels(QDomElement* root) = 0;
	virtual bool ParseConnectios(QDomElement* root) = 0;

protected:
	QString _filename;
	vector<QString>* _listTypes;
	vector<QDomElement>* _listModels;
	vector<QDomElement>* _listConnections;
};

#endif