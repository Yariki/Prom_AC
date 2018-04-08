///////////////////////////////////////////////////////////
//  StartedObjectCommand.h
//  Implementation of the Class StartedObjectCommand
//  Created on:      31-Jul-2013 10:15:14 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_9DCC86A2_49A3_49a5_85B7_DE87515C10D2__INCLUDED_)
#define EA_9DCC86A2_49A3_49a5_85B7_DE87515C10D2__INCLUDED_

#include "InputCommand.h"

class StartedObjectCommand : public InputCommand<int>
{

public:
	StartedObjectCommand();
	virtual ~StartedObjectCommand();

	virtual int getResult();
	virtual bool parse();

};
#endif // !defined(EA_9DCC86A2_49A3_49a5_85B7_DE87515C10D2__INCLUDED_)
