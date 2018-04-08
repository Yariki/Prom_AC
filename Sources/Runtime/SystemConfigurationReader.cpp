#include "StdAfx.h"
#include "SystemConfigurationReader.h"

#include <QFile>

// defines for model types
#define MODELTYPES_TAGNAME "modeltypes"
#define TYPE_TAG "type"
#define VALUE_ATTR "value"

// define for models
#define MODELS_TAGNAME "models"
#define MODEL_TAGNAME "model"

// define for connections

#define CONNECTIONS_TAGNAME "connections"
#define CONNECTION_TAGNAME "connection"



SystemConfigurationReader::SystemConfigurationReader(void)
{
}

SystemConfigurationReader::SystemConfigurationReader(QString& filename)
	:BaseSystemConfigurationReader(filename)
{
}


SystemConfigurationReader::~SystemConfigurationReader(void)
{
}

bool SystemConfigurationReader::Parse()
{
	if(_filename.isEmpty())
		return false;

	QFile file(_filename);
	if(!file.exists())
	{
		LOG_ERROR("File doesn't exist");
		return false;
	}

	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		LOG_ERROR("Error while opening file");
		return false;
	}
	return ParseFile(&file);
}

bool SystemConfigurationReader::ParseFile(QFile* file)
{
	QString error;
	int errorLine;
	int errorColumn;
	QDomDocument doc;
	if(!doc.setContent(file,true,&error,&errorLine,&errorColumn))
	{
		LOG_ERROR("Can't set content of xml project");
		return false;
	}
	
	QDomElement root = doc.documentElement();

	if(root.tagName() != "project")
	{
		LOG_ERROR("File doesn't consist project");
		return false;
	}
	if(!root.hasChildNodes())
	{
		LOG_ERROR("XML doesn't has child nodes");
		return  false;
	}

	bool result = ParseTypes(&root) && ParseModels(&root) && ParseConnectios(&root);
	return  result;
}

bool SystemConfigurationReader::ParseTypes(QDomElement* root)
{
	auto md = root->firstChildElement(MODELTYPES_TAGNAME);
	if(md.isNull())
		return false;
	_listTypes = new vector<QString>;
	QDomNode nodeChild = md.firstChild();
	bool result = true;
	while(!nodeChild.isNull())
	{
		auto el = nodeChild.toElement();
		if(el.isNull() || el.tagName().toLower() != TYPE_TAG)
		{
			result = false;
			break;
		}
		if(el.hasAttribute(VALUE_ATTR))
		{
			auto attr = el.attributeNode(VALUE_ATTR);
			_listTypes->push_back(attr.value());
		}
		nodeChild = nodeChild.nextSibling();
	}
	return result;
}

bool SystemConfigurationReader::ParseModels(QDomElement* root)
{
	auto models = root->firstChildElement(MODELS_TAGNAME);
	if(models.isNull())
		return false;
	_listModels = new vector<QDomElement>;
	QDomNode nodeChild = models.firstChild();
	bool result = true;
	while(!nodeChild.isNull())
	{
		auto el = nodeChild.toElement();
		if(el.isNull() || el.tagName().toLower() != MODEL_TAGNAME)
		{
			result = false;
			break;
		}
		_listModels->push_back(el);
		nodeChild = nodeChild.nextSibling();
	}
	return result;
}

bool SystemConfigurationReader::ParseConnectios(QDomElement* root)
{
	auto connections = root->firstChildElement(CONNECTIONS_TAGNAME);
	
	if(connections.isNull())
		return false;
	_listConnections = new vector<QDomElement>;
	QDomNode nodeChild = connections.firstChild();
	bool result = true;
	while(!nodeChild.isNull())
	{
		auto el = nodeChild.toElement();
		if(el.isNull() || el.tagName().toLower() != CONNECTION_TAGNAME)
		{
			result = false;
			break;
		}
		_listConnections->push_back(el);
		nodeChild = nodeChild.nextSibling();
	}
	return result;
}
