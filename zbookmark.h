#ifndef ZBOOKMARK_H
#define ZBOOKMARK_H

#include <QtGui/QMainWindow>


class ZBookMark : public QMainWindow
{
	Q_OBJECT

public:
	ZBookMark(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ZBookMark();



private slots:
	void SlotSaveAct();

protected:
	void closeEvent(QCloseEvent *event);


private:
	ZDockWidget	*m_indexDockWidget;
	ZTreeWidget	*m_indexTreeWidget;
	ZCentralWidget *m_centralWidget;



	QMenu		*m_fileMenu;
	QAction		*m_exitAct;

	QMenu		*m_editMenu;
	QAction		*m_saveAct;


};

#endif // ZBOOKMARK_H
