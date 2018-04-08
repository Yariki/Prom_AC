#include "stdafx.h"
#include "runtime.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Runtime w;
	w.show();
	return a.exec();
}
