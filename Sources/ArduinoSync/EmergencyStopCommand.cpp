///////////////////////////////////////////////////////////
//  EmergencyStopCommand.cpp
//  Implementation of the Class EmergencyStopCommand
//  Created on:      31-Jul-2013 10:10:47 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "EmergencyStopCommand.h"


EmergencyStopCommand::EmergencyStopCommand(){

}



EmergencyStopCommand::~EmergencyStopCommand(){

}

QByteArray EmergencyStopCommand::createCommand(){

	return  createOutputCommand(OTEmergencyStop);
}