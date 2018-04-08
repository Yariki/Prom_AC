#include "svgparser.h"
#include <QFile>
#include "AbstractFactorySvgObjects.h"
#include "FactorySvgObjects.h"

SvgParser::SvgParser(QString fileName)
{
	m_filename = fileName;
}

SvgParser::~SvgParser()
{

}

SvgObjectContainer* SvgParser::getSvgObjectContainer()
{
	return m_objectContainer;
}

bool SvgParser::Parse()
{
	if(m_filename.isEmpty())
		return false;

	QFile file(m_filename);
	if (!file.exists())
	{
		qDebug("File doesn't exist");
		return false;
	}
	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug("Error while open file");
		return false;
	}
	return ParseXml(&file);
}

bool SvgParser::ParseXml( QIODevice *device )
{
	QString errorStr;
	int errorLine;
	int errorColumn;
	if(!m_document.setContent(device,true,&errorStr,&errorLine,&errorColumn))
		return false;

	QDomElement root = m_document.documentElement();
	if(root.tagName() != "svg")
	{
		return false;
	}
	if(!root.hasChildNodes())
		return false;
	m_objectContainer = new SvgObjectContainer();
	if(!ParseRootElement(m_objectContainer,&root))
	{
		return false;
	}
	return ParseLayouts(&root);
}

bool SvgParser::ParseRootElement( SvgObjectContainer* object, QDomElement* root )
{
	if(object == NULL || root == NULL)
		return false;
	if(!root->hasAttribute("width") || !root->hasAttribute("height"))
		return false;
	
	QString strWidth = root->attribute("width");
	const QString strW = strWidth.left(strWidth.indexOf("px"));
	int w = strW.toInt();
	QString strHeight = root->attribute("height");
	const QString strH = strHeight.left(strHeight.indexOf("px"));
	int h = strH.toInt();
	object->setWidth(w);
	object->setHeight(h);
	return true;
}

bool SvgParser::ParseLayouts(QDomElement* root)
{
	bool result =  true;
	QDomNode node = root->firstChild();
	AbstractFactorySvgObjects* factory = new FactorySvgObjects();
	while(!node.isNull())
	{
		QDomElement el = node.toElement();
		if(el.isNull() || el.tagName().toLower() != "g")
		{
			result = false;
			break;
		}
		if(!el.hasChildNodes())
			continue;
		QDomNode nodeChild = el.firstChild();
		while(!nodeChild.isNull())
		{
			QDomElement elChild = nodeChild.toElement();
			if(elChild.isNull())
				continue;
			BaseSvgObject* object = NULL;
			if((object = factory->CreateSvgObject(elChild)) != NULL)
			{
				m_objectContainer->addObject(object);
			}
			// next element(such as line, rect etc)
			nodeChild = nodeChild.nextSibling();
		}
		// next element (layout)
		node = node.nextSibling();
	}
	if(factory != NULL)
	{
		delete factory;
	}

	return result;
}
