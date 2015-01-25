#pragma once

#include <QtWidgets>

class UserPanel : public QGroupBox {
Q_OBJECT;
public:
	UserPanel(QWidget *parent);

	void clear();

	QString nick() const;

signals:
	void start();

private:
	void started();

	QLineEdit *lineEditNick;
	QLabel *labelNickWarning;
	QPushButton *buttonStart;
};