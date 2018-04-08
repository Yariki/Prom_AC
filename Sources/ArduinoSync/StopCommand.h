///////////////////////////////////////////////////////////
//  StopCommand.h
//  Implementation of the Class StopCommand
//  Created on:      31-Jul-2013 10:10:44 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_087200A9_DB1F_4868_91CD_E4DE43C5BDAC__INCLUDED_)
#define EA_087200A9_DB1F_4868_91CD_E4DE43C5BDAC__INCLUDED_

#include "OutputCommand.h"

class StopCommand : public OutputCommand
{

public:
	StopCommand();
	virtual ~StopCommand();

	QByteArray createCommand() override;

};
#endif // !defined(EA_087200A9_DB1F_4868_91CD_E4DE43C5BDAC__INCLUDED_)
