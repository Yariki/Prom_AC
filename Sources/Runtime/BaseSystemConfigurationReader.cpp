#include "StdAfx.h"
#include "BaseSystemConfigurationReader.h"


BaseSystemConfigurationReader::BaseSystemConfigurationReader(void)
{

}

BaseSystemConfigurationReader::BaseSystemConfigurationReader(QString& filename)
{
	_filename = filename;
}

BaseSystemConfigurationReader::~BaseSystemConfigurationReader(void)
{
	if(_listTypes != nullptr)
	{
		delete _listTypes;
	}
	if(_listModels != nullptr)
	{
		delete _listModels;
	}
	if(_listConnections != nullptr)
	{
		delete _listConnections;
	}
}

vector<QString>* BaseSystemConfigurationReader::getTypes() const
{
	return _listTypes;
}

vector<QDomElement>* BaseSystemConfigurationReader::getModels() const
{
	return _listModels;
}

vector<QDomElement>* BaseSystemConfigurationReader::getConnections() const
{

	 return _listConnections;
}