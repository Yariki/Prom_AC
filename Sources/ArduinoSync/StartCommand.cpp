///////////////////////////////////////////////////////////
//  StartCommand.cpp
//  Implementation of the Class StartCommand
//  Created on:      31-Jul-2013 10:10:41 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "StartCommand.h"


StartCommand::StartCommand(){

}



StartCommand::~StartCommand(){

}





QByteArray StartCommand::createCommand(){
	return  createOutputCommand(OTStart);
}