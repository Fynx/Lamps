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
	void setConfigurations(const QSet<Configuration> &cs = {});
	void setTimeout(int time);
	void setExperimentTime(int time);
	void setWithFeedback(bool yes);
	void setWithTimer(bool yes);

	void start();
	void stop();
	void trigger(Qt::Key key);

	void clearConfigurations();

	void resetStats();
	QHash<QString, int> getStats();
	QVector<QVector<QVariant> > getStatsList() const;

signals:
	void experimentEnded();
	void experimentStopped();

private:
	static QSet<Configuration> generateAllConfigurations();
	void setNewConfiguration();
	void saveConfiguration();
	void timeout();
	void onLampExpired();

	QHash<int, Lamp *> lamps;
	QVector<int> currentChecksTimeouts;
	QSet<Configuration> configurations;
	Configuration currentConfiguration;

	bool feedback;
	bool withTimer;

	int totalTime;
	bool randomConfigurations;
	qreal checkProbability;

	int timestamp;
	QElapsedTimer elapsedTimer;
	QTimer timer;
	int period;
	bool started;

	/** Stats */
	int correctChecks;
	int incorrectChecks;
	int skippedChecks;
	int timeElapsed;
	QVector<QPair<Configuration, QVector<int> > > usedConfigurations;
};
