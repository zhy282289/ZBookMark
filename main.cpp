#include "stdafx.h"
#include "zbookmark.h"
#include <QtGui/QApplication>
#include <QTextCodec>
bool InitEnviroment();
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));

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