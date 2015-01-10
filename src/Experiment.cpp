#include "Experiment.h"

static const QList<Qt::Key> keys {
	Qt::Key_Q,
	Qt::Key_W,
	Qt::Key_E,
	Qt::Key_R,
	Qt::Key_T,
	Qt::Key_Y,
	Qt::Key_U,
	Qt::Key_I,
	Qt::Key_O,
	Qt::Key_P,
};

Experiment::Experiment()
	: QGraphicsView()
{
	int lampTimeout = 1000;
	QGraphicsScene *scene = new QGraphicsScene();

	QPointF position(100.0, 200.0);
	qreal diff = 100.0;

	for (Qt::Key key : keys) {
		Lamp *lamp = new Lamp(lampTimeout);
		lamp->setPos(position);
		position.rx() += diff;
		lamps[key] = lamp;
		scene->addItem(lamp);
	}

	setScene(scene);
}

Experiment::~Experiment()
{
	qDeleteAll(lamps);
}
