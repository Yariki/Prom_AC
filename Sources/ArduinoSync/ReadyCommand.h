#pragma once
#include "basestringcommand.h"
class ReadyCommand :
	public BaseStringCommand
{
public:
	ReadyCommand(void);
	virtual ~ReadyCommand(void);
};

