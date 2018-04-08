///////////////////////////////////////////////////////////
//  OutputCommand.h
//  Implementation of the Class OutputCommand
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_47E08747_C2E8_4170_B080_A5E9FF8F0AB5__INCLUDED_)
#define EA_47E08747_C2E8_4170_B080_A5E9FF8F0AB5__INCLUDED_

#include <QByteArray>
#include "CommandType.h"
#include "OperationType.h"
#include "BaseCommand.h"
#include <vector>

using std::vector;

class OutputCommand : public BaseCommand
{
protected:
	vector<int>* _content;

public:
	OutputCommand();
	virtual ~OutputCommand();
	virtual QByteArray createCommand(vector<int>* content);
	virtual QByteArray createCommand() = 0;
	virtual void setContent(vector<int>* content);

protected:
	QByteArray createOutputCommand(OperationType ct);

};
#endif // !defined(EA_47E08747_C2E8_4170_B080_A5E9FF8F0AB5__INCLUDED_)
