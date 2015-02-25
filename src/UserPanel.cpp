#include "UserPanel.h"

UserPanel::UserPanel(QWidget *parent)
	: QGroupBox("Panel użytkownika", parent)
{
	QVBoxLayout *layout = new QVBoxLayout();


	QSpacerItem *spacerNickWarning = new QSpacerItem(10, 10);
	labelNickWarning = new QLabel("Wypełnienie tego pola jest konieczne do realizacji eksperymentu");

	layout->addWidget(labelNickWarning);
	layout->addItem(spacerNickWarning);


	QHBoxLayout *layoutNick = new QHBoxLayout();
	layoutNick->setAlignment(Qt::AlignLeft);
	lineEditNick = new QLineEdit();
	lineEditNick->setFixedWidth(150);
	QLabel *labelNick = new QLabel("Pseudonim");

	QSpacerItem *spacerNick = new QSpacerItem(30, 10);

	layoutNick->addWidget(lineEditNick);
	layoutNick->addItem(spacerNick);
	layoutNick->addWidget(labelNick);

	layout->addItem(layoutNick);


	QSpacerItem *genderSpacer = new QSpacerItem(30, 30);

	groupBoxGender = new QGroupBox("Płeć");

	groupBoxGender->setFixedWidth(300);

	buttonFemale = new QRadioButton("kobieta");
	buttonMale = new QRadioButton("mężczyzna");

	buttonFemale->setChecked(true);

	QVBoxLayout *genderLayout = new QVBoxLayout();
	genderLayout->addWidget(buttonFemale);
	genderLayout->addWidget(buttonMale);

	groupBoxGender->setLayout(genderLayout);

	layout->addItem(genderSpacer);
	layout->addWidget(groupBoxGender);


	QSpacerItem *spacerAge = new QSpacerItem(30, 30);
	QLabel *labelAge = new QLabel("Wiek");

	boxAge = new QSpinBox();

	boxAge->setFixedWidth(80);
	boxAge->setMinimum(4);
	boxAge->setMaximum(200);
	boxAge->setValue(20);

	layout->addItem(spacerAge);
	layout->addWidget(labelAge);
	layout->addWidget(boxAge);


	QSpacerItem *spacerButton = new QSpacerItem(30, 30);
	layout->addItem(spacerButton);

	buttonStart = new QPushButton("Start!");
	buttonStart->setFixedWidth(100);
	connect(buttonStart, &QPushButton::clicked, this, &UserPanel::started);
	layout->addWidget(buttonStart);


	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);
}

void UserPanel::clear()
{
	lineEditNick->clear();
	labelNickWarning->setVisible(false);
}

QString UserPanel::nick() const
{
	return lineEditNick->text();
}

void UserPanel::setNick(const QString &nick)
{
	lineEditNick->setText(nick);
}

QString UserPanel::gender() const
{
	if (buttonMale->isChecked())
		return "mezczyzna";
	else
		return "kobieta";
}

int UserPanel::age() const
{
	return boxAge->value();
}

void UserPanel::started()
{
	if (!nick().isEmpty())
		emit start();
	else
		labelNickWarning->setVisible(true);
}
