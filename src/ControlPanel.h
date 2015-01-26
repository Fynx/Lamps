#pragma once

#include <QtWidgets>

class ControlPanel : public QGroupBox {
Q_OBJECT;
public:
	ControlPanel(QWidget *parent);
	~ControlPanel();

	int maxExperimentTime() const;
	bool withFeedback() const;
	bool withTimer() const;
	bool isRandom() const;
	qreal checkProbability() const;
	int timeout() const;
	QString filePath() const;

signals:
	void start();
	void quit();

private:
	void loadSession();

	QSpinBox *spinBoxMaxExperimentTime;
	QCheckBox *checkBoxWithFeedback;
	QCheckBox *checkBoxWithTimer;
	QSpinBox *spinBoxTimeout;
	QPushButton *buttonConfirm;
	QPushButton *buttonQuit;
	QPushButton *buttonLoadLast;
	QLabel *labelSessionFileName;
	QString sessionFilePath;
};