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

static const QMap<Qt::Key, QString> keyToString {
	{Qt::Key_Q, "Q"},
	{Qt::Key_W, "W"},
	{Qt::Key_E, "E"},
	{Qt::Key_R, "R"},
	{Qt::Key_T, "T"},
	{Qt::Key_Y, "Y"},
	{Qt::Key_U, "U"},
	{Qt::Key_I, "I"},
	{Qt::Key_O, "O"},
	{Qt::Key_P, "P"},
};

Experiment::Experiment()
	: QGraphicsView(),
	  feedback(false),
	  totalTime(0),
	  randomConfigurations(false),
	  checkProbability(0),
	  started(false)
{
	QGraphicsScene *scene = new QGraphicsScene();

	QPointF position(100.0, 200.0);
	qreal diff = 130.0;

	for (Qt::Key key : keys) {
		Lamp *lamp = new Lamp(keyToString[key]);
		lamp->setPos(position);
		position.rx() += diff;
		lamps[key] = lamp;
		connect(lamp, &Lamp::expired, this, &Experiment::onLampExpired);
		scene->addItem(lamp);
	}

	textMainSessionName = new QGraphicsTextItem("Sesja główna");
	textTrialSessionName = new QGraphicsTextItem("Sesja próbna");
	textStartSession = new QGraphicsTextItem("Aby zacząć sesję, wciśnij Ctrl+Shift+D");
	textStopSession = new QGraphicsTextItem("Aby zatrzymać sesję, wciśnij Ctrl+Shift+S");
	textResumeSession = new QGraphicsTextItem("Aby ponowić sesję wciśnij Ctrl+Shift+D");
	textTrialSession = new QGraphicsTextItem("Aby zakończyć sesję próbną, wciśnij Ctrl+Shift+S");
	textExperimentEnded = new QGraphicsTextItem("Eksperyment zakończony! Naciśnij Ctrl+Shift+Q aby wyjść z programu.");

	textMainSessionName->setPos(600, -200);
	textTrialSessionName->setPos(600, -200);
	textStartSession->setPos(100, -200);
	textStopSession->setPos(100, -160);
	textTrialSession->setPos(100, -160);
	textResumeSession->setPos(100, -160);
	textExperimentEnded->setPos(600, -100);

	textMainSessionName->setDefaultTextColor(Qt::white);
	textTrialSessionName->setDefaultTextColor(Qt::white);
	textStartSession->setDefaultTextColor(Qt::white);
	textStopSession->setDefaultTextColor(Qt::white);
	textTrialSession->setDefaultTextColor(Qt::white);
	textResumeSession->setDefaultTextColor(Qt::white);
	textExperimentEnded->setDefaultTextColor(Qt::white);

	resetStats();

	scene->addItem(textMainSessionName);
	scene->addItem(textTrialSessionName);
	scene->addItem(textStartSession);
	scene->addItem(textStopSession);
	scene->addItem(textTrialSession);
	scene->addItem(textResumeSession);
	scene->addItem(textExperimentEnded);

	setScene(scene);

	elapsedTimer.start();
	connect(&timer, &QTimer::timeout, this, &Experiment::timeout);

	updateText();
}

Experiment::~Experiment()
{
	qDeleteAll(lamps);
}

void Experiment::setRandom(bool random)
{
	randomConfigurations = random;
}

void Experiment::setCheckProbability(qreal prob)
{
	checkProbability = prob;
}

void Experiment::setConfigurations(const QSet<Experiment::Configuration> &cs)
{
	if (cs.isEmpty())
		configurations = generateAllConfigurations();
	else
		configurations = cs;
}

void Experiment::setTimeout(int time)
{
	period = time;
	for (Lamp *lamp : lamps)
		lamp->setTimeout(time * (int) withTimer);
}

void Experiment::setExperimentTime(int time)
{
	totalTime = time;
}

void Experiment::setWithFeedback(bool yes)
{
	feedback = yes;
}

void Experiment::setWithTimer(bool yes)
{
	withTimer = yes;
	for (Lamp *lamp : lamps)
		lamp->setTimeout(period * (int) withTimer);
}

void Experiment::setPractise(bool yes)
{
	practise = yes;
	updateText();
}

bool Experiment::isPractise() const
{
	return practise;
}

void Experiment::timeout()
{
	static int init = false;
	if (!init) {
		init = true;
		qsrand(QTime::currentTime().msec());
	}

	drawRectangle(Qt::green);

	if (configurations.isEmpty())
		setConfigurations();

	timeElapsed += period;
	if ((timeElapsed >= totalTime && totalTime != 0) || (configurations.isEmpty() && !randomConfigurations)) {
		stop();
		emit experimentEnded();
	}

	if (!withTimer) {
		for (Lamp *lamp : lamps)
			if (lamp->isOn())
				return;
	}
	if (!currentConfiguration.isNull())
		usedConfigurations.append({currentConfiguration, currentChecksTimeouts});
	timestamp = elapsedTimer.elapsed();
	currentChecksTimeouts = QVector<int>(10);
	for (int &a : currentChecksTimeouts)
		a = 0;
	setNewConfiguration();
}

void Experiment::onLampExpired()
{
	++skippedChecks;
}

void Experiment::updateText()
{
	if (practise) {
		textTrialSessionName->setVisible(true);
		textMainSessionName->setVisible(false);
	} else {
		textTrialSessionName->setVisible(false);
		textMainSessionName->setVisible(true);
	}

	if (started) {
		if (!practise) {
			textStopSession->setVisible(true);
			textTrialSession->setVisible(false);
		} else {
			textStopSession->setVisible(false);
			textTrialSession->setVisible(true);
		}
		textStartSession->setVisible(false);
	} else {
		textStartSession->setVisible(true);
		textStopSession->setVisible(false);
		textTrialSession->setVisible(false);
	}

	textResumeSession->setVisible(false);

	textExperimentEnded->setVisible(false);

	scene()->update();
}

void Experiment::drawRectangle(QColor color)
{
	QPen rectPen;
	QBrush rectBrush(color);
	rectPen.setColor(color);
// 	scene()->addRect(QRectF(50, 330, 1250, 50), rectPen, rectBrush);
// 	scene()->setSceneRect(QRectF(-1366/2, -768/2, 1366, 768));
}

void Experiment::start()
{
	timer.start(period);
	started = true;
	updateText();
	for (Lamp *lamp : lamps)
		lamp->setVisible(true);
}

void Experiment::stop()
{
	timer.stop();
	started = false;
	drawRectangle(Qt::black);
	updateText();
	saveConfiguration();
	for (Lamp *lamp : lamps)
		lamp->setVisible(false);
	emit experimentStopped();
}

void Experiment::trigger(Qt::Key key)
{
	if (!started || !lamps.contains(key))
		return;
	if (lamps[key]->isOn()) {
		++correctChecks;
		currentChecksTimeouts[keys.indexOf(key)] = elapsedTimer.elapsed() - timestamp;
		lamps[key]->turnOff();
	} else {
		++incorrectChecks;
		if (feedback)
			qDebug() << "\a";
	}
}

void Experiment::clearConfigurations()
{
	configurations.clear();
}

void Experiment::removeConfigurations(const QSet<Experiment::Configuration> &cs)
{
	configurations -= cs;
}

void Experiment::resetStats()
{
	correctChecks   = 0;
	incorrectChecks = 0;
	skippedChecks   = 0;
	timeElapsed     = 0;

	usedConfigurations.clear();
}

QHash<QString, int> Experiment::getStats()
{
	QHash<QString, int> sts;
	sts["correctChecks"]   = correctChecks;
	sts["incorrectChecks"] = incorrectChecks;
	sts["skippedChecks"]   = skippedChecks;
	sts["timeElapsed"]     = timeElapsed;

	return sts;
}

QVector<QVector<QVariant> > Experiment::getStatsList() const
{
	QVector<QVector<QVariant> > result;
	result.append({"\"Poprawne klikniecia\"", correctChecks});
	result.append({"\"Niepoprawne klikniecia\"", incorrectChecks});
	result.append({"\"Ominiete klikniecia\"", skippedChecks});
	result.append({"\"Czas (ms)\"", timeElapsed});

	result.append({"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"});

	for (auto &x : usedConfigurations) {
		QVector<QVariant> vec;
		for (const int &a : x.second)
			vec.append(a);
		result.append(vec);
	}
	return result;
}

QSet<Experiment::Configuration> Experiment::generateAllConfigurations()
{
	QSet<Configuration> set;
	for (int i = 0; i < (1 << 10); ++i) {
		Configuration c(10);
		for (int j = 0; j < 10; ++j)
			c[j] = (i & (1 << j));
		set.insert(c);
	}
	return set;
}

void Experiment::setNewConfiguration()
{
	if (randomConfigurations) {
		for (Lamp *lamp : lamps) {
			qreal randomNumber = (qreal) (qrand() % 1000);
			static const qreal maxNumber = (qreal) (999);
			if (randomNumber / maxNumber <= checkProbability)
				lamp->turnOn();
		}
	} else {
		int k = qrand() % configurations.size();
		auto it = configurations.begin();
		for (int i = 0; i < k; ++i)
			++it;
		currentConfiguration = *it;
		int i = 0;
		for (Lamp *lamp : lamps) {
			if (currentConfiguration[i])
				lamp->turnOn();
			++i;
		}
		configurations.erase(it);
	}
}

void Experiment::saveConfiguration()
{
	QBitArray res;
	res.resize(lamps.size());
	int i = 0;
	for (Lamp *lamp : lamps)
		res[i++] = lamp->isOn();

	configurations.insert(res);
}
