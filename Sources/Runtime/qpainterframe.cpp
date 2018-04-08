#include "StdAfx.h"
#include "qpainterframe.h"
#include "BaseSystemObject.h"
#include "ConnectionUIObject.h"


QPainterFrame::QPainterFrame(QWidget *parent)
	: QFrame(parent)
{
	_parent = parent;
}

QPainterFrame::~QPainterFrame()
{

}

void QPainterFrame::paintEvent( QPaintEvent * args )
{
	QPainter canvas(this);
	const QRect& rect = args->rect();
	canvas.setBackground(QBrush(Qt::black));
	canvas.fillRect(rect,Qt::BrushStyle::SolidPattern);
	SystemWindow* wnd = static_cast<SystemWindow*>(_parent);
	if(wnd == nullptr)
		return;
	canvas.setPen(QPen(QBrush(Qt::green),2));
	for(int i = 0; i < wnd->_system->getConnectionUIObjects()->size();i++)
	{
		ConnectionUIObject * coon = static_cast<ConnectionUIObject*>(wnd->_system->getConnectionUIObjects()->at(i));
		if(coon == nullptr)
			continue;
		coon->renderTemplate(&canvas);
	}
}

void QPainterFrame::mouseMoveEvent( QMouseEvent* args )
{
	QFrame::mouseReleaseEvent(args);
	SystemWindow* wnd = static_cast<SystemWindow*>(_parent);
	if(wnd == nullptr)
		return;
	wnd->updateCoordinateForMain(args->pos().x(),args->pos().y());
}
