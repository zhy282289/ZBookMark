
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
	void LoadFromDirectory(const QString &path ,QTreeWidgetItem *item);

private slots:
	void SlotItemPressed(QTreeWidgetItem *item, int colume);
	void SlotItemChanged(QTreeWidgetItem *item, int colume);;
private:

	ZTreeItemData	m_rootItemData;
	QTreeWidgetItem	*m_root;


	QString			m_folderIcon;
	QString			m_fileIcon;
};






class ZTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	ZTextEdit(QWidget *parent = 0);
	~ZTextEdit();

	void SetSelectColor(const QColor &color);
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





class ZColorDialog : public QLabel
{
	Q_OBJECT
public:
	ZColorDialog(QWidget *parent = 0);
	~ZColorDialog();

	QColor CurrentColor();
protected:
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
private:
	QColorDialog		*m_colorDlg;
	QColor				m_curColor;
	QRect 				m_btnRect;
};







#endif




