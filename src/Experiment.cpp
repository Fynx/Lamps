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
		Lamp *lamp = new Lamp();
		lamp->setPos(position);
		position.rx() += diff;
		lamps[key] = lamp;
		connect(lamp, &Lamp::expired, this, &Experiment::onLampExpired);
		scene->addItem(lamp);
	}

	resetStats();

	setScene(scene);

	connect(&timer, &QTimer::timeout, this, &Experiment::timeout);
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

void Experiment::timeout()
{
	static int init = false;
	if (!init) {
		init = true;
		qsrand(QTime::currentTime().msec());
	}

	timeElapsed += period;
	if (timeElapsed >= totalTime && withTimer) {
		stop();
		emit experimentEnded();
	}

	if (!withTimer) {
		for (Lamp *lamp : lamps)
			if (lamp->isOn())
				return;
		setNewConfiguration();
	} else {
		setNewConfiguration();
	}
}

void Experiment::onLampExpired()
{
	++skippedChecks;
}

void Experiment::start()
{
	qDebug() << "Start.";
	timer.start(period);
	started = true;
	for (Lamp *lamp : lamps)
		lamp->setVisible(true);
}

void Experiment::stop()
{
	timer.stop();
	started = false;
	saveConfiguration();
	for (Lamp *lamp : lamps)
		lamp->setVisible(false);

	qDebug() << getStats();
}

void Experiment::trigger(Qt::Key key)
{
	if (!started || !lamps.contains(key))
		return;
	if (lamps[key]->isOn()) {
		++correctChecks;
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

void Experiment::resetStats()
{
	correctChecks   = 0;
	incorrectChecks = 0;
	skippedChecks   = 0;
	timeElapsed     = 0;
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
