#include "stdafx.h"
#include "zbookmark.h"
#include <QtGui/QApplication>

bool InitEnviroment();
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (!InitEnviroment())
	{
		return 0;
	}


	ZBookMark w;
	w.showMaximized();



	return a.exec();
}


bool InitEnviroment()
{
	RegisterAllMetaType();

	return true;
}