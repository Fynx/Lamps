#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget* parent)
	: QGroupBox("Panel eksperymentatora", parent)
{
	QVBoxLayout *layout = new QVBoxLayout();


	checkBoxWithFeedback = new QCheckBox("Ze sprzężeniem zwrotnym", this);
	checkBoxWithTimer    = new QCheckBox("Z odliczaniem czasu", this);

	layout->addWidget(checkBoxWithFeedback);
	layout->addWidget(checkBoxWithTimer);


	QHBoxLayout *layoutTimeout = new QHBoxLayout();

	spinBoxTimeout = new QSpinBox(this);
	spinBoxTimeout->setFixedWidth(100);
	spinBoxTimeout->setMinimum(20);
	spinBoxTimeout->setMaximum(9999);
	spinBoxTimeout->setValue(50);
	QLabel *labelTimeout = new QLabel("Czas palenia się lampki (ms)");
	labelTimeout->setBuddy(spinBoxTimeout);

	QSpacerItem *spacerTimeout = new QSpacerItem(30, 10);

	layoutTimeout->addWidget(spinBoxTimeout);
	layoutTimeout->addItem(spacerTimeout);
	layoutTimeout->addWidget(labelTimeout);

	layout->addItem(layoutTimeout);


	QSpacerItem *spacerButtons = new QSpacerItem(30, 30);
	buttonConfirm = new QPushButton("Start");
	buttonQuit = new QPushButton("Wyjdź");

	buttonConfirm->setFixedWidth(70);
	buttonQuit->setFixedWidth(70);

	connect(buttonConfirm, &QPushButton::clicked, this, &ControlPanel::start);
	connect(buttonQuit, &QPushButton::clicked, this, &ControlPanel::quit);

	layout->addItem(spacerButtons);
	layout->addWidget(buttonConfirm);
	layout->addWidget(buttonQuit);

	layout->setAlignment(Qt::AlignTop);

	setLayout(layout);
}

ControlPanel::~ControlPanel()
{}

bool ControlPanel::withFeedback() const
{
	return checkBoxWithFeedback->isChecked();
}

bool ControlPanel::withTimer() const
{
	return checkBoxWithTimer->isChecked();
}

bool ControlPanel::isRandom() const
{
	return false;
}

qreal ControlPanel::checkProbability() const
{
	return 0.3;
}

int ControlPanel::timeout() const
{
	return spinBoxTimeout->value();
}

int ControlPanel::experimentTime() const
{
	return 0;
}
