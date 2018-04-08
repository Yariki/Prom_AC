///////////////////////////////////////////////////////////
//  InputCommand.h
//  Implementation of the Class InputCommand
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_FFA12663_43BC_4f2c_A0D5_6453B0B43B64__INCLUDED_)
#define EA_FFA12663_43BC_4f2c_A0D5_6453B0B43B64__INCLUDED_

#include "CommandType.h"
#include "OperationType.h"
#include "BaseCommand.h"
#include <QString>

template<class T>
class InputCommand : public BaseCommand
{
protected:
	T _result;
	QString _content;

public:
	InputCommand();
	virtual ~InputCommand();

public:
	virtual bool parse() = 0;
	virtual T getResult() = 0;
	virtual bool parse(QString content);
	virtual void setContent(QString content);

};

template<class T>
InputCommand<T>::InputCommand(){
	_commandType = CommandType::CTInput;
}

template<class T>
InputCommand<T>::~InputCommand(){}

template<class T>
bool InputCommand<T>::parse(QString content){
	setContent(content);
	return parse();
}

template<class T>
void InputCommand<T>::setContent(QString content){
	_content = content;
}

#endif // !defined(EA_FFA12663_43BC_4f2c_A0D5_6453B0B43B64__INCLUDED_)
