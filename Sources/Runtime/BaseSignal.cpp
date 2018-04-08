

#include "stdafx.h"
#include "BaseSignal.h"
#include "SignalState.h"

BaseSignal::BaseSignal()
{
	_deviceId = -1;
}

BaseSignal::~BaseSignal(){}

void BaseSignal::checkSignal() {
	_state = checkValues();
}

void BaseSignal::checkSignal(SignalInfo* signalInfo) {
	_currentValue = signalInfo->getValue();
	_state = checkValues();
}

void BaseSignal::configureSignal() {
	_value = 0;
	_signalId = -1;
}

SignalState BaseSignal::getSignalState() {
	return _state;
}

void BaseSignal::setDeviceId(int id) {
	_deviceId = id;
}

int BaseSignal::getSignalId(){
	return _signalId;
}

SignalState BaseSignal::checkValues(){
	return _currentValue > _value ? SignalState::Emergency : SignalState::Normal;
}