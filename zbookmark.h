#ifndef ZBOOKMARK_H
#define ZBOOKMARK_H

#include <QtGui/QMainWindow>


class ZBookMark : public QMainWindow
{
	Q_OBJECT

public:
	ZBookMark(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ZBookMark();

private:
	ZDockWidget	*m_indexDockWidget;
	ZTreeWidget	*m_indexTreeWidget;
	ZCentralWidget *m_centralWidget;
};

#endif // ZBOOKMARK_H
