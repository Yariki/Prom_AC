#include "StdAfx.h"
#include "baseuiwidget.h"



BaseUIWidget::BaseUIWidget(QWidget *parent)
	: QWidget(parent)
{
	setMinimumSize(100,100 + MINHEIGHT_TOOLBAR_INDICATOR);
}

BaseUIWidget::~BaseUIWidget()
{

}

void BaseUIWidget::paintEvent( QPaintEvent* args )
{
	QPainter canvas(this);
	const QRect& rect = args->rect();
	QRect r = QRect(0,0,rect.width() - 1,rect.height() - 1);
	canvas.setBackground(QBrush(Qt::transparent));
	canvas.fillRect(rect,Qt::BrushStyle::SolidPattern);
	canvas.setRenderHint(QPainter::Antialiasing);
	canvas.setPen(QPen(QBrush(Qt::green),3));
	//canvas.drawRect(r);
	renderTemplate(&canvas);
}

void BaseUIWidget::mousePressEvent( QMouseEvent* args )
{
	if(args->button() == Qt::LeftButton)
	{
		emit onClick(this);
	}
}

void BaseUIWidget::mouseMoveEvent( QMouseEvent* args )
{

}

void BaseUIWidget::Start()
{
	throw std::exception("The method or operation is not implemented.");
}

void BaseUIWidget::Stop()
{
	throw std::exception("The method or operation is not implemented.");
}

void BaseUIWidget::EmergencyStop()
{
	throw std::exception("The method or operation is not implemented.");
}

IOName BaseUIWidget::getName()
{
	throw std::exception("The method or operation is not implemented.");
}

int BaseUIWidget::getPriority()
{
	throw std::exception("The method or operation is not implemented.");
}

void BaseUIWidget::setPriority( int priority )
{
	throw std::exception("The method or operation is not implemented.");
}
