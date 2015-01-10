#pragma once

#include <QtWidgets>

#include "Experiment.h"

class Lamps : public QMainWindow {
public:
	Lamps();

private:
	Experiment experiment;
};