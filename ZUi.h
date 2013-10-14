
#ifndef ZUI_H_H
#define ZUI_H_H





class ZDockWidget : public QDockWidget
{
	Q_OBJECT
public:
	ZDockWidget(QWidget *parent = 0);
	~ZDockWidget();


private:

};


class ZTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	ZTreeWidget(QWidget *parent = 0);
	~ZTreeWidget();
	
	bool Load(const QString &filePath);
	bool Save(const QString &filePath = "");

private:
	void InitTreeWidget();
	void _InitTreeWidget(QTreeWidgetItem *parent, const ZTreeItemData &parentItemData);
	void LoadTreeWidget(ZTreeItemData &treeItemData, QTreeWidgetItem *item);
	void SaveTreeWidget(ZTreeItemData &treeItemData, QTreeWidgetItem *item);

	void DeleteTreeItem(QTreeWidgetItem *item);
	void _DeleteTreeItem(QTreeWidgetItem *item);

	void ExpandTree(QTreeWidgetItem *item);
private slots:
	void SlotItemPressed(QTreeWidgetItem *item, int colume);
	void SlotItemChanged(QTreeWidgetItem *item, int colume);;
private:

	ZTreeItemData	m_rootItemData;
	QTreeWidgetItem	*m_root;


	QString			m_floderIcon;
	QString			m_fileIcon;
};






class ZTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	ZTextEdit(QWidget *parent = 0);
	~ZTextEdit();


private:



};




class ZCentralWidget : public QWidget
{
	Q_OBJECT
public:
	ZCentralWidget(QWidget *parent = 0);
	~ZCentralWidget();


	bool	OpenFile(const QString &filePath);
	bool	SaveFile();
	void	ClearContent();
	
protected:
	void resizeEvent(QResizeEvent *event);
	void customEvent(QEvent *event);
	bool SaveFile(const QString &filePath, const QByteArray &content);

private:
	ZTextEdit	*m_textEdit;

	ZItemData	m_curItemData;
};









#endif




