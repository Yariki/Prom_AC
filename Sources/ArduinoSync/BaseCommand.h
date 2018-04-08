///////////////////////////////////////////////////////////
//  BaseCommand.h
//  Implementation of the Class BaseCommand
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_E6A67655_DCDA_46ad_B1E0_502B01388097__INCLUDED_)
#define EA_E6A67655_DCDA_46ad_B1E0_502B01388097__INCLUDED_

#include "CommandType.h"
#include "OperationType.h"

#define SPLIT_CHAR ","
#define END_CHAR ";"
#define PARAMS_CHAR "|"

class BaseCommand
{

public:
	BaseCommand();
	virtual ~BaseCommand();

	CommandType getCommandType();
	OperationType getOperationType();
	void setOperationType(OperationType operationType);

protected:
	CommandType _commandType;
	OperationType _operationType;

};
#endif // !defined(EA_E6A67655_DCDA_46ad_B1E0_502B01388097__INCLUDED_)
