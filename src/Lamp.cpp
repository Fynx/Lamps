#include "Lamp.h"

Lamp::Lamp(int lampTimeout)
	: triggered(false), lampTimeout(lampTimeout)
{
	connect(&turnOffTimer, &QTimer::timeout, this, &Lamp::turnOff);
}

void Lamp::turnOff()
{
	triggered = false;
}

void Lamp::turnOn()
{
	triggered = true;
	turnOffTimer.start(lampTimeout);
}

QRectF Lamp::boundingRect() const
{
	return QRectF(-30, -50, 60, 100);
}

void Lamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QColor color;
	if (triggered)
		color = Qt::yellow;
	else
		color = Qt::black;

	painter->setBrush(color);
	painter->drawEllipse(boundingRect());
}
