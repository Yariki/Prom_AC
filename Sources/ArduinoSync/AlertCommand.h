///////////////////////////////////////////////////////////
//  AlertCommand.h
//  Implementation of the Class AlertCommand
//  Created on:      31-Jul-2013 10:40:56 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_71E49230_2153_44ca_8F62_3164C8AC577D__INCLUDED_)
#define EA_71E49230_2153_44ca_8F62_3164C8AC577D__INCLUDED_

#include <vector>
#include "InputCommand.h"
#include "ObjectInfo.h"

using std::vector;

class AlertCommand : public InputCommand<vector<ObjectInfo*>*>
{

public:
	AlertCommand();
	virtual ~AlertCommand();

	virtual vector<ObjectInfo*>* getResult();
	virtual bool parse();

};
#endif // !defined(EA_71E49230_2153_44ca_8F62_3164C8AC577D__INCLUDED_)
