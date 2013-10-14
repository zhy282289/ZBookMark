#ifndef ZDEF_H_H
#define ZDEF_H_H




enum ZTreeItemType{ DirectoryType, FileType, };



class ZTreeItemData;
class ZItemData
{
public:
	QString			title;
	int				type;
	QString			path;
	bool			expand;
	QDateTime		time;

	ZItemData();
	ZItemData(const ZTreeItemData &itemData);
	ZItemData(const ZItemData &itemData);
	bool operator == (const ZItemData &other);
	friend QDataStream& operator >> (QDataStream &in, ZItemData &data);
	friend QDataStream& operator << (QDataStream &out, const ZItemData &data);
};
Q_DECLARE_METATYPE(ZItemData)


class ZTreeItemData : public ZItemData
{
public:
	QVector<ZTreeItemData>	items;

	ZTreeItemData();
	ZTreeItemData(const ZItemData &itemData);
	ZTreeItemData(const ZTreeItemData &itemData);
	//ZTreeItemData& operator = (const ZTreeItemData &other);

	friend QDataStream& operator >> (QDataStream &in, ZTreeItemData &data);
	friend QDataStream& operator << (QDataStream &out, const ZTreeItemData &data);
};

Q_DECLARE_METATYPE(ZTreeItemData)








#ifdef Q_OS_WIN32
#define PATH_SEPERATOR "\\"
#else
	#define PATH_SEPERATOR "/"
#endif





// messgae
#define ZBOOKMARK		QEvent::User + 1

#define ZTREEWIDGET_PRESS	ZBOOKMARK + 1





#define ZBOOKMARKMAINWINDOW		ZBOOKMARK + 1000
#define ZBOOKMARKMAINWINDOW_MENU_SAVE ZBOOKMARKMAINWINDOW + 1

#endif