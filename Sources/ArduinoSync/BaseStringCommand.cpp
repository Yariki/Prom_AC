#include "BaseStringCommand.h"
#include <QStringList>


BaseStringCommand::BaseStringCommand(void)
{
}


BaseStringCommand::~BaseStringCommand(void)
{
}

QString BaseStringCommand::getResult()
{
	return _result;
}

bool BaseStringCommand::parse()
{
	QStringList tokens = _content.split(SPLIT_CHAR);
	if(!tokens.count() || tokens.count() == 1)
		return false;
	_result = tokens[1].replace(";",".");
	return true;
}
