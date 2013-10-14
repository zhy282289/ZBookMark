#include "stdafx.h"
#include "zbookmark.h"
#include <QtGui/QApplication>
#include <QTextCodec>

Q_IMPORT_PLUGIN(qcncodecs);

bool InitEnviroment();
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
	QTranslator qtTranslator;          
	qtTranslator.load( QObject::tr(":/ZBookMark/Resources/cn.qm") ); 
	a.installTranslator(&qtTranslator); 

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