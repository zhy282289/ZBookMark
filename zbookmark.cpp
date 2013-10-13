#include "stdafx.h"
#include "zbookmark.h"

ZBookMark::ZBookMark(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	m_indexDockWidget = new ZDockWidget(this);
	m_indexTreeWidget = new ZTreeWidget;
	m_indexDockWidget->setWidget(m_indexTreeWidget);
	m_indexDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_indexDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	m_indexDockWidget->setWindowTitle("Index");
	m_indexDockWidget->setMinimumWidth(225);
	m_indexDockWidget->setMaximumWidth(800);
	addDockWidget(Qt::LeftDockWidgetArea , m_indexDockWidget);


	m_centralWidget = new ZCentralWidget;
	setCentralWidget(m_centralWidget);




	m_fileMenu = menuBar()->addMenu(("文件"));
	m_exitAct = new QAction("退出", this);
	m_fileMenu->addAction(m_exitAct);
	connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));



	m_editMenu = menuBar()->addMenu(("编辑"));
	m_saveAct = new QAction("保存", this);
	m_editMenu->addAction(m_saveAct);
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(SlotSaveAct()));

}

ZBookMark::~ZBookMark()
{

}

void ZBookMark::SlotSaveAct()
{
	DsGetIMsg()->SendMsg(ZBOOKMARKMAINWINDOW_MENU_SAVE);
}

void ZBookMark::closeEvent( QCloseEvent *event )
{

	m_indexTreeWidget->Save();

	return QMainWindow::closeEvent(event);
}
