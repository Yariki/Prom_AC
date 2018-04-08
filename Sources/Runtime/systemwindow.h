#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QWidget>
#include "BaseSystemObject.h"
#include "WidgetUIObject.h"
#include "qpainterframe.h"
#include "usbport.h"
#include "ISendDataCallback.h"
#include "IUILogger.h"

class SystemWindow : public QWidget, public ISendDataCallback
{
	Q_OBJECT

public:
	SystemWindow(QWidget *parent = 0);
	~SystemWindow();
	void enableConfigurationMode();
	void disableConfigurationMode();
	void setLogger(IUILogger* logger);
	friend class QPainterFrame;
private slots:
	void onModelClicked(BaseUIWidget* obj);
	void onComboBoxInputChanged(int index);
	void onComboBoxOutputChanged(int index);
	void onStateChanged(int state);
	void readData();

signals:
	void coordinateChanged(int x, int y);

private:
	QVBoxLayout *verticalLayout;
	QHBoxLayout *horizontalLayout;
	QFrame *settingsFrame;
	QPainterFrame *paintFrame;
	QComboBox	*comboBoxInput;
	QComboBox	*comboBoxOutput;
	QCheckBox	*checkBoxActive;
	IUILogger* _logger;

	BaseSystemObject* _system;
	WidgetUIObject* _activeUiObject;
	UsbPort * _port;
	
	vector<WidgetUIObject*>* _listWidgets;
	bool _lockComboChanging;

protected:
	void setupUi(QWidget *SystemWindow);
	void retranslateUi(QWidget *SystemWindow);
	void paintEvent(QPaintEvent *pe);
	void InternalLog(QString message);

public:
	void loadSystem();
	void closeSystem();
	void startSystem();
	void stopSystem();
	void sendData(QByteArray& data) override;
private:
	void prepareInputCombo(const BaseModelObject* model);
	void prepareOutputCombo(const BaseModelObject* model);
	void setupCombobox(QComboBox* combo, vector<IOName>* names);
	void setCurrentComboBoxItem(QComboBox* combo, IOName* name);
	void updateCoordinateForMain(int x, int y);

};

#endif // SYSTEMWINDOW_H
