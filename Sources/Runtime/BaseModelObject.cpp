

#include "stdafx.h"
#include "BaseModelObject.h"
#include "StateObject.h"
#include "TypeObject.h"
#include "IOName.h"
#include <algorithm>

// for models
#define ID_TAGNAME "id"
#define SYSTYMID_TAGNAME "systemid"
#define PRIORITY_TAGNAME "priority"
#define VALUE_ATTRIBUTE "value"
#define NAME_ATTRIBUTE "name"
#define TYPE_ATTRIBUTE "type"

BaseModelObject::BaseModelObject()
{
	_isActive = false;
}

BaseModelObject::~BaseModelObject()
{

}

void BaseModelObject::Start() {
	_state = StateObject::Work;
	Notify(this);
}

void BaseModelObject::Stop() {
	_state = StateObject::Stop;
	Notify(this);
}

void BaseModelObject::EmergencyStop() {
	_state = StateObject::EmergencyStoped;
	Notify(this);
}

StateObject BaseModelObject::getState() {
	return _state;
}

TypeObject BaseModelObject::getType() {
	return _type;
}

void BaseModelObject::addInput(InputOutputModel* input) {
	_listConnections.push_back(input);
}

void BaseModelObject::removeInput(InputOutputModel* input) {
	if(_listConnections.size() > 0)
	{
		std::remove(_listConnections.begin(),_listConnections.end(),input);
	}
}

int BaseModelObject::getDeviceId() {
	return _id;
}

vector<IOName> BaseModelObject::getInputsListName() const{
	vector<IOName> result;
	for(auto it = _listConnections.begin(); it != _listConnections.end();it++)
		if((*it)->getDestinationObject() == this)
			result.push_back((*it)->getName());
	return result;
}

vector<IOName> BaseModelObject::getOutputListName() const{
	vector<IOName> result;
	for(auto it = _listConnections.begin();it != _listConnections.end();it++)
		if((*it)->getSourceObject() == this)
			result.push_back((*it)->getName());
	return result;
}

void BaseModelObject::setActiveInput(IOName& inputName) {
	if(_listConnections.size() == 0)
		return;
	for(int i = 0; i < _listConnections.size();i++)
	{
		if(_listConnections.at(i)->getDestinationObject() != this)
			continue;

		if(_listConnections.at(i)->getName().getName() == inputName.getName())
		{
			_listConnections.at(i)->SetActive(true);
		}
		else
			_listConnections.at(i)->SetActive(false);
	}
}

void BaseModelObject::setActiveOutput(IOName& active) {
	if(_listConnections.size() == 0)
		return;
	for(int i = 0; i < _listConnections.size();i++)
	{
		if(_listConnections.at(i)->getSourceObject() != this)
			continue;

		if(_listConnections.at(i)->getName().getName() == active.getName())
		{
			_listConnections.at(i)->SetActive(true);
		}
		else
			_listConnections.at(i)->SetActive(false);
	}

}

IOName BaseModelObject::getActiveInput() const{
	
	InputOutputModel* ioModel = nullptr;
	for(int i = 0; i < _listConnections.size();i++)
	{
		if(_listConnections.at(i)->getDestinationObject() == this && _listConnections.at(i)->IsActive())
		{
			ioModel = _listConnections.at(i);
			break;
		}
	}
	return ioModel ?  ioModel->getName() : IOName();
}

IOName BaseModelObject::getActiveOutput() const{
	InputOutputModel* ioModel = nullptr;
	for(int i = 0; i < _listConnections.size();i++)
	{
		if(_listConnections.at(i)->getSourceObject() == this && _listConnections.at(i)->IsActive())
		{
			ioModel = _listConnections.at(i);
			break;
		}
	}
	return ioModel ? ioModel->getName() : IOName();
	
}

void BaseModelObject::Update(IObject* input) {

}

void BaseModelObject::Notify(IObject* input) {
	
	for(auto iter = _observers.begin(); iter != _observers.end();iter++)
	{
		((IObserver*)(*iter))->Update(input);
	}
}

void BaseModelObject::Attach(IObserver* observer) {
	if(observer != NULL)
	{
		_observers.push_back((IObserver*)observer);
	}
}

void BaseModelObject::Deattach(IObserver* observer) {
	if(_observers.size() == 0)
		return;
	int index = -1;
	for(auto iter = _observers.begin(); iter != _observers.end();iter++)
	{
		index++;
		if((*iter) == (IObserver*)observer)
			break;
	}
	_observers.erase(_observers.begin() + index);
}


IOName BaseModelObject::getName() {
	return _name;
}

int BaseModelObject::getPriority(){
	return _priority;
}

void BaseModelObject::setPriority(int priority) {
	_priority = priority;
}

void BaseModelObject::readConfiguration(QDomElement* xmlEl) {
	if(xmlEl == nullptr || !xmlEl->hasChildNodes())
		return;
	QDomNode node = xmlEl->firstChild();
	while(!node.isNull())
	{
		auto el = node.toElement();
		if(el.isNull())
		{
			node = node.nextSibling();
			continue;;
		}
		QString lowName = el.tagName().toLower();
		if(lowName == ID_TAGNAME)
		{
			QString strID = el.attributeNode(VALUE_ATTRIBUTE).value();
			QString name = el.attributeNode(NAME_ATTRIBUTE).value();
			QUuid id = QUuid(strID);
			_name = IOName(name,id);
		}
		else if(lowName == SYSTYMID_TAGNAME)
		{
			_id = el.attributeNode(VALUE_ATTRIBUTE).value().toInt();
		}
		else if(lowName == PRIORITY_TAGNAME)
		{
			int pr = el.attributeNode(VALUE_ATTRIBUTE).value().toInt();
			setPriority(pr);
		}
		node  = node.nextSibling();
	}
}

bool BaseModelObject::IsActive()
{
	return _isActive;
}

void BaseModelObject::setActive( bool state )
{
	_isActive = state;
	Notify(this);
}

