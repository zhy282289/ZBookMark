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
}

ZBookMark::~ZBookMark()
{

}
