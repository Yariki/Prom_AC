///////////////////////////////////////////////////////////
//  StartCommand.h
//  Implementation of the Class StartCommand
//  Created on:      31-Jul-2013 10:10:41 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_EC25F7F5_881E_4e21_966F_5586528C7DC5__INCLUDED_)
#define EA_EC25F7F5_881E_4e21_966F_5586528C7DC5__INCLUDED_

#include "OutputCommand.h"

class StartCommand : public OutputCommand
{

public:
	StartCommand();
	virtual ~StartCommand();

	QByteArray createCommand() override;

};
#endif // !defined(EA_EC25F7F5_881E_4e21_966F_5586528C7DC5__INCLUDED_)
