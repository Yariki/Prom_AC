///////////////////////////////////////////////////////////
//  ConnectionUIObject.cpp
//  Implementation of the Class ConnectionUIObject
//  Created on:      07-Jul-2013 7:21:11 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// 
#include "stdafx.h"
#include "ConnectionUIObject.h"
#include "../SvgParser/svgparser.h"
#include "../SvgParser/PolygonSvgObject.h"

ConnectionUIObject::ConnectionUIObject(QWidget* parent)
	:BaseUIWidget(parent){

}



ConnectionUIObject::~ConnectionUIObject(){

}

void ConnectionUIObject::prepareForRendering(){

}


void ConnectionUIObject::readConfiguration(QDomElement* input){
	if(input == nullptr || !input->hasChildNodes())
		return;
	LOG_INFO(input->localName());
	if(input->elementsByTagName("polygon").count() > 0)
	{
		auto element = input->elementsByTagName("polygon").at(0).toElement();
		if(element.isNull())
			return;
		PolylineSvgObject *polygon = new PolylineSvgObject();
		polygon->Parse(element);
		_listRenderObjects.push_back(polygon);
	}
}


void ConnectionUIObject::render(){
	
}


void ConnectionUIObject::renderTemplate(QPainter* canvas){
	move(0,0);
	for(int i = 0; i < _listRenderObjects.size();i++)
	{
		_listRenderObjects.at(i)->render(canvas);
	}
}

void ConnectionUIObject::paintEvent( QPaintEvent* args )
{

}
