#include "Lamps.h"

Lamps::Lamps()
{
	setCentralWidget(&experiment);
	showFullScreen();

	experiment.setRandom(true);
	experiment.setCheckProbability(0.3);
	experiment.setTimeout(2000);
	experiment.setExperimentTime(20001);

	QMenu *menuFile = menuBar()->addMenu("File");

	QAction *actionStart = new QAction("Start", this);
	actionStart->setShortcut(Qt::CTRL + Qt::Key_N);
	connect(actionStart, &QAction::triggered, &experiment, &Experiment::start);
	menuFile->addAction(actionStart);

	QAction *actionQuit = new QAction("Quit", this);
	actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
	connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	menuBar()->show();
}

void Lamps::keyPressEvent(QKeyEvent *event)
{
	if (!event->modifiers())
		experiment.trigger(Qt::Key(event->key()));
	else
		QWidget::keyPressEvent(event);
}