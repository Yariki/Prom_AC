

#include "stdafx.h"
#include "InputOutputModel.h"
#include "IOType.h"
#include "IOName.h"

InputOutputModel::InputOutputModel(BaseModelObject* inputObject, BaseModelObject* outputObject)
{
	_priority = -1;
	_isActive = false;
	_sourceObject = inputObject;
	_destinationObject = outputObject;
}
InputOutputModel::~InputOutputModel()
{
	_sourceObject = nullptr;
	_destinationObject = nullptr;
}

void InputOutputModel::SetActive(bool active)
{
	_isActive = active;
}

BaseModelObject* InputOutputModel::getSourceObject() {
	return _sourceObject;
}

BaseModelObject* InputOutputModel::getDestinationObject() {
	return _destinationObject;
}

void InputOutputModel::setPriority(int priority) {
	_priority = priority;
}

void InputOutputModel::Notify(IObject* input) {
	if(_sourceObject != nullptr)
	{
		((ObjectObserver*)_sourceObject)->Update(this);
	}
	if(_destinationObject != nullptr)
	{
		((ObjectObserver*)_destinationObject)->Update(this);
	}
}

void InputOutputModel::Attach(IObserver* observer) {

}

void InputOutputModel::Deattach(IObserver* observer) {

}

int InputOutputModel::getPriority(){
	return _priority;
}


IOType InputOutputModel::getType() {
	return IOType::None;
}

IOName InputOutputModel::getName(){
	return _name;
}


void InputOutputModel::setName(IOName& name){
	_name = IOName(name);
}

void InputOutputModel::Start() {

}

void InputOutputModel::Stop() {

}

void InputOutputModel::EmergencyStop() {

}

