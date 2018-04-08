///////////////////////////////////////////////////////////
//  ObjectInfo.cpp
//  Implementation of the Class ObjectInfo
//  Created on:      31-Jul-2013 10:40:52 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "ObjectInfo.h"


ObjectInfo::~ObjectInfo(){
	if(_signalsCollection != nullptr)
	{
		for (auto iter = _signalsCollection->begin(); iter != _signalsCollection->end();iter++)
		{
			delete (*iter);
		}
		delete _signalsCollection;
		_signalsCollection = nullptr;
	}
}


int ObjectInfo::getId(){

	return _id;
}


vector<SignalInfo*>* ObjectInfo::getSignalsInfo(){

	return  _signalsCollection;
}


void ObjectInfo::insertSignalInfo(SignalInfo* si){
	_signalsCollection->push_back(si);
}