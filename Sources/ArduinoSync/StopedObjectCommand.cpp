///////////////////////////////////////////////////////////
//  StopedObjectCommand.cpp
//  Implementation of the Class StopedObjectCommand
//  Created on:      31-Jul-2013 10:30:18 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "StopedObjectCommand.h"
#include <QStringList>

StopedObjectCommand::StopedObjectCommand(){

}

StopedObjectCommand::~StopedObjectCommand(){

}

int StopedObjectCommand::getResult(){

	return  _result;
}

bool StopedObjectCommand::parse(){

	QStringList tokens = _content.split(SPLIT_CHAR);
	if(!tokens.count() || tokens.count() == 1)
		return  false;
	QString strtemp = tokens[1].replace(";","");
	_result = strtemp.toInt();
	return  true;
}