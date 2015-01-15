#pragma once

#include <QtWidgets>

class Lamp : public QGraphicsObject {
Q_OBJECT;
public:
	Lamp();

	void setTimeout(int timeout);
	void setVisible(bool vis);

	void turnOff();
	void turnOn();

	bool isOn() const;

signals:
	void expired();

private:
	void expire();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

	bool visible;
	bool triggered;
	QTimer turnOffTimer;
	int lampTimeout;

	QPixmap *pixmap;
};