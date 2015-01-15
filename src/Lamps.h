#pragma once

#include <QtWidgets>

#include "Experiment.h"

class Lamps : public QMainWindow {
public:
	Lamps();

	void keyPressEvent(QKeyEvent *event);

private:
	Experiment experiment;
};