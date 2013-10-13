#ifndef ZAPI_H_H
#define ZAPI_H_H







void RegisterAllMetaType();



QString GetAppPath();
QString GetCurrentFileDir();
QString GetNewFilePath();
QString GetTreeItemDataConfigPath();

bool YesNoBox(QWidget *parent , const QString caption, const QString &text);





#endif
