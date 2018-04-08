///////////////////////////////////////////////////////////
//  StopedObjectCommand.h
//  Implementation of the Class StopedObjectCommand
//  Created on:      31-Jul-2013 10:30:18 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_D41C2AB6_D481_4e67_9763_FB09189BA5D1__INCLUDED_)
#define EA_D41C2AB6_D481_4e67_9763_FB09189BA5D1__INCLUDED_

#include "InputCommand.h"

class StopedObjectCommand : public InputCommand<int>
{

public:
	StopedObjectCommand();
	virtual ~StopedObjectCommand();

	virtual int getResult();
	virtual bool parse();

};
#endif // !defined(EA_D41C2AB6_D481_4e67_9763_FB09189BA5D1__INCLUDED_)
