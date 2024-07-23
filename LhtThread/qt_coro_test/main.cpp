#include "dlgct.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DlgCT w;
	w.show();
	return a.exec();
}
