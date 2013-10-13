
#include "stdafx.h"
#include "ZDef.h"



 QDataStream& operator >> (QDataStream &in, ZTreeItemData &data)
{
	in >> data.title >> data.type >> data.path >> data.time  >> data.expand;
	in >> data.items;
	return in;
}

QDataStream& operator << (QDataStream &out, const ZTreeItemData &data)
{
	out << data.title << data.type << data.path << data.time  << data.expand;
	out << data.items;
	return out;
}


QDataStream& operator >> (QDataStream &in, ZItemData &data)
{
	return in >> data.title >> data.type >> data.path >> data.time  >> data.expand;
}
QDataStream& operator << (QDataStream &out, const ZItemData &data)
{
	return out << data.title << data.type << data.path << data.time  << data.expand;
}



ZTreeItemData::ZTreeItemData( const ZItemData &itemData )
{
	title = itemData.title;
	type = itemData.type;
	path = itemData.path;
	time = itemData.time;
	expand = itemData.expand;
}

ZTreeItemData::ZTreeItemData()
	:ZItemData()
{

}

ZTreeItemData::ZTreeItemData( const ZTreeItemData &itemData )
{
	title = itemData.title;
	type = itemData.type;
	path = itemData.path;
	time = itemData.time;
	expand = itemData.expand;
	items = itemData.items;
}


ZItemData::ZItemData( const ZTreeItemData &itemData )
{
	
	title = itemData.title;
	type = itemData.type;
	path = itemData.path;
	time = itemData.time;
	
}

ZItemData::ZItemData()
{
	type = FileType;
	expand = false;
}

bool ZItemData::operator == (const ZItemData &other)
{
	return path == other.path;
}