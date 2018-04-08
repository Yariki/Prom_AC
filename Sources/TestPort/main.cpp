#include "testport.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestPort w;
	w.show();
	return a.exec();
}
