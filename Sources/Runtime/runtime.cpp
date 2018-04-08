#include "stdafx.h"
#include "runtime.h"
#include <FileAppender.h>
#include <PlainTextAppender.h>

Runtime::Runtime(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mdiArea = new QMdiArea();
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);
	windowMapper = new QSignalMapper(this);
	FileAppender* con = new FileAppender("test.log");
	PlainTextAppender* plainText = new PlainTextAppender(ui.plainTextEdit);
	con->setFormat("%t{HH:mm:ss.zzz} [-7l] <%C> %m\n");
	Logger::registerAppender(con);
	Logger::registerAppender(plainText);
	Init();
	LOG_INFO("Start application");
	
}

Runtime::~Runtime()
{
	if(windowMapper != nullptr)
	{
		delete windowMapper;
	}
	if(mdiArea  != nullptr)
	{
		delete mdiArea;
	}
	if(_labelCoordinat != nullptr)
	{
		delete _labelCoordinat;
	}
}

void Runtime::Init()
{
	bindActionAndSlots();
	_labelCoordinat = new QLabel();
	ui.statusBar->addWidget(_labelCoordinat);

}

void Runtime::closeApp()
{
	QMessageBox mes;
	mes.setText("You really want exit?");
	mes.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	mes.setDefaultButton(QMessageBox::Cancel);
	mes.setIcon(QMessageBox::Question);
	int ret = mes.exec();
	switch(ret)
	{
	case QMessageBox::Cancel:
			return;
	}
	LOG_INFO("Exit application");
	close();
}

void Runtime::bindActionAndSlots()
{
	connect(ui.actionExit,SIGNAL(triggered()),this,SLOT(closeApp()));
	connect(ui.actionLoad,SIGNAL(triggered()),this,SLOT(openSystemWindow()));
	connect(ui.actionUnload,SIGNAL(triggered()),this,SLOT(closeSystemWindow()));
	connect(ui.actionEnable,SIGNAL(triggered()),this,SLOT(enableConfigMode()));
	connect(ui.actionDisable,SIGNAL(triggered()),this,SLOT(disableConfigMode()));
	connect(ui.actionStart,SIGNAL(triggered()),this,SLOT(onStartSystem()));
	connect(ui.actionStop,SIGNAL(triggered()),this,SLOT(onStopSystem()));
	ui.actionDisable->setEnabled(false);
}

void Runtime::openSystemWindow()
{
	_systemWindow = new SystemWindow();
	_systemWindow->setLogger(this);
	mdiArea->addSubWindow(_systemWindow);
	_systemWindow->loadSystem();
	ui.actionLoad->setEnabled(false);
	ui.actionUnload->setEnabled(true);
	connect(_systemWindow,SIGNAL(coordinateChanged(int,int)),this,SLOT(updatedCoordinate(int,int)));
}

void Runtime::closeSystemWindow()
{
	if(_systemWindow != nullptr)
	{
		_systemWindow->closeSystem();
		mdiArea->removeSubWindow(_systemWindow);
		mdiArea->closeAllSubWindows();
		delete _systemWindow;
		_systemWindow = nullptr;
	}
	ui.actionLoad->setEnabled(true);
	ui.actionUnload->setEnabled(false);
}

void Runtime::enableConfigMode()
{
	if(_systemWindow == nullptr)
		return;
	_systemWindow->enableConfigurationMode();
	ui.actionEnable->setEnabled(false);
	ui.actionDisable->setEnabled(true);
}

void Runtime::disableConfigMode()
{
	if(_systemWindow == nullptr)
		return;
	_systemWindow->disableConfigurationMode();
	ui.actionEnable->setEnabled(true);
	ui.actionDisable->setEnabled(false);
}

void Runtime::updatedCoordinate( int x, int y )
{
	_labelCoordinat->setText("X = " + QString::number(x) + "; Y = " + QString::number(y));
}

void Runtime::onStartSystem()
{
	if(_systemWindow == nullptr)
		return;
	_systemWindow->startSystem();
}

void Runtime::onStopSystem()
{
	if(_systemWindow == nullptr)
		return;
	_systemWindow->stopSystem();
}

void Runtime::Log( QString message )
{
	if(ui.plainTextEdit == nullptr)
		return;
	ui.plainTextEdit->appendPlainText(message);
}


