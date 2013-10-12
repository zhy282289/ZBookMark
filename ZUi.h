
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
	bool Save(const QString &filePath);

private:
	void InitTreeWidget();
	void _InitTreeWidget(QTreeWidgetItem *parent, const ZTreeItemData &parentItemData);

private slots:
	void SlotItemPressed(QTreeWidgetItem *item, int colume);
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

protected:
	void resizeEvent(QResizeEvent *event);
	void customEvent(QEvent *event);


private:
	ZTextEdit	*m_textEdit;
};









#endif




