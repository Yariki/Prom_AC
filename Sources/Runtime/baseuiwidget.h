#ifndef BASEUIWIDGET_H
#define BASEUIWIDGET_H

#include <vector>
#include <map>
#include <QWidget>
#include "IObject.h"

using std::vector;

#define MINHEIGHT_TOOLBAR_INDICATOR 25

#define WORK_COLOR_ACTIVE QColor::fromRgb(26,255,0)
#define WORK_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define STOP_COLOR_ACTIVE QColor::fromRgb(221,255,0)
#define STOP_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define EMERGENCY_COLOR_ACTIVE QColor::fromRgb(255,0,0)
#define EMERGENCY_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define ALARNSWITCH_COLOR_ACTIVE QColor::fromRgb()
#define ALARNSWITCH_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define EMPTY_COLOR_ACTIVE QColor::fromRgb()
#define EMPTY_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define FULL_COLOR_ACTIVE QColor::fromRgb()
#define FULL_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define GATHERTAPE_COLOR_ACTIVE QColor::fromRgb()
#define GATHERTAPE_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define MOROTOVERLOAD_COLOR_ACTIVE QColor::fromRgb()
#define MOROTOVERLOAD_COLOR_DEACTIVE QColor::fromRgb(25,25,25)

#define SHORTCUIRCUIT_COLOR_ACTIVE QColor::fromRgb()
#define SHORTCUIRCUIT_COLOR_DEACTIVE QColor::fromRgb(25,25,25)



class BaseUIWidget : public QWidget,public IObject
{
	Q_OBJECT

public:
	BaseUIWidget(QWidget *parent);
	virtual ~BaseUIWidget();
	virtual void render() = 0;
	virtual void prepareForRendering() = 0;
	virtual void Start();

	virtual void Stop();

	virtual void EmergencyStop();

	virtual IOName getName();

	virtual int getPriority();

	virtual void setPriority( int priority );
protected:
	void mousePressEvent(QMouseEvent* args);
	void mouseMoveEvent(QMouseEvent* args);
	void paintEvent(QPaintEvent* args);
	virtual void renderTemplate(QPainter* canvas) = 0;

signals:
	void onClick(BaseUIWidget* obj);

protected:
	QString _templateName;
	QString _activeInput;
	QString _activeOutput;
	vector<QString> _listInputs;
	vector<QString> _listOutputs;
	int _x;
	int _y;
	int _width;
	int _height;
	
};

#endif // BASEUIWIDGET_H
