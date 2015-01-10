#pragma once

#include <QtWidgets>

class Lamp : public QGraphicsObject {
Q_OBJECT;
public:
	Lamp(int lampTimeout);

	void turnOff();
	void turnOn();

	bool isOn();

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

	bool triggered;
	QTimer turnOffTimer;
	int lampTimeout;
};