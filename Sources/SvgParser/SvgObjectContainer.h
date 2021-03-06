//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Core Model
//  @ File Name : SvgObjectContainer.h
//  @ Date : 3/25/2013
//  @ Author : 
//
//


#if !defined(_SVGOBJECTCONTAINER_H)
#define _SVGOBJECTCONTAINER_H

#include <vector>
#include "BaseSvgObject.h"
using namespace std;


class SvgObjectContainer
{
protected:
	int m_width;
	int m_height;
	std::vector<BaseSvgObject*> m_listObjects;

public:
	void setWidth(int &width) {m_width = width;}
	void setHeight(int &height) {m_height = height;}
	int getWidth() {return m_width;}
	int getHeight() {return m_height;}
	int getObjectsCount() {return m_listObjects.size();}
	BaseSvgObject* getObject(int index);
	void addObject(BaseSvgObject *object);
};

#endif  //_SVGOBJECTCONTAINER_H
