#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget* parent)
	: QGroupBox("Panel eksperymentatora", parent)
{
	QVBoxLayout *layout = new QVBoxLayout();


	QHBoxLayout *layoutMaxExperimentTime = new QHBoxLayout();

	QSpacerItem *spacerMaxExperimentTime = new QSpacerItem(30, 10);
	QLabel *labelMaxExperimentTime = new QLabel("Maksymalny czas eksperymentu (s)");
	spinBoxMaxExperimentTime = new QSpinBox();
	spinBoxMaxExperimentTime->setFixedWidth(140);
	spinBoxMaxExperimentTime->setMinimum(10);
	spinBoxMaxExperimentTime->setMaximum(3600 * 24);

	layoutMaxExperimentTime->addWidget(spinBoxMaxExperimentTime);
	layoutMaxExperimentTime->addItem(spacerMaxExperimentTime);
	layoutMaxExperimentTime->addWidget(labelMaxExperimentTime);

	layout->addItem(layoutMaxExperimentTime);


	checkBoxWithFeedback = new QCheckBox("Ze sprzężeniem zwrotnym", this);
	checkBoxWithTimer    = new QCheckBox("Z odliczaniem czasu", this);

	layout->addWidget(checkBoxWithFeedback);
	layout->addWidget(checkBoxWithTimer);


	QHBoxLayout *layoutTimeout = new QHBoxLayout();

	spinBoxTimeout = new QSpinBox(this);
	spinBoxTimeout->setFixedWidth(140);
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
	QSpacerItem *spacerLoad = new QSpacerItem(30, 30);
	buttonLoadLast = new QPushButton("Wczytaj sesję");
	labelSessionFileName = new QLabel("");

	buttonConfirm->setFixedWidth(100);
	buttonQuit->setFixedWidth(100);
	buttonLoadLast->setFixedWidth(170);

	connect(buttonConfirm, &QPushButton::clicked, this, &ControlPanel::start);
	connect(buttonQuit, &QPushButton::clicked, this, &ControlPanel::quit);
	connect(buttonLoadLast, &QPushButton::clicked, this, &ControlPanel::loadSession);

	layout->addItem(spacerButtons);
	layout->addWidget(labelSessionFileName);
	layout->addWidget(buttonLoadLast);
	layout->addItem(spacerLoad);
	layout->addWidget(buttonConfirm);
	layout->addWidget(buttonQuit);

	layout->setAlignment(Qt::AlignTop);

	setLayout(layout);
}

ControlPanel::~ControlPanel()
{}

int ControlPanel::maxExperimentTime() const
{
	return spinBoxMaxExperimentTime->value();
}

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

QString ControlPanel::filePath() const
{
	return sessionFilePath;
}

void ControlPanel::setMaxExperimentTime(int time)
{
	spinBoxMaxExperimentTime->setValue(time);
}

void ControlPanel::setWithFeedback(bool feedback)
{
	checkBoxWithFeedback->setChecked(feedback);
}

void ControlPanel::setWithTimer(bool timer)
{
	checkBoxWithTimer->setChecked(timer);
}

void ControlPanel::setTimeout(int timeout)
{
	spinBoxTimeout->setValue(timeout);
}

void ControlPanel::loadSession()
{
	sessionFilePath = QFileDialog::getOpenFileName(this, "Open session", "", tr("Excel files (*.csv)"));
	labelSessionFileName->setText(sessionFilePath);
	qDebug() << sessionFilePath;
}
