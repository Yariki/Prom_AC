///////////////////////////////////////////////////////////
//  EmergencyStopCommand.h
//  Implementation of the Class EmergencyStopCommand
//  Created on:      31-Jul-2013 10:10:47 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_005F8FD7_0794_408a_AC99_4A5F42277320__INCLUDED_)
#define EA_005F8FD7_0794_408a_AC99_4A5F42277320__INCLUDED_

#include "OutputCommand.h"

class EmergencyStopCommand : public OutputCommand
{

public:
	EmergencyStopCommand();
	virtual ~EmergencyStopCommand();

	QByteArray createCommand() override;

};
#endif // !defined(EA_005F8FD7_0794_408a_AC99_4A5F42277320__INCLUDED_)
