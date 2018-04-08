///////////////////////////////////////////////////////////
//  AlertCommand.cpp
//  Implementation of the Class AlertCommand
//  Created on:      31-Jul-2013 10:40:56 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#include "AlertCommand.h"
#include <QtCore/qstringlist.h>

#include "SignalInfo.h"

#define START_CHAR "("
#define FINISH_CHAR ")"
#define SPLIT_SIGNALS_CHAR "/"
#define SPLIT_SIGNALS_VALUE_CHAR ":"

AlertCommand::AlertCommand(){

}

AlertCommand::~AlertCommand(){

}

vector<ObjectInfo*>* AlertCommand::getResult(){

	return  _result;
}

bool AlertCommand::parse(){

	if(!_content.length())
		return false;

	auto tok = _content.split(SPLIT_CHAR);
	if(!tok.count() || tok.count() == 1)
		return false;
	_content = tok[1];
	_result = new vector<ObjectInfo*>;
	QStringList tokens = _content.split(PARAMS_CHAR);
	if(tokens.count() > 0)
	{
		for(int i = 0; i < tokens.count();i++)
		{
			QString current = tokens[i];
			if(current.isEmpty())
				continue;
			if(i == tokens.count() - 1)
			{
				current = current.remove(END_CHAR);
			}
			QString strIdObject = current.left(current.indexOf(START_CHAR));
			int idObj = strIdObject.toInt();
			ObjectInfo* oi = new ObjectInfo(&idObj);
			
			int index1 = current.indexOf(START_CHAR) + 1;
			int lenght = current.indexOf(FINISH_CHAR) - index1;

			QString strData = current.mid(index1,lenght);

			QStringList tokSignals = strData.split(SPLIT_SIGNALS_CHAR);
			if(!tokSignals.count())
				continue;

			for (int j = 0; j < tokSignals.count();j++)
			{
				QString strSignal = tokSignals[j];
				if(!strSignal.length())
					continue;
				QStringList	toks = strSignal.split(SPLIT_SIGNALS_VALUE_CHAR);
				if(!toks.count() || toks.count() < 2)
					continue;
				int idSig = toks[0].toInt();
				int valSig = toks[1].toInt();
				oi->insertSignalInfo(new SignalInfo(&idSig,&valSig));
			}
			_result->push_back(oi);
		}
	}
	return true;
}