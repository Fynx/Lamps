#pragma once

#include <QtWidgets>
#include "Lamp.h"

class Experiment : public QGraphicsView {
public:
	Experiment();
	~Experiment();

private:
	QHash<Qt::Key, Lamp *> lamps;
};