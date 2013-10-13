#include "StdAfx.h"
#include "ZApi.h"




void RegisterAllMetaType()
{
	qRegisterMetaTypeStreamOperators<ZTreeItemData>("ZTreeItemData");
	qRegisterMetaTypeStreamOperators<ZItemData>("ZItemData");
}

QString GetCurrentFileDir()
{
	QString path = GetAppPath() + "data" + PATH_SEPERATOR + QDateTime::currentDateTime().toString("yyyy-MM") + PATH_SEPERATOR;
	QDir dir(path);
	if (!dir.exists())
	{
		dir.mkpath(path);
	}
	return path;
}


QString GetNewFilePath()
{
	return GetCurrentFileDir() + QDateTime::currentDateTime().toString("dd hh-mm-ss") + ".html";
}


QString GetAppPath()
{
	QString appPath;
#ifdef _WIN32
	appPath = QApplication::applicationDirPath() + "\\";
#else
	appPath = QApplication::applicationDirPath();
	int index = appPath.lastIndexOf(PATH_SEPERATOR);
	appPath = appPath.left(index);
	appPath += "/Frameworks/"; 
#endif
	return QDir::toNativeSeparators(appPath);
}

QString GetTreeItemDataConfigPath()
{
	QString filePath = GetAppPath() + "ZBookMarkTree";
	return filePath;
}

bool YesNoBox( QWidget *parent , const QString caption, const QString &text )
{
	QMessageBox box(parent);
	box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	box.setWindowTitle(caption);
	box.setText(text);
	return (box.exec() == QMessageBox::Yes) ? true : false;
}
