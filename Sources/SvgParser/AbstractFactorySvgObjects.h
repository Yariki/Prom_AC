//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Core Model
//  @ File Name : AbstractFactorySvgObjects.h
//  @ Date : 3/25/2013
//  @ Author : 
//
//


#if !defined(_ABSTRACTFACTORYSVGOBJECTS_H)
#define _ABSTRACTFACTORYSVGOBJECTS_H

#include <QDomElement>
#include "BaseSvgObject.h"

class AbstractFactorySvgObjects
{
public:
	virtual BaseSvgObject* CreateSvgObject(QDomElement &domElement) = 0;
};

#endif  //_ABSTRACTFACTORYSVGOBJECTS_H