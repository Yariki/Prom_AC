#ifndef ARDUINOCOMMANDHANDLER_H
#define ARDUINOCOMMANDHANDLER_H

#include <QObject>

#include <vector>

#include "OperationType.h"
#include "CommandType.h"
#include "ObjectInfo.h"
#include "SignalInfo.h"


using std::vector;


class ArduinoCommandHandler : public QObject
{
	Q_OBJECT

public:
	ArduinoCommandHandler();
	virtual ~ArduinoCommandHandler();

public:
	bool firstPreviewCommand(QByteArray response);
	OperationType getOperationType();
	CommandType getCommandType();

	//////////////////////////////////////////////////////////////////////////
	//output commands
	QByteArray getStartCommand(vector<int>* data);
	QByteArray getStopCommand(vector<int>* data);
	QByteArray getEmegencyStopCommand();

	//////////////////////////////////////////////////////////////////////////
	// handle input command
	int getStartedObjectResult(QByteArray& response);
	int getStopedObjectResult(QByteArray& response);
	vector<ObjectInfo*>* getAlertResult(QByteArray& response);
	QString getCommonErrorResult(QByteArray& response);
	QString getErrorResult(QByteArray& response);
	QString getOkResult(QByteArray& response);
	QString getReadyResult(QByteArray& response);
	
private:
	OperationType _lastOperationType;
	CommandType _lastCommandType;


protected:
	CommandType getCommandType(OperationType operation);
	bool firstParseCommand(QStringList& tokenList);
	

};

#endif // ARDUINOCOMMANDHANDLER_H
