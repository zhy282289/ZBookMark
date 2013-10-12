
#include "stdafx.h"
#include "ZDef.h"



 QDataStream& operator >> (QDataStream &in, ZTreeItemData &data)
{
	in >> data.title >> data.type >> data.path >> data.time;
	in >> data.items;
	return in;
}

QDataStream& operator << (QDataStream &out, const ZTreeItemData &data)
{
	out << data.title << data.type << data.path << data.time;
	out << data.items;
	return out;
}


QDataStream& operator >> (QDataStream &in, ZItemData &data)
{
	return in >> data.title >> data.type >> data.path >> data.time;
}
QDataStream& operator << (QDataStream &out, const ZItemData &data)
{
	return out << data.title << data.type << data.path << data.time;
}


