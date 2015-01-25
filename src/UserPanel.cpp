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

void UserPanel::started()
{
	if (!nick().isEmpty())
		emit start();
	else
		labelNickWarning->setVisible(true);
}
