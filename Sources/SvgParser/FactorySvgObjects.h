//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Core Model
//  @ File Name : FactorySvgObjects.h
//  @ Date : 3/25/2013
//  @ Author : 
//
//


#if !defined(_FACTORYSVGOBJECTS_H)
#define _FACTORYSVGOBJECTS_H

#include "AbstractFactorySvgObjects.h"
#include "BaseSvgObject.h"

class FactorySvgObjects : public AbstractFactorySvgObjects
{
public:
	BaseSvgObject* CreateSvgObject(QDomElement &domElement);
};

#endif  //_FACTORYSVGOBJECTS_H
