

#include "stdafx.h"
#include "WidgetUIObject.h"
#include "../SvgParser/svgparser.h"
#include "../SvgParser/SvgObjectContainer.h"


#define UIFILENAME_TAGNAME "uifilename"
#define POSITION_TAGNAME "position"
#define SIZE_TAGNAME "size"

#define VALUE_ATTR_NAME "value"
#define X_ATTR_NAME "x"
#define Y_ATTR_NAME "y"
#define WIDTH_ATTR_NAME "width"
#define HEIGHT_ATTR_NAME "height"


void WidgetUIObject::Update(IObject* input) 
{
	auto state = getModel()->getState();
	switch(state)
	{
	case StateObject::Work:
		_mapStates[StateObject::Work] = true;
		_mapStates[StateObject::Stop] = false;
		_mapStates[StateObject::EmergencyStoped] = false;
		break;
	case StateObject::Stop:
		_mapStates[StateObject::Work] = false;
		_mapStates[StateObject::Stop] = true;
		_mapStates[StateObject::EmergencyStoped] = false;

		break;
	case StateObject::EmergencyStoped:
		_mapStates[StateObject::Work] = false;
		_mapStates[StateObject::Stop] = false;
		_mapStates[StateObject::EmergencyStoped] = true;
		break;
	case StateObject::NoneState:
		break;
	}
	render();
	LOG_INFO("update");
}

WidgetUIObject::WidgetUIObject(QWidget* parent)
	:BaseUIWidget(parent)
{
	init();
}

WidgetUIObject::WidgetUIObject( QWidget* parent, BaseModelObject* modelObject)
	:BaseUIWidget(parent)
{
	if(modelObject != nullptr)
	{
		_baseModelObject = modelObject;
		_baseModelObject->Attach((IObserver*)this);
	}
	init();
}

WidgetUIObject::~WidgetUIObject()
{

}

void WidgetUIObject::render()
{
	repaint();
}

void WidgetUIObject::readConfiguration(QDomElement* input)
{
	if(input == nullptr || !input->hasChildNodes())
		return;
	QDomNode node = input->firstChild();
	while(!node.isNull())
	{
		auto el = node.toElement();
		if(el.isNull())
		{
			node = node.nextSibling();
			continue;
		}
		QString lowName = el.tagName().toLower();
		if(lowName == UIFILENAME_TAGNAME)
		{
			QString filename = el.attributeNode(VALUE_ATTR_NAME).value();
			_templateName = filename;
		}
		else if(lowName == POSITION_TAGNAME)
		{
			_x = el.attributeNode(X_ATTR_NAME).value().toInt();
			_y = el.attributeNode(Y_ATTR_NAME).value().toInt();
		}
		else if(lowName == SIZE_TAGNAME)
		{
			_width = el.attributeNode(WIDTH_ATTR_NAME).value().toInt();
			_height = el.attributeNode(HEIGHT_ATTR_NAME).value().toInt();
		}
		node = node.nextSibling();
	}
}

void WidgetUIObject::prepareForRendering()
{
	if(_templateName.length() == 0)
		return;

	SvgParser parser("./models/"+_templateName);
	if(parser.Parse())
	{
		SvgObjectContainer* conteiner = parser.getSvgObjectContainer();
		for(int i=0;i < conteiner->getObjectsCount();i++)
		{
			auto obj = conteiner->getObject(i);
			if(obj != nullptr)
			{
				obj->setXFactor(((float)_width / (float)conteiner->getWidth()));
				obj->setYFactor(((float)_height / (float)conteiner->getHeight()));
				_listRenderObjects.push_back(obj);
			}
		}
	}
	
	
}

void WidgetUIObject::renderTemplate( QPainter* canvas )
{
	if(canvas == nullptr)
		return;

	renderIndicators(canvas);
	if(!_listRenderObjects.size())
		return;
	move(_x,_y);
	resize(_width,_height);
	for (int i=0;i < _listRenderObjects.size();i++)
	{
		_listRenderObjects.at(i)->render(canvas);
	}
}

BaseModelObject* WidgetUIObject::getModel() const
{
	return _baseModelObject;
}

void WidgetUIObject::renderIndicators( QPainter* canvas )
{
	int w = width();
	int h = height();
	int startX = 0;
	int startY = h - MINHEIGHT_TOOLBAR_INDICATOR;
	int delta = w / _mapStates.size();
	int heightIndicator = MINHEIGHT_TOOLBAR_INDICATOR / 2;
	canvas->fillRect(QRect(startX,startY,delta,heightIndicator),_mapStates[StateObject::Work] ? WORK_COLOR_ACTIVE : WORK_COLOR_DEACTIVE);
	startX += delta;
	canvas->fillRect(QRect(startX,startY,delta,heightIndicator),_mapStates[StateObject::Stop] ? STOP_COLOR_ACTIVE : STOP_COLOR_DEACTIVE);
	startX += delta;
	canvas->fillRect(QRect(startX,startY,delta,heightIndicator),_mapStates[StateObject::EmergencyStoped] ? EMERGENCY_COLOR_ACTIVE : EMERGENCY_COLOR_DEACTIVE);
	startY += heightIndicator;
	startX = 0;
	
	canvas->drawStaticText(startX,startY, getModel()->IsActive() ?  QStaticText("Active") : QStaticText("De active"));
	
}

void WidgetUIObject::init()
{
	_mapStates[StateObject::Work] = false;
	_mapStates[StateObject::Stop] = true;
	_mapStates[StateObject::EmergencyStoped] = false;
}

