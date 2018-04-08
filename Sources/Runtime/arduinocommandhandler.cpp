
#include "stdafx.h"
#include "arduinocommandhandler.h"
#include <QStringList>
#include "StartCommand.h"
#include "StopCommand.h"
#include "EmergencyStopCommand.h"
#include "StartedObjectCommand.h"
#include "StopedObjectCommand.h"
#include "AlertCommand.h"
#include "CommonErrorCommand.h"
#include "ErrorCommand.h"
#include "OkCommand.h"
#include "ReadyCommand.h"


#include "BaseCommand.h"

ArduinoCommandHandler::ArduinoCommandHandler()
	: QObject(nullptr)
{

}

ArduinoCommandHandler::~ArduinoCommandHandler()
{

}

bool ArduinoCommandHandler::firstPreviewCommand( QByteArray response )
{
	bool result = false;
	QString str(response);

	if(!str.length())
		return result;
	
	QStringList tokens = str.split(SPLIT_CHAR);
	if(!tokens.count())
		return result;
	return firstParseCommand(tokens);
}

OperationType ArduinoCommandHandler::getOperationType()
{
	return _lastOperationType;
}

CommandType ArduinoCommandHandler::getCommandType()
{
	return _lastCommandType;
}

CommandType ArduinoCommandHandler::getCommandType( OperationType operation )
{
	switch(operation)
	{
	case OTStarted:
	case OTStoped:
	case OTAlert:
	case OTOk:
	case OTCommonError:
	case OTArduinoReady:
	case OTError:
		return CTInput;

	case OTStart:
	case OTStop:
	case OTEmergencyStop:
		return CTOutput;
	}
	return CommandTypeUnknown;
}

bool ArduinoCommandHandler::firstParseCommand(QStringList& tokenList)
{
	QString strCommand = tokenList[0];
	_lastOperationType  = (OperationType)strCommand.toInt();
	_lastCommandType = getCommandType(_lastOperationType);
	return _lastOperationType != OperationTypeUnknown && _lastCommandType != CommandTypeUnknown;
}

QByteArray ArduinoCommandHandler::getStartCommand( vector<int>* data )
{
	StartCommand* start = new StartCommand();
	start->setContent(data);
	QByteArray result = start->createCommand();
	delete start;
	return result;
}

QByteArray ArduinoCommandHandler::getStopCommand( vector<int>* data )
{
	StopCommand* stop = new StopCommand();
	stop->setContent(data);
	QByteArray result = stop->createCommand();
	delete stop;
	return result;
}

QByteArray ArduinoCommandHandler::getEmegencyStopCommand()
{
	EmergencyStopCommand* stop = new EmergencyStopCommand();
	stop->setContent(nullptr);
	QByteArray result = stop->createCommand();
	delete stop;
	return result;
}

int ArduinoCommandHandler::getStartedObjectResult( QByteArray& response )
{
	StartedObjectCommand* cmd = new StartedObjectCommand();
	cmd->setContent(QString(response));
	int result = cmd->parse() ? cmd->getResult() : -1;
	delete cmd;
	return result;
}

int ArduinoCommandHandler::getStopedObjectResult( QByteArray& response )
{
	StopedObjectCommand* cmd = new StopedObjectCommand();
	cmd->setContent(QString(response));
	int result = cmd->parse() ? cmd->getResult() : -1;
	delete cmd;
	return result;
}

vector<ObjectInfo*>* ArduinoCommandHandler::getAlertResult( QByteArray& response )
{
	AlertCommand* cmd = new AlertCommand();
	cmd->setContent(QString(response));
	vector<ObjectInfo*>* result = cmd->parse() ? cmd->getResult() : nullptr;
	delete cmd;
	return result;
}

QString ArduinoCommandHandler::getCommonErrorResult( QByteArray& response )
{
	CommonErrorCommand* cmd = new CommonErrorCommand();
	cmd->setContent(QString(response));
	QString result = cmd->parse() ? cmd->getResult() : QString();
	delete cmd;
	return result;
}

QString ArduinoCommandHandler::getErrorResult( QByteArray& response )
{
	ErrorCommand* cmd = new ErrorCommand();
	cmd->setContent(QString(response));
	QString result = cmd->parse() ? cmd->getResult() : QString();
	delete cmd;
	return result;
}

QString ArduinoCommandHandler::getOkResult( QByteArray& response )
{
	OkCommand* cmd = new OkCommand();
	cmd->setContent(QString(response));
	QString result = cmd->parse() ? cmd->getResult() : QString();
	delete cmd;
	return result;
}

QString ArduinoCommandHandler::getReadyResult( QByteArray& response )
{
	ReadyCommand* cmd = new ReadyCommand();
	cmd->setContent(QString(response));
	QString result = cmd->parse() ? cmd->getResult() : QString();
	delete cmd;
	return result;
}



