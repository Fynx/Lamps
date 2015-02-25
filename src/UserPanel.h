#pragma once

#include <QtWidgets>

class UserPanel : public QGroupBox {
Q_OBJECT;
public:
	UserPanel(QWidget *parent);

	void clear();

	QString nick() const;
	void setNick(const QString &nick);
	QString gender() const;
	int age() const;

signals:
	void start();

private:
	void started();

	QLineEdit *lineEditNick;
	QLabel *labelNickWarning;
	QGroupBox *groupBoxGender;
	QRadioButton *buttonFemale;
	QRadioButton *buttonMale;
	QSpinBox *boxAge;
	QPushButton *buttonStart;
};