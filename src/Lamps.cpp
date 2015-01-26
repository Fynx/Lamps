#include "CSVWriter.h"
#include "Lamps.h"

Lamps::Lamps()
	: controlPanel(this), userPanel(this)
{
	stackedWidget = new QStackedWidget();

	stackedWidget->addWidget(&controlPanel);
	stackedWidget->addWidget(&userPanel);
	stackedWidget->addWidget(&experiment);

	setCentralWidget(stackedWidget);
	showFullScreen();

	connect(&controlPanel, &ControlPanel::start, this, &Lamps::settingsSet);
	connect(&controlPanel, &ControlPanel::quit, this, &Lamps::quit);
	connect(&experiment, &Experiment::experimentEnded, this, &Lamps::settingsSet);
	connect(&userPanel, &UserPanel::start, this, &Lamps::start);
	connect(&experiment, &Experiment::experimentStopped, this, &Lamps::save);

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

	menuBar()->hide();
}

void Lamps::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier + Qt::ShiftModifier) {
		if (event->key() == Qt::Key_S)
			experiment.stop();
		else if (event->key() == Qt::Key_D)
			experiment.start();
		else if (event->key() == Qt::Key_Q)
			close();
	}
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

	userPanel.clear();
	stackedWidget->setCurrentIndex(1);

	experimentStartTime = QTime::currentTime();

	experiment.setPractise(true);
}

void Lamps::start()
{
	qDebug() << userPanel.nick();
	stackedWidget->setCurrentIndex(2);
}

void Lamps::quit()
{
	close();
}

void Lamps::save()
{
	if (experiment.isPractise()) {
		experiment.clearConfigurations();
		experiment.setConfigurations();
		experiment.resetStats();
		experiment.setPractise(false);
		return;
	} else {
		qDebug() << "saving statistics";
	}

	QVector<QVector<QVariant> > info;
	info.append({"pseudonim", userPanel.nick()});
	info.append({"data", QDate::currentDate().toString("d.M.yy")});
	info.append({"\"czas rozpoczecia\"", experimentStartTime.toString("hh:mm:ss")});
	info.append({"\"czas zatrzymania\"", QTime::currentTime().toString("hh:mm:ss")});
	info.append({"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"});

	CSVWriter::saveVectors(userPanel.nick() + "." + QDate::currentDate().toString("d.M.yy")
		+ ".csv", info + experiment.getStatsList());
}
