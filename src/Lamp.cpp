#include "Lamp.h"

Lamp::Lamp()
	: visible(false), triggered(false), lampTimeout(1000)
{
	connect(&turnOffTimer, &QTimer::timeout, this, &Lamp::expire);
	QImage image;
	image.load("data/download.jpg", "JPG");
	pixmap = new QPixmap(QPixmap::fromImage(image));
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
	return QRectF(-64, -96, 128, 194);
}

void Lamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!visible)
		return;

	if (triggered)
		painter->drawPixmap(boundingRect(), *pixmap, QRectF(138, 0, 128, 194));
	else
		painter->drawPixmap(boundingRect(), *pixmap, QRectF(0, 0, 128, 194));
}
