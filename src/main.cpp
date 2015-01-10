#include "Lamps.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	Lamps lamps;
	lamps.show();
	return app.exec();
}
