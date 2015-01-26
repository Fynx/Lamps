#pragma once

#include <QtWidgets>

#include "ControlPanel.h"
#include "Experiment.h"
#include "UserPanel.h"

class Lamps : public QMainWindow {
public:
	Lamps();

	void keyPressEvent(QKeyEvent *event);

private:
	void settingsSet();

	void start();
	void quit();
	void save();
	bool load();

	QStackedWidget *stackedWidget;
	ControlPanel controlPanel;
	Experiment experiment;
	UserPanel userPanel;
	QTime experimentStartTime;
	int sessionNumber;

	QString previousInfo;
};