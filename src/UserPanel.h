#pragma once

#include <QtWidgets>

class UserPanel : public QGroupBox {
Q_OBJECT;
public:
	UserPanel(QWidget *parent);

	void clear();

	QString nick() const;
	void setNick(const QString &nick);

signals:
	void start();

private:
	void started();

	QLineEdit *lineEditNick;
	QLabel *labelNickWarning;
	QPushButton *buttonStart;
};