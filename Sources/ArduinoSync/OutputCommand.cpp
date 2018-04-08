///////////////////////////////////////////////////////////
//  OutputCommand.cpp
//  Implementation of the Class OutputCommand
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "OutputCommand.h"
#include <QString>



OutputCommand::OutputCommand(){
	_commandType = CommandType::CTOutput;
}



OutputCommand::~OutputCommand(){

}


QByteArray OutputCommand::createCommand(vector<int>* content){
	setContent(content);
	return  createCommand();
}

void OutputCommand::setContent(vector<int>* content){
	_content = content;
}

QByteArray OutputCommand::createOutputCommand( OperationType ct)
{
	if(ct == OperationTypeUnknown)
		return QByteArray();

	QString result;
	if(ct == OTStart || ct == OTStop)
	{
		if(_content == nullptr)
			return QByteArray();
		QString strIDs;
		for(auto iter = _content->begin(); iter != _content->end();iter++)
		{
			strIDs.append(QString().setNum(*iter)+PARAMS_CHAR);
		}
		result = QString("%1,%2%3").arg(ct).arg(strIDs).arg(END_CHAR);
	}
	else
	{
		result = QString("%1%3").arg(ct).arg(END_CHAR);
	}
	return result.toLatin1();
}
