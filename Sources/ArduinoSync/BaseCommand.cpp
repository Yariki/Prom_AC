///////////////////////////////////////////////////////////
//  BaseCommand.cpp
//  Implementation of the Class BaseCommand
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "BaseCommand.h"


BaseCommand::BaseCommand(){

}



BaseCommand::~BaseCommand(){

}

CommandType BaseCommand::getCommandType(){

	return _commandType;
}


OperationType BaseCommand::getOperationType(){

	return  _operationType;
}

void BaseCommand::setOperationType(OperationType operationType){
	_operationType = operationType;
}