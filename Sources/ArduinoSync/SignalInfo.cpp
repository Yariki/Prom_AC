///////////////////////////////////////////////////////////
//  SignalInfo.cpp
//  Implementation of the Class SignalInfo
//  Created on:      31-Jul-2013 10:40:54 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "SignalInfo.h"


SignalInfo::SignalInfo(int* id, int* val){
	_id = *id;
	_value = *val;
}



SignalInfo::~SignalInfo(){

}

int SignalInfo::getId(){

	return _id;
}


int SignalInfo::getValue(){

	return _value;
}