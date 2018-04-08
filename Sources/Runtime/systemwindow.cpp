#include "StdAfx.h"
#include <QObject>
#include "systemwindow.h"
#include "ConnectionUIObject.h"

SystemWindow::SystemWindow(QWidget *parent)
	: QWidget(parent,Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint )
{
	setupUi(this);
	_system = nullptr;
	_activeUiObject = nullptr;
	_lockComboChanging = false;
	_port = new UsbPort("usbsettings.xml");
	if(_port->init())
	{
		connect(_port,SIGNAL(readyRead()),this,SLOT(readData()));
	}
	else
	{
		delete _port;
		_port = nullptr;
	}
}

SystemWindow::~SystemWindow()
{
	if(_system != nullptr)
	{
		_system->Stop();
		delete _system;
		_system = nullptr;
	}
	if(_port != nullptr)
	{
		delete _port;
	}
}

void SystemWindow::loadSystem()
{
	_system = new BaseSystemObject(paintFrame);
	_system->loadSystem();
	_listWidgets = _system->getUIObjects();
	for(int i = 0; i < _listWidgets->size();i++)
	{
		_listWidgets->at(i)->prepareForRendering();
		connect((BaseUIWidget*)_listWidgets->at(i),SIGNAL(onClick(BaseUIWidget*)),this,SLOT(onModelClicked(BaseUIWidget*)));
	}
	_system->setSendDataCallback(this);
	connect(comboBoxInput,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxInputChanged(int)));
	connect(comboBoxOutput,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxOutputChanged(int)));
	connect(checkBoxActive,SIGNAL(stateChanged(int)),this,SLOT(onStateChanged(int)));

	showMaximized();
}

void SystemWindow::closeSystem()
{
	if(_system != nullptr)
	{
		_system->Stop();
		delete _system;
		_system = nullptr;
	}
	
}

void SystemWindow::setupUi(QWidget *SystemWindow)
{
	if (SystemWindow->objectName().isEmpty())
		SystemWindow->setObjectName(QStringLiteral("SystemWindow"));
	SystemWindow->resize(1062, 719);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(SystemWindow->sizePolicy().hasHeightForWidth());
	SystemWindow->setSizePolicy(sizePolicy);
	SystemWindow->setMinimumSize(QSize(550, 650));
	SystemWindow->setAutoFillBackground(true);
	verticalLayout = new QVBoxLayout(SystemWindow);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	verticalLayout->setContentsMargins(1, 1, 1, 1);
	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	settingsFrame = new QFrame(SystemWindow);
	settingsFrame->setObjectName(QStringLiteral("settingsFrame"));
	settingsFrame->setMaximumSize(QSize(250, 16777215));
	settingsFrame->setFrameShape(QFrame::StyledPanel);
	settingsFrame->setFrameShadow(QFrame::Raised);
	// settings ui
	QVBoxLayout * vbox = new QVBoxLayout();
	QLabel *input = new QLabel("Input:",settingsFrame);
	QLabel *output = new QLabel("Output:",settingsFrame);
	QLabel *active = new QLabel("Is Active:",settingsFrame);
	comboBoxInput = new QComboBox(settingsFrame);
	comboBoxOutput = new QComboBox(settingsFrame);
	checkBoxActive = new QCheckBox(settingsFrame);
	QHBoxLayout *h1 = new QHBoxLayout();		
	h1->addWidget(input);
	h1->addWidget(comboBoxInput);
	vbox->addLayout(h1);
	h1 = new QHBoxLayout();		
	h1->addWidget(output);
	h1->addWidget(comboBoxOutput);
	vbox->addLayout(h1);
	h1 = new QHBoxLayout();		
	h1->addWidget(active);
	h1->addWidget(checkBoxActive);
	vbox->addLayout(h1);
	vbox->addSpacing(10);
	settingsFrame->setLayout(vbox);
	settingsFrame->hide();

	horizontalLayout->addWidget(settingsFrame);


	paintFrame = new QPainterFrame(SystemWindow);
	paintFrame->setObjectName(QStringLiteral("paintFrame"));
	paintFrame->setFrameShape(QFrame::StyledPanel);
	paintFrame->setFrameShadow(QFrame::Raised);
	horizontalLayout->addWidget(paintFrame);


	verticalLayout->addLayout(horizontalLayout);


	retranslateUi(SystemWindow);

	QMetaObject::connectSlotsByName(SystemWindow);
}

void SystemWindow::retranslateUi(QWidget *SystemWindow)
{
	SystemWindow->setWindowTitle(QApplication::translate("SystemWindow", "SystemWindow", 0));
} 

void SystemWindow::onModelClicked( BaseUIWidget* obj )
{
	LOG_INFO("click");
	auto widget = static_cast<WidgetUIObject*>(obj);
	if(widget == nullptr)
		return;
	_activeUiObject = widget;
	_lockComboChanging = true;
	prepareInputCombo(widget->getModel());
	prepareOutputCombo(widget->getModel());
	checkBoxActive->setCheckState(_activeUiObject->getModel()->IsActive() ? Qt::Checked : Qt::Unchecked);
	_lockComboChanging = false;
}

void SystemWindow::enableConfigurationMode()
{
	settingsFrame->show();
}

void SystemWindow::disableConfigurationMode()
{
	settingsFrame->hide();
}

void SystemWindow::prepareInputCombo(const BaseModelObject* model)
{
	auto inputs = model->getInputsListName();
	setupCombobox(comboBoxInput,&inputs);
	auto active = model->getActiveInput();
	if(!active.IsEmpty())
	{
		setCurrentComboBoxItem(comboBoxInput,&active);
	}
}

void SystemWindow::prepareOutputCombo(const BaseModelObject* model)
{
	auto outputs = model->getOutputListName();
	setupCombobox(comboBoxOutput,&outputs);
	auto active = model->getActiveOutput();
	if (!active.IsEmpty())
	{
		setCurrentComboBoxItem(comboBoxOutput,&active);
	}
}

void SystemWindow::onComboBoxInputChanged( int index )
{
	if(_lockComboChanging || index < 0)
		return;
	auto data = comboBoxInput->itemData(index).toUuid();
	auto text = comboBoxInput->itemText(index);
	if(_activeUiObject)
	{
		IOName active (text,data);
		_activeUiObject->getModel()->setActiveInput(active);
	}
	
}

void SystemWindow::onComboBoxOutputChanged( int index )
{
	if(_lockComboChanging || index < 0)
		return;
	auto data = comboBoxOutput->itemData(index).toUuid();
	auto text = comboBoxOutput->itemText(index);
	if(_activeUiObject)
	{
		IOName active (text,data);
		_activeUiObject->getModel()->setActiveOutput(active);
	}
	
}

void SystemWindow::setupCombobox(QComboBox* combo, vector<IOName>* names )
{
	if(!combo)
		return;
	combo->clear();
	for(int i = 0; i < names->size();i++)
	{
		combo->addItem(names->at(i).getName(),names->at(i).getId());
	}
}

void SystemWindow::setCurrentComboBoxItem(QComboBox*combo, IOName* name )
{
	int index = -1;
	for(int i = 0; i < combo->count();i++)
	{
		auto data = combo->itemData(i);
		if(name->getId() == data)
		{
			index = i;
			break;
		}
	}
	combo->setCurrentIndex(index > -1 ? index : 0);
}

void SystemWindow::paintEvent( QPaintEvent *pe )
{
}

void SystemWindow::updateCoordinateForMain( int x, int y )
{
	emit coordinateChanged(x,y);
}

void SystemWindow::onStateChanged( int state )
{
	if(_lockComboChanging)
		return;

	switch(state)
	{
	case Qt::Unchecked:
		_activeUiObject->getModel()->setActive(false);
		_system->removeActiveModel(_activeUiObject->getModel());
		break;
	case Qt::Checked:
		_activeUiObject->getModel()->setActive(true);
		_system->addActiveModel(_activeUiObject->getModel());
		break;
	}
}

void SystemWindow::startSystem()
{
	if(_system == nullptr)
		return;
	_system->Start();
}

void SystemWindow::stopSystem()
{
	if(_system == nullptr)
		return;
	_system->Stop();
}

void SystemWindow::readData()
{
	if(_port == nullptr)
		return;
	QByteArray res = _port->read();
	_system->readData(res);
}

void SystemWindow::sendData( QByteArray& data )
{
	if(_port != nullptr)
	{
		_port->write(data);
	}
}

void SystemWindow::setLogger(IUILogger* logger )
{
	if(logger == nullptr)
		return;
	_logger = logger;
}

void SystemWindow::InternalLog( QString message )
{
	if(_logger == nullptr)
		return;
	_logger->Log(message);
}


