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
	
	m_root = NULL;
	//ZItemData itemData;
	//itemData.title = "Root";
	//itemData.type = DirectoryType;
	//m_root = new QTreeWidgetItem(this, QStringList() <<itemData.title);
	//m_root->setData(0, ItemData, QVariant::fromValue(itemData));
	//m_root->setExpanded(true);

	m_floderIcon = ":/ZBookMark/Resources/floder.png";
	m_fileIcon = ":/ZBookMark/Resources/file.png";

	connect(this, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(SlotItemPressed(QTreeWidgetItem*,int)));
	connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(SlotItemChanged(QTreeWidgetItem*,int)));

	Load(GetTreeItemDataConfigPath());
}

ZTreeWidget::~ZTreeWidget()
{
}

bool ZTreeWidget::Load( const QString &filePath )
{
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly))
	{
		QDataStream stream(&file);
		stream.setVersion(QDataStream::Qt_4_8);
		stream >> m_rootItemData;	
	}
	else
	{
		ZItemData itemData;
		itemData.title = "Root";
		itemData.type = DirectoryType;
		itemData.expand = true;
		m_rootItemData = (itemData);
	}


	LoadTreeWidget(m_rootItemData, m_root);
	ExpandTree(m_root);

	return true;
}



bool ZTreeWidget::Save( const QString &filePath )
{
	QString path = GetTreeItemDataConfigPath();
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}


	SaveTreeWidget(m_rootItemData, m_root);

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
		QAction *fileAct = menu.addAction("增加文件");
		fileAct->setEnabled(item != m_root);
		QAction *floderAct = menu.addAction("增加文件夹");
		//floderAct->setEnabled(oldItemData.type == DirectoryType);
		QAction *deleteAct = menu.addAction("删除");
		deleteAct->setEnabled(item != m_root);

		QAction *act = menu.exec(cursor().pos());
		if (act == floderAct)
		{
			QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "未命名");
			newItem->setIcon(0, QIcon(m_floderIcon));
			newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
			ZItemData itemData;
			itemData.title = "未命名";
			itemData.type = DirectoryType;
			itemData.path = GetNewFilePath();
			itemData.time = QDateTime::currentDateTime();
			newItem->setData(0,ItemData, QVariant::fromValue(itemData));
			if (oldItemData.type == DirectoryType)
			{
				item->insertChild(0, newItem);
			}
			else
			{
				item->parent()->insertChild(item->parent()->indexOfChild(item), newItem);
			}

			item->setExpanded(true);
		}
		else if (act == fileAct)
		{
			QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "未命名");
			newItem->setIcon(0, QIcon(m_fileIcon));
			newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
			ZItemData itemData;
			itemData.title = "未命名";
			itemData.type = FileType;
			itemData.path = GetNewFilePath();
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
			item->setExpanded(true);
		}
		else if (act == deleteAct)
		{
			QString text = oldItemData.type == DirectoryType ? "确定要删除此文件夹包括文件夹下面的文件吗" : "确定要删除此文件吗";
			//if (YesNoBox(this, "警告", text))
			{
				DeleteTreeItem(item);
			}
		}
	}
	else
	{
		//if (oldItemData.type == FileType)
		{

			DsGetIMsg()->SendMsg(ZTREEWIDGET_PRESS, &oldItemData);
		}
	}
}

void ZTreeWidget::SaveTreeWidget( ZTreeItemData &treeItemData , QTreeWidgetItem *item)
{
	ZItemData itemData = item->data(0, ItemData).value<ZItemData>();

	treeItemData.title = itemData.title;
	treeItemData.type = itemData.type;
	treeItemData.path = itemData.path;
	treeItemData.time = itemData.time;
	treeItemData.expand = item->isExpanded();

	QVector<ZTreeItemData> treeItemDatas;
	if (itemData.type == DirectoryType)
	{
		int size = item->childCount();
		if (size)
		{
			for (int i = 0; i < size; ++i)
			{
				ZTreeItemData childTreeItemData;
				QTreeWidgetItem *childItem = item->child(i);
				SaveTreeWidget(childTreeItemData, childItem);
				treeItemDatas.push_back(childTreeItemData);
			}
		}
		else
		{
			// 文件夹转为文件
			treeItemData.type = FileType;
		}
	}
	else if (itemData.type == FileType)
	{
		int size = item->childCount();
		if (size)
		{
			treeItemData.type = DirectoryType;
		}	
		for (int i = 0; i < size; ++i)
		{
			ZTreeItemData childTreeItemData;
			QTreeWidgetItem *childItem = item->child(i);
			SaveTreeWidget(childTreeItemData, childItem);
			treeItemDatas.push_back(childTreeItemData);
			
		}
	}

	treeItemData.items = treeItemDatas;
}

void ZTreeWidget::LoadTreeWidget( ZTreeItemData &treeItemData, QTreeWidgetItem *item )
{
	if (treeItemData.type == DirectoryType)
	{
		QTreeWidgetItem *newItem;
		newItem = new QTreeWidgetItem(QStringList() << treeItemData.title);
		newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);	
		newItem->setIcon(0, QIcon(m_floderIcon));

		int size = treeItemData.items.size();
		for (int i = 0; i < size; ++i)
		{
			ZTreeItemData childTreeItemData = treeItemData.items.at(i);
			LoadTreeWidget(childTreeItemData, newItem);		
		}

		
		ZItemData itemData(treeItemData);
		newItem->setData(0,ItemData, QVariant::fromValue(itemData));
		
		if (item != NULL)
		{
			item->addChild(newItem);
		}
		else
		{
			m_root = newItem;
			this->addTopLevelItem(newItem);
		}


		//newItem->setExpanded(treeItemData.expand);

	}
	else if (treeItemData.type == FileType)
	{
		QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << treeItemData.title);
		newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);	
		newItem->setIcon(0, QIcon(m_fileIcon));
		//item->addChild(newItem);

		if (item != NULL)
		{
			item->addChild(newItem);
		}
		else
		{
			treeItemData.type = DirectoryType;
			m_root = newItem;
			this->addTopLevelItem(newItem);
		}

	
		ZItemData itemData(treeItemData);
		newItem->setData(0,ItemData, QVariant::fromValue(itemData));
	}

}

void ZTreeWidget::SlotItemChanged( QTreeWidgetItem *item, int colume )
{
	this->blockSignals(true);
	QString newTitle = item->text(0);
	ZItemData itemData = item->data(0, ItemData).value<ZItemData>();
	if (!newTitle.isEmpty())
	{
		itemData.title = newTitle;
		item->setData(0, ItemData, QVariant::fromValue(itemData));
	}
	else
	{
		item->setText(0, itemData.title);
	}
	this->blockSignals(false);
}

void ZTreeWidget::DeleteTreeItem( QTreeWidgetItem *item )
{
	_DeleteTreeItem(item);
	item->parent()->takeChild(item->parent()->indexOfChild(item));
}

void ZTreeWidget::_DeleteTreeItem( QTreeWidgetItem *item )
{
	ZItemData itemData = item->data(0, ItemData).value<ZItemData>();
	if (itemData.type == DirectoryType)
	{
		QString filePath = itemData.path;
		if (!QFile::remove(filePath))
		{
			//QMessageBox::warning(this, "提示", QString("删除文件失败:%1\n").arg(filePath));
		}

		int size = item->childCount();
		for (int i = 0; i < size; ++i)
		{
			QTreeWidgetItem *childItem = item->child(i);
			_DeleteTreeItem(childItem);
		}
	}
	else if (itemData.type == FileType)
	{
		QString filePath = itemData.path;
		if (!QFile::remove(filePath))
		{
			//QMessageBox::warning(this, "提示", QString("删除文件失败:%1\n").arg(filePath));
		}
	}
}

void ZTreeWidget::ExpandTree( QTreeWidgetItem *item )
{
	ZItemData itemData = item->data(0, ItemData).value<ZItemData>();
	if (itemData.type == DirectoryType)
	{
		item->setExpanded(itemData.expand);
		for (int i = 0; i < item->childCount(); ++i)
		{
			QTreeWidgetItem *childItem = item->child(i);
			ExpandTree(childItem);
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



	DsGetIMsgObserver()->AddObserver(this, ZTREEWIDGET_PRESS, NULL);
	DsGetIMsgObserver()->AddObserver(this, ZBOOKMARKMAINWINDOW_MENU_SAVE, NULL);
}

ZCentralWidget::~ZCentralWidget()
{
	DsGetIMsgObserver()->RemoveObserver(this);
}

void ZCentralWidget::resizeEvent( QResizeEvent *event )
{
	const int margins = 1;
	QRect rect = this->rect();
	m_textEdit->setGeometry(margins, margins, rect.width()-2*margins, rect.height()-2*margins);
}

void ZCentralWidget::customEvent( QEvent *event )
{
	switch (event->type())
	{
	case ZTREEWIDGET_PRESS:
		{
			CDsDataEvent *pEvent = static_cast<CDsDataEvent*>(event);
			ZItemData tempItemData = *((ZItemData*)pEvent->data());
			if (!(tempItemData == m_curItemData))
			{
				ClearContent();
				m_curItemData = *((ZItemData*)pEvent->data());
				QString filePath = m_curItemData.path;
				OpenFile(filePath);
			}

		}
		break;
	case ZBOOKMARKMAINWINDOW_MENU_SAVE:
		{
			m_textEdit->document()->setModified(false);
			SaveFile();
		}
		break;
	}
}


bool ZCentralWidget::OpenFile( const QString &filePath )
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QByteArray content = file.readAll();

	m_textEdit->setHtml(content);
	file.close();
	m_textEdit->document()->setModified(false);
	return true;
}

void ZCentralWidget::ClearContent()
{
	if (m_textEdit->document()->isModified())
	{
		//if (YesNoBox(this, "提示", "文件未保存, 是否保存"))
		{
			SaveFile();
		}

	}
	m_textEdit->clear();
}

bool ZCentralWidget::SaveFile( const QString &filePath, const QByteArray &content )
{
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	file.write(content);
	file.close();

	return true;
}

bool ZCentralWidget::SaveFile()
{
	QByteArray content = m_textEdit->toHtml().toLocal8Bit();
	return SaveFile(m_curItemData.path, content);
}

