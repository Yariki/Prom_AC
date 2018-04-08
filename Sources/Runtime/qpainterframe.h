#ifndef QPAINTERFRAME_H
#define QPAINTERFRAME_H

#include <QFrame>
#include "systemwindow.h"

class QPainterFrame : public QFrame
{
	Q_OBJECT

public:
	QPainterFrame(QWidget *parent);
	~QPainterFrame();
	friend class SystemWindow;

protected:
	void paintEvent(QPaintEvent * args);
	void mouseMoveEvent(QMouseEvent* args);

private :
	QWidget* _parent;

};

#endif // QPAINTERFRAME_H
