#include "Lamps.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QFont newFont("Courier [Adobe]", 14, QFont::Normal, true);
	app.setFont(newFont);

	Lamps lamps;
	lamps.show();
	return app.exec();
}
