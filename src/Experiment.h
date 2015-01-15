#pragma once

#include <QtWidgets>
#include "Lamp.h"

class Experiment : public QGraphicsView {
Q_OBJECT;
public:
	Experiment();
	~Experiment();

	typedef QBitArray Configuration;

	void setRandom(bool random);
	void setCheckProbability(qreal prob);
	void setConfigurations(const QSet<Configuration> &cs);
	void setTimeout(int time);
	void setExperimentTime(int time);

	void start();
	void stop();
	void trigger(Qt::Key key);

	void clearConfigurations();

	void resetStats();
	QHash<QString, int> getStats();

signals:
	void experimentEnded();

private:
	void saveConfiguration();
	void timeout();
	void onLampExpired();

	QHash<int, Lamp *> lamps;
	QSet<Configuration> configurations;

	int totalTime;
	bool randomConfigurations;
	qreal checkProbability;

	QTimer timer;
	int period;
	bool started;

	/** Stats */
	int correctChecks;
	int incorrectChecks;
	int skippedChecks;
	int timeElapsed;
};