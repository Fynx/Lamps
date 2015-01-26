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

void Lamps::setSettings()
{
	experiment.setWithFeedback(controlPanel.withFeedback());
	experiment.setWithTimer(controlPanel.withTimer());
	experiment.setTimeout(controlPanel.timeout());
	experiment.setRandom(controlPanel.isRandom());
	experiment.setCheckProbability(controlPanel.checkProbability());
	experiment.setExperimentTime(controlPanel.maxExperimentTime());
}

void Lamps::settingsSet()
{
	setSettings();
	experiment.setConfigurations();

	if (!controlPanel.filePath().isEmpty() && load()) {
		stackedWidget->setCurrentIndex(2);
		experiment.setPractise(false);
	} else {
		sessionNumber = 1;
		stackedWidget->setCurrentIndex(1);
		experiment.setPractise(true);
	}

	experimentStartTime = QTime::currentTime();
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
	info.append({"\"numer sesji\"", sessionNumber});
	info.append({"\"czas rozpoczecia\"", experimentStartTime.toString("hh:mm:ss")});
	info.append({"\"czas zatrzymania\"", QTime::currentTime().toString("hh:mm:ss")});

	info.append({"\"max czas eksperymentu\"", controlPanel.maxExperimentTime()});
	info.append({"\"sprzezenie zwrotne\"", (int) controlPanel.withFeedback()});
	info.append({"\"z czasem\"", (int) controlPanel.withTimer()});
	info.append({"\"timeout\"", controlPanel.timeout()});

	QString filePath = controlPanel.filePath();
	if (filePath.isEmpty())
		filePath = userPanel.nick() + "." + QDate::currentDate().toString("d.M.yy") + ".csv";

	CSVWriter::saveVectors(filePath, info + experiment.getStatsList());

	experiment.resetStats();
}

bool Lamps::load()
{
	QFile file(controlPanel.filePath());

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Unable to open file!";
		return false;
	}

	qDebug() << "loading" << controlPanel.filePath();

	QSet<Experiment::Configuration> configurations;

	while (!file.atEnd()) {
		QByteArray data = file.readLine();
		QStringList list = QString(data).split(",");
		if (list[0] == "\"numer sesji\"") {
			if (sessionNumber == list[1].toInt())
				configurations.clear();
			sessionNumber = list[1].toInt() + 1;
		} else if (list[0] == "pseudonim") {
			userPanel.setNick(list[1].left(list[1].size() - 1));
		} else if (list[0] == "\"max czas eksperymentu\"") {
			controlPanel.setMaxExperimentTime(list[1].toInt());
		} else if (list[0] == "\"sprzezenie zwrotne\"") {
			controlPanel.setWithFeedback((bool) list[1].toInt());
		} else if (list[0] == "\"z czasem\"") {
			controlPanel.setWithTimer((bool) list[1].toInt());
		} else if (list[0] == "\"timeout\"") {
			controlPanel.setTimeout(list[1].toInt());
		} else if (list.size() == 10) {
			Experiment::Configuration c(10);
			int i = 0;
			for (const QString &l : list)
				c[i++] = (l.toInt() != 0);
			configurations.insert(c);
		}
	}

	experiment.setConfigurations();
	experiment.removeConfigurations(configurations);

	setSettings();

	qDebug() << "done!";

	return true;
}
