#include "stdafx.h"
#include "ZUi.h"


enum TreeRole{ItemData = Qt::UserRole, };

ZDockWidget::ZDockWidget( QWidget *parent /*= 0*/ )
	:QDockWidget(parent)
{
	
}

ZDockWidget::~ZDockWidget()
{

}

ZTreeWidget::ZTreeWidget( QWidget *parent /*= 0*/ )
	:QTreeWidget(parent)
{

	this->setAnimated(true);
	this->setDragDropMode(QAbstractItemView::InternalMove);

	ZItemData itemData;
	itemData.title = "Root";
	itemData.type = DirectoryType;
	m_root = new QTreeWidgetItem(this, QStringList() <<itemData.title);
	m_root->setData(0, ItemData, QVariant::fromValue(itemData));

	m_floderIcon = ":/ZBookMark/Resources/floder.png";
	m_fileIcon = ":/ZBookMark/Resources/file.png";


	connect(this, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(SlotItemPressed(QTreeWidgetItem*,int)));




	DsGetIMsgObserver()->AddObserver(this, ZTREEWIDGET_PRESS, NULL);

}

ZTreeWidget::~ZTreeWidget()
{
	DsGetIMsgObserver()->RemoveObserver(this);
}

bool ZTreeWidget::Load( const QString &filePath )
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{

		return false;
	}

	QDataStream stream(&file);
	stream.setVersion(QDataStream::Qt_4_8);
	stream >> m_rootItemData;


	return true;
}



bool ZTreeWidget::Save( const QString &filePath )
{
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QDataStream stream(&file);
	stream.setVersion(QDataStream::Qt_4_8);
	stream << m_rootItemData;


	return true;
}

void ZTreeWidget::InitTreeWidget()
{
	_InitTreeWidget(m_root, m_rootItemData);
}

void ZTreeWidget::_InitTreeWidget(QTreeWidgetItem *parent,  const ZTreeItemData &parentItemData )
{
	foreach(const ZTreeItemData &childItemData, parentItemData.items)
	{
		QTreeWidgetItem *newItem = new QTreeWidgetItem(parent);
		ZItemData itemData(childItemData);
		newItem->setData(0, ItemData, QVariant::fromValue(itemData));
		if (parentItemData.type == DirectoryType)
		{
			newItem->setIcon(0, QIcon(m_floderIcon));
			if (!parentItemData.items.isEmpty())
			{
				_InitTreeWidget(newItem, childItemData);
			}

		}
		else if (parentItemData.type == FileType)
		{
			newItem->setIcon(0, QIcon(m_fileIcon));

		}
	}
}

void ZTreeWidget::SlotItemPressed( QTreeWidgetItem *item, int colume )
{

	ZItemData oldItemData = item->data(0, ItemData).value<ZItemData>();
	if (qApp->mouseButtons() & Qt::RightButton)
	{
		QMenu menu;
		QAction *floderAct = menu.addAction("add floder");
		floderAct->setEnabled(oldItemData.type == DirectoryType);
		QAction *fileAct = menu.addAction("add file");
		fileAct->setEnabled(item != m_root);
		QAction *act = menu.exec(cursor().pos());
		if (act == floderAct)
		{
			//QTreeWidgetItem *newItem = new QTreeWidgetItem(item, QStringList() << "Untitle");
			QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "Untitle");
			newItem->setIcon(0, QIcon(m_floderIcon));
			ZItemData itemData;
			itemData.title = "Untitle";
			itemData.type = DirectoryType;
			itemData.path = "";
			itemData.time = QDateTime::currentDateTime();
			newItem->setData(0,ItemData, QVariant::fromValue(itemData));
			item->insertChild(0, newItem);

		}
		else if (act == fileAct)
		{
			QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "Untitle");
			newItem->setIcon(0, QIcon(m_fileIcon));
			ZItemData itemData;
			itemData.title = "Untitle";
			itemData.type = FileType;
			itemData.path = GetCurrentFileDir() + "Untitle.html";
			itemData.time = QDateTime::currentDateTime();
			newItem->setData(0, ItemData, QVariant::fromValue(itemData));

			if (oldItemData.type == DirectoryType)
			{
				item->insertChild(0, newItem);
			}
			else if (oldItemData.type == FileType)
			{
				item->parent()->insertChild(item->parent()->indexOfChild(item), newItem);
			}


		}
		item->setExpanded(true);
	}
	else
	{
		if (oldItemData.type == FileType)
		{

			DsGetIMsg()->SendMsg(ZTREEWIDGET_PRESS, &oldItemData);
		}
	}
}




ZTextEdit::ZTextEdit( QWidget *parent /*= 0*/ )
	:QTextEdit(parent)
{

}

ZTextEdit::~ZTextEdit()
{

}

ZCentralWidget::ZCentralWidget( QWidget *parent /*= 0*/ )
	:QWidget(parent)
{
	m_textEdit = new ZTextEdit(this);
}

ZCentralWidget::~ZCentralWidget()
{

}

void ZCentralWidget::resizeEvent( QResizeEvent *event )
{
	const int margins = 1;
	QRect rect = this->rect();
	m_textEdit->setGeometry(margins, margins, rect.width()-2*margins, rect.height()-2*margins);
}
