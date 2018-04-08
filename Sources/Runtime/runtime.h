#ifndef RUNTIME_H
#define RUNTIME_H

#include <QtWidgets/QMainWindow>
#include "ui_runtime.h"
#include "systemwindow.h"
#include "IUILogger.h"

class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;

class Runtime : public QMainWindow,public IUILogger
{
	Q_OBJECT

public:
	Runtime(QWidget *parent = 0);
	~Runtime();
	virtual void Log(QString message);

private:
	Ui::RuntimeClass ui;

	QMdiArea* mdiArea;
	QSignalMapper* windowMapper;
	SystemWindow* _systemWindow;
	QLabel* _labelCoordinat;



private slots:
	void closeApp();
	void openSystemWindow();
	void closeSystemWindow();
	void enableConfigMode();
	void disableConfigMode();
	void updatedCoordinate(int x, int y);
	void onStartSystem();
	void onStopSystem();

private:
	void Init();
	void bindActionAndSlots();

};

#endif // RUNTIME_H
