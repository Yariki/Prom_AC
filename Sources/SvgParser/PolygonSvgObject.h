//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Core Model
//  @ File Name : PolygonSvgObject.h
//  @ Date : 3/25/2013
//  @ Author : 
//
//


#if !defined(_POLYGONSVGOBJECT_H)
#define _POLYGONSVGOBJECT_H

#include <vector>
#include <QPoint>
#include "BaseSvgObject.h"

using namespace std;

class PolylineSvgObject : public BaseSvgObject
{
protected:
	std::vector<QPoint> m_points;

private:
	void ParsePoints(QString points);

public:
	PolylineSvgObject();
	virtual ~PolylineSvgObject();

	int getPointCount();
	QPoint getPoint(int index);
	void Parse(QDomElement &element);
	void render(QPainter *canvas);
	QString toString();
};

#endif  //_POLYGONSVGOBJECT_H
