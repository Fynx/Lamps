#include "Lamps.h"

Lamps::Lamps()
{
	setCentralWidget(&experiment);
	showFullScreen();

	QMenu *menuFile = menuBar()->addMenu("File");

	QAction *actionQuit = new QAction("Quit", this);
	actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
	connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	menuBar()->show();
}