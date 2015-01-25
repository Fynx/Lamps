#include "Lamps.h"

Lamps::Lamps()
	: controlPanel(this)
{
	stackedWidget = new QStackedWidget();

	stackedWidget->addWidget(&controlPanel);
	stackedWidget->addWidget(&experiment);

	setCentralWidget(stackedWidget);
	showFullScreen();

	connect(&controlPanel, &ControlPanel::start, this, &Lamps::start);
	connect(&controlPanel, &ControlPanel::quit, this, &Lamps::quit);

	QMenu *menuFile = menuBar()->addMenu("File");

	QAction *actionStart = new QAction("Start", this);
	actionStart->setShortcut(Qt::CTRL + Qt::Key_N);
	connect(actionStart, &QAction::triggered, &experiment, &Experiment::start);
	menuFile->addAction(actionStart);

	QAction *actionQuit = new QAction("Quit", this);
	actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
	connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	stackedWidget->setCurrentIndex(0);
}

void Lamps::keyPressEvent(QKeyEvent *event)
{
	if (!event->modifiers())
		experiment.trigger(Qt::Key(event->key()));
	else
		QWidget::keyPressEvent(event);
}

void Lamps::settingsSet()
{
	experiment.setWithFeedback(controlPanel.withFeedback());
	experiment.setWithTimer(controlPanel.withTimer());
	experiment.setTimeout(controlPanel.timeout());
	experiment.setRandom(controlPanel.isRandom());
	experiment.setCheckProbability(controlPanel.checkProbability());
	experiment.setExperimentTime(controlPanel.experimentTime());

	experiment.setConfigurations();
}

void Lamps::start()
{
	settingsSet();
	stackedWidget->setCurrentIndex(1);
}

void Lamps::quit()
{
	close();
}
