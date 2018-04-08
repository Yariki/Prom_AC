#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <QDomDocument>
#include "SvgObjectContainer.h"


class SvgParser
{
public:
	SvgParser(QString fileName);
	~SvgParser();
	SvgObjectContainer* getSvgObjectContainer();
	bool Parse();


private:
	bool ParseXml(QIODevice *device);
	bool ParseRootElement(SvgObjectContainer* object, QDomElement* root);
	bool ParseLayouts(QDomElement* root);
	bool ParseObject(QDomElement* element);

private:
	QDomDocument m_document;
	QString m_filename;
	SvgObjectContainer *m_objectContainer;
};

#endif // SVGPARSER_H
