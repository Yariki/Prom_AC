///////////////////////////////////////////////////////////
//  StartedObjectCommand.cpp
//  Implementation of the Class StartedObjectCommand
//  Created on:      31-Jul-2013 10:15:14 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "StartedObjectCommand.h"
#include <QStringList>


StartedObjectCommand::StartedObjectCommand(){

}

StartedObjectCommand::~StartedObjectCommand(){

}

int StartedObjectCommand::getResult(){

	return  _result;
}

bool StartedObjectCommand::parse(){

	QStringList tokens = _content.split(SPLIT_CHAR);
	if (!tokens.count() || tokens.count() == 1)
		return false;
	QString strtemp = tokens[1].replace(";","");
	_result = strtemp.toInt();

	return true;
}