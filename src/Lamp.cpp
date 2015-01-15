#include "Lamp.h"

Lamp::Lamp()
	: visible(false), triggered(false), lampTimeout(1000)
{
	connect(&turnOffTimer, &QTimer::timeout, this, &Lamp::expire);
}

void Lamp::setTimeout(int timeout)
{
	lampTimeout = timeout;
}

void Lamp::setVisible(bool vis)
{
	visible = vis;
	update();
}

void Lamp::turnOff()
{
	triggered = false;
	update();
}

void Lamp::turnOn()
{
	triggered = true;
	turnOffTimer.start(lampTimeout);
	update();
}

bool Lamp::isOn() const
{
	return triggered;
}

void Lamp::expire()
{
	if (isOn())
		emit expired();
	turnOff();
}

QRectF Lamp::boundingRect() const
{
	return QRectF(-30, -50, 60, 100);
}

void Lamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!visible)
		return;

	QColor color;
	if (triggered)
		color = Qt::yellow;
	else
		color = Qt::black;

	painter->setBrush(color);
	painter->drawEllipse(boundingRect());
}
