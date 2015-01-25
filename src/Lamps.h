#pragma once

#include <QtWidgets>

#include "ControlPanel.h"
#include "Experiment.h"

class Lamps : public QMainWindow {
public:
	Lamps();

	void keyPressEvent(QKeyEvent *event);

private:
	void settingsSet();

	void start();
	void quit();

	QStackedWidget *stackedWidget;
	ControlPanel controlPanel;
	Experiment experiment;
};