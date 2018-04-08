#ifndef TESTPORT_H
#define TESTPORT_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include "usbport.h"
#include "ui_testport.h"
#include "arduinocommandhandler.h"

class TestPort : public QDialog
{
	Q_OBJECT

public:
	TestPort(QWidget *parent = 0);
	virtual ~TestPort();

private slots:
	void readData();
	void onStartClicked();
	void onStopClicked();
	void onEStopClicked();

private:
	void onStopedObject(QByteArray& response);
	void onStartedObject(QByteArray& response);
	void onCommonErrorResult(QByteArray& response);
	void onErrorResult(QByteArray& response);
	void onOkResult(QByteArray& response);
	void onReadyResult(QByteArray& response);
	void onAlertResult(QByteArray& response);

private:
	Ui::TestPortClass ui;
	QPushButton* _buttonStart;
	QPushButton* _buttonStop;
	QPushButton* _buttonEStop;
		
	UsbPort * port;
	ArduinoCommandHandler* _arduinoCommandHandler;

};

#endif // TESTPORT_H
