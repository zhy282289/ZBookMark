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

	return path;
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
	return appPath;
}
