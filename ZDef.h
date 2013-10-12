#ifndef ZDEF_H_H
#define ZDEF_H_H




enum ZTreeItemType{ DirectoryType, FileType, };





class ZTreeItemData
{
public:
	QString			title;
	int				type;
	QString			path;
	QDateTime		time;
	QVector<ZTreeItemData>	items;

	ZTreeItemData()
	{

	}

	friend QDataStream& operator >> (QDataStream &in, ZTreeItemData &data);
	friend QDataStream& operator << (QDataStream &out, const ZTreeItemData &data);
};

Q_DECLARE_METATYPE(ZTreeItemData)


class ZItemData
{
public:
	QString			title;
	int				type;
	QString			path;
	QDateTime		time;
	ZItemData(){}
	ZItemData(const ZTreeItemData &itemData)
	{
		title = itemData.title;
		type = itemData.type;
		path = itemData.path;
		time = itemData.time;
	}
	friend QDataStream& operator >> (QDataStream &in, ZItemData &data);
	friend QDataStream& operator << (QDataStream &out, const ZItemData &data);
};
Q_DECLARE_METATYPE(ZItemData)






#ifdef Q_OS_WIN32
#define PATH_SEPERATOR "\\"
#else
	#define PATH_SEPERATOR "/"
#endif





// messgae
#define ZBOOKMARK		QEvent::User + 1

#define ZTREEWIDGET_PRESS	ZBOOKMARK + 1







#endif