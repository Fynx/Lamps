#pragma once

#include <QtWidgets>

class ControlPanel : public QGroupBox {
Q_OBJECT;
public:
	ControlPanel(QWidget *parent);
	~ControlPanel();

	bool withFeedback() const;
	bool withTimer() const;
	bool isRandom() const;
	qreal checkProbability() const;
	int timeout() const;
	int experimentTime() const;

signals:
	void start();
	void quit();

private:
	QCheckBox *checkBoxWithFeedback;
	QCheckBox *checkBoxWithTimer;
	QSpinBox *spinBoxTimeout;
	QPushButton *buttonConfirm;
	QPushButton *buttonQuit;
};