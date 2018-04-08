#include "StdAfx.h"
#include "IOModelSettings.h"

// for models
#define ID_TAGNAME "id"
#define PRIORITY_TAGNAME "priority"
#define SOURCE_TAGNAME "source"
#define DESTINATION_TAGNAME "destination"

#define VALUE_ATTRIBUTE "value"
#define NAME_ATTRIBUTE "name"


IOModelSettings::IOModelSettings(void)
{
}


IOModelSettings::~IOModelSettings(void)
{
}

void IOModelSettings::readConfiguration( QDomElement* xmlEl )
{
	if(xmlEl == nullptr || !xmlEl->hasChildNodes())
		return;
	QDomNode node = xmlEl->firstChild();
	while(!node.isNull())
	{
		auto el = node.toElement();
		if(el.isNull())
			break;
		QString lowName = el.tagName().toLower();
		if(lowName == ID_TAGNAME)
		{
			QString strID = el.attributeNode(VALUE_ATTRIBUTE).value();
			QString name = el.attributeNode(NAME_ATTRIBUTE).value();
			QUuid id = QUuid(strID);
			_name = IOName(name,id);
		}
		else if(lowName == SOURCE_TAGNAME)
		{
			_sourceName = el.attributeNode(VALUE_ATTRIBUTE).value();
		}
		else if(lowName == DESTINATION_TAGNAME)
		{
			_destinationName = el.attributeNode(VALUE_ATTRIBUTE).value();
		}
		else if(lowName == PRIORITY_TAGNAME)
		{
			_priority = el.attributeNode(VALUE_ATTRIBUTE).value().toInt();
		}
		node  = node.nextSibling();
	}
}

IOName IOModelSettings::getName() const
{
	return _name;
}

int IOModelSettings::getPriority() const
{
	return _priority;
}

QString IOModelSettings::getSourceName() const
{
	return _sourceName;
}

QString IOModelSettings::getDestinationName() const
{
	return _destinationName;
}
