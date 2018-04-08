#include "testport.h"
#include <vector>

using std::vector;

TestPort::TestPort(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	port = new UsbPort("usbsettings.xml");
	if(port->init())
	{
		connect(port,SIGNAL(readyRead()),this,SLOT(readData()));
	}
	else
	{
		delete port;
		port = nullptr;
	}
	_buttonStart = ui.buttonStart;
	_buttonStop = ui.buttonStop;
	_buttonEStop = ui.buttonEStop;
	_arduinoCommandHandler = new ArduinoCommandHandler();

	connect(_buttonStart,SIGNAL(clicked()),this,SLOT(onStartClicked()));
	connect(_buttonStop,SIGNAL(clicked()),this,SLOT(onStopClicked()));
	connect(_buttonEStop,SIGNAL(clicked()),this,SLOT(onEStopClicked()));

}

TestPort::~TestPort()
{

}

void TestPort::readData()
{
	if(port != nullptr)
	{
		QByteArray res = port->read();
		//ui.plainTextEdit->insertPlainText(QString(res) + "\n");
		if(_arduinoCommandHandler->firstPreviewCommand(res))
		{
			if(_arduinoCommandHandler->getCommandType() == CTInput)
			{
				switch(_arduinoCommandHandler->getOperationType())
				{
				case OTStoped:
					onStopedObject(res);
					break;
				case OTStarted:
					onStartedObject(res);
					break;
				case OTAlert:
					onAlertResult(res);
					break;
				case OTCommonError:
					onCommonErrorResult(res);
					break;
				case OTError:
					onErrorResult(res);
					break;
				case OTOk:
					onOkResult(res);
					break;
				case OTArduinoReady:
					onReadyResult(res);
					break;
				}
			}

		}
	}
}

void TestPort::onStartClicked()
{
	vector<int> vec;
	vec.push_back(1);
	//vec.push_back(3);
	QByteArray sendData = _arduinoCommandHandler->getStartCommand(&vec);

	port->write(sendData);
}

void TestPort::onStopClicked()
{
	vector<int> vec;
	//vec.push_back(3);
	vec.push_back(1);
	QByteArray sendData = _arduinoCommandHandler->getStopCommand(&vec);
	port->write(sendData);
}

void TestPort::onEStopClicked()
{
	QByteArray sendData = _arduinoCommandHandler->getEmegencyStopCommand();
	port->write(sendData);
}

void TestPort::onStopedObject(QByteArray& response)
{
	int id = _arduinoCommandHandler->getStopedObjectResult(response);
	ui.plainTextEdit->appendPlainText("Stoped: " + QString::number(id) + "\n");
}

void TestPort::onStartedObject( QByteArray& response )
{
	int id = _arduinoCommandHandler->getStartedObjectResult(response);
	ui.plainTextEdit->appendPlainText("Started: " + QString::number(id) + "\n");
}

void TestPort::onCommonErrorResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getCommonErrorResult(response);
	ui.plainTextEdit->appendPlainText("Common error: " + resp + "\n");
}

void TestPort::onErrorResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getErrorResult(response);
	ui.plainTextEdit->appendPlainText("Error: " + resp + "\n");
}

void TestPort::onOkResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getOkResult(response);
	ui.plainTextEdit->appendPlainText("Ok: " + resp + "\n");
}

void TestPort::onReadyResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getReadyResult(response);
	ui.plainTextEdit->appendPlainText("Ready: " + resp + "\n");
}

void TestPort::onAlertResult( QByteArray& response )
{
	vector<ObjectInfo*>* result = _arduinoCommandHandler->getAlertResult(response);
	if(result != nullptr)
	{
		ui.plainTextEdit->appendPlainText("Alelrt. \n");
		for(auto it = result->begin(); it != result->end(); it++)
		{
			ObjectInfo* obj = static_cast<ObjectInfo*>(*it);
			ui.plainTextEdit->appendPlainText("--Object ID: " + QString::number(obj->getId())+" \n");

			vector<SignalInfo*>* listSignals = obj->getSignalsInfo();
			for(auto itSig = listSignals->begin(); itSig != listSignals->end(); itSig++)
			{
				SignalInfo* sig = static_cast<SignalInfo*>(*itSig);
				ui.plainTextEdit->appendPlainText("----Signal : ID=" + QString::number(sig->getId()) + "; Value="+QString::number(sig->getValue()) +" \n");
			}
			delete (*it);
			*it = nullptr;
		}
		delete result;
		result = nullptr;
	}
}




