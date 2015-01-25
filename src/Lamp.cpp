#include "Lamp.h"

Lamp::Lamp(const QString &key)
	: key(key), visible(false), triggered(false), lampTimeout(1000)
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
	turnOffTimer.stop();
	update();
}

void Lamp::turnOn()
{
	triggered = true;
	if (lampTimeout)
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
	return QRectF(-64, -96, 128, 194 + 100);
}

void Lamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!visible)
		return;

	if (triggered)
		painter->drawPixmap(QRectF(-64, -96, 128, 194), *pixmap, QRectF(138, 0, 128, 194));
	else
		painter->drawPixmap(QRectF(-64, -96, 128, 194), *pixmap, QRectF(0, 0, 128, 194));
	QPen pen;
	pen.setWidth(5);
	pen.setColor(Qt::white);
	painter->setPen(pen);
	painter->drawText(QPointF(-10, 120), key);
}
