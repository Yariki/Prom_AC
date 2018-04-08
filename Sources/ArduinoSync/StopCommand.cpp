///////////////////////////////////////////////////////////
//  StopCommand.cpp
//  Implementation of the Class StopCommand
//  Created on:      31-Jul-2013 10:10:44 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "StopCommand.h"


StopCommand::StopCommand(){

}



StopCommand::~StopCommand(){

}

QByteArray StopCommand::createCommand(){

	return  createOutputCommand(OTStop);
}