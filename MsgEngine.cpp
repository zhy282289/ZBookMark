#include "stdafx.h"

#include "MsgEngine.h"

CDsMsgEngine::CDsMsgEngine(QObject *parent)
	: QObject(parent)
{

}

CDsMsgEngine::~CDsMsgEngine()
{
	MSGMAPITER it;
	for(it = m_msgMapTable.begin(); it != m_msgMapTable.end(); ++it)
	{
		if((*it).second != NULL)
			delete (*it).second;
	}
}

void CDsMsgEngine::SendMsg(int eventType,bool isPost)//仅仅是发出这个通知
{
	SendMsg(NULL,eventType,isPost);
}

void CDsMsgEngine::SendMsg(int eventType,void *pdata,bool isPost)//带验证数据的message
{
	SendMsg(NULL,eventType,pdata,isPost);
}

void CDsMsgEngine::SendMsg(int eventType,void *pdata,qptrdiff data,bool isPost)
{
	SendMsg(NULL,eventType,pdata,data,isPost);
}

void CDsMsgEngine::SendMsg(int eventType,void *pdata,string strData,bool isPost)
{
	SendMsg(NULL, eventType, pdata, strData, isPost);
}

bool CDsMsgEngine::AddObserver(QObject *observer,int eventType,QObject *anObject)
{
	if(eventType == 1861)
	{
		int xx = 0;
	}
	MSGMAPITER it = m_msgMapTable.find(eventType);
	if(it == m_msgMapTable.end())
	{//没有找到对应的,当然要将该消息进入map
		ObserverList *pObserverList = new ObserverList();
		ObserverNode node;
		node.observer = observer;
		node.anObject = anObject;
		pObserverList->push_back(node);
		m_msgMapTable.insert(pair<int,ObserverList*>(eventType, pObserverList));
	}
	else
	{
		ObserverList *pObserverList = (*it).second;
		bool bResult = false;
		//找一下看是否已经做了注册，以防多次注册
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			if((*pObserverList)[i].observer == observer)
				bResult = true;
		}
		if(bResult)
		{//如果此句柄的此消息已经做了注册，那当然就没有必要注册了
			return false;
		}
		else
		{
			ObserverNode node;
			node.observer = observer;
			node.anObject = anObject;
			pObserverList->push_back(node);
		}
	}
	return true;
}

void CDsMsgEngine::RemoveObserver(int eventType)
{
	MSGMAPITER itObserverList = m_msgMapTable.find(eventType);
	if(itObserverList != m_msgMapTable.end())
	{
		m_msgMapTable.erase(itObserverList);
	}
}

void CDsMsgEngine::RemoveObserver(QObject *observer)
{
	MSGMAPITER it;
	for(it = m_msgMapTable.begin(); it != m_msgMapTable.end();)
	{
		int eventType = (*it).first;
		//MSGMAPITER itObserverList = it;
		ObserverList *pObserverList = (*it).second;
		ObserverList::iterator itxx;
		//找一下看是否已经做了注册，以防多次注册
		for(itxx = pObserverList->begin(); itxx != pObserverList->end(); ++itxx)
		{
			if((*itxx).observer == observer)
			{
				pObserverList->erase(itxx);
				break;
			}
		}
		if(pObserverList->size() == 0)
		{
			delete pObserverList;
			m_msgMapTable.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void CDsMsgEngine::RemoveObserver(QObject *observer,int eventType)
{
	if(eventType == 1861)
	{
		int xx = 0;
	}
	MSGMAPITER itObserverList = m_msgMapTable.find(eventType);
	if(itObserverList != m_msgMapTable.end())
	{//没有找到对应的,当然要将该消息进入map
		ObserverList *pObserverList = (*itObserverList).second;
		ObserverList::iterator it;
		//找一下看是否已经做了注册，以防多次注册
		for(it = pObserverList->begin(); it != pObserverList->end(); ++it)
		{
			if((*it).observer == observer)
			{
				pObserverList->erase(it);
				break;
			}
		}
		if(pObserverList->size() == 0)
		{
			delete pObserverList;
			m_msgMapTable.erase(itObserverList);
		}
	}
	return;
}

	//anObject指定发送者
void CDsMsgEngine::SendMsg(QObject *anObject,int eventType,bool isPost)
{
	MSGMAPITER it = m_msgMapTable.find(eventType);
	if(it != m_msgMapTable.end())
	{
		ObserverList *pObserverList = (*it).second;
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			//csj 2010-7-3
			//if((*pObserverList)[i].anObject==NULL || 
			//	((*pObserverList)[i].anObject==anObject && (*pObserverList)[i].observer!=anObject))
			if((*pObserverList)[i].anObject==NULL || 
				(*pObserverList)[i].observer==anObject)
			{
				if(isPost)
				{
					//QEvent *pEvent = new QEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)));
					QEvent *pEvent = new QEvent(static_cast<QEvent::Type>(eventType));
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);
				}
				else
				{
					//QEvent curEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)));
					QEvent curEvent(static_cast<QEvent::Type>(eventType));
					QApplication::sendEvent((*pObserverList)[i].observer,&curEvent);
				}
			}
		}
	}
}

void CDsMsgEngine::SendMsg(QObject *anObject,QEvent *pEvent,bool isPost)
{
	MSGMAPITER it = m_msgMapTable.find(pEvent->type());
	if(it != m_msgMapTable.end())
	{
		ObserverList *pObserverList = (*it).second;
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			//csj 2010-7-3
			//if((*pObserverList)[i].anObject==NULL || 
			//	((*pObserverList)[i].anObject==anObject && (*pObserverList)[i].observer!=anObject))
			if((*pObserverList)[i].anObject==NULL || 
				(*pObserverList)[i].observer==anObject)
			{
				if(isPost)
				{
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);
				}
				else
				{
					QApplication::sendEvent((*pObserverList)[i].observer,pEvent);
				}
			}
		}
	}
}

void CDsMsgEngine::SendMsg(QObject *anObject,int eventType,void *pdata,bool isPost)
{
	MSGMAPITER it = m_msgMapTable.find(eventType);
	if(it != m_msgMapTable.end())
	{
		ObserverList *pObserverList = (*it).second;
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			//csj 2010-7-3
			//if((*pObserverList)[i].anObject==NULL || 
			//	((*pObserverList)[i].anObject==anObject && (*pObserverList)[i].observer!=anObject))
			if((*pObserverList)[i].anObject==NULL || 
				(*pObserverList)[i].observer==anObject)
			{
				if(isPost)
				{
					//CDsDataEvent *pEvent = new CDsDataEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)),pdata);
					CDsDataEvent *pEvent = new CDsDataEvent(static_cast<QEvent::Type>(eventType),pdata);
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);
				}
				else
				{
					//CDsDataEvent curEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)),pdata);
					CDsDataEvent curEvent(static_cast<QEvent::Type>(eventType),pdata);
					QApplication::sendEvent((*pObserverList)[i].observer,&curEvent);
				}
			}
		}
	}
}

void CDsMsgEngine::SendMsg(QObject *anObject,int eventType,void *pdata,qptrdiff data,bool isPost)
{
	MSGMAPITER it = m_msgMapTable.find(eventType);
	if(it != m_msgMapTable.end())
	{
		ObserverList *pObserverList = (*it).second;
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			//csj 2010-7-3
			//if((*pObserverList)[i].anObject==NULL || 
			//	((*pObserverList)[i].anObject==anObject && (*pObserverList)[i].observer!=anObject))
			if((*pObserverList)[i].anObject==NULL || 
				(*pObserverList)[i].observer==anObject)
			{
				if(isPost)
				{
					//CDsDataEvent *pEvent = new CDsDataEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)),pdata);
					CDsPointerIntEvent *pEvent = new CDsPointerIntEvent(static_cast<QEvent::Type>(eventType),pdata,data);
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);
				}
				else
				{
					//CDsDataEvent curEvent(static_cast<QEvent::Type>(QEvent::registerEventType(eventType)),pdata);
					CDsPointerIntEvent curEvent(static_cast<QEvent::Type>(eventType),pdata,data);
					QApplication::sendEvent((*pObserverList)[i].observer,&curEvent);
				}
			}
		}
	}
}

void CDsMsgEngine::SendMsg(QObject *anObject, int eventType, void *pdata, string strData, bool isPost)
{
	MSGMAPITER it = m_msgMapTable.find(eventType);
	if(it != m_msgMapTable.end())
	{
		ObserverList *pObserverList = (*it).second;
		for(int i = 0; i < pObserverList->size(); ++i)
		{
			//csj 2010-7-3
			if((*pObserverList)[i].anObject==NULL || 
				(*pObserverList)[i].observer==anObject)
			{
				if(isPost)
				{
					CDsStringDataEvent *pEvent = new CDsStringDataEvent(static_cast<QEvent::Type>(eventType),pdata,strData);
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);
				}
				else
				{
					CDsStringDataEvent curEvent(static_cast<QEvent::Type>(eventType),pdata,strData);
					QApplication::sendEvent((*pObserverList)[i].observer,&curEvent);
				}
			}
		}
	}
}


 void CDsMsgEngine::PostMsg(int eventType, QVariant variant/* = QVariant()*/)
 {
	 QObject *anObject = NULL;

	 MSGMAPITER it = m_msgMapTable.find(eventType);
	 if(it != m_msgMapTable.end())
	 {
		 ObserverList *pObserverList = (*it).second;
		 for(int i = 0; i < pObserverList->size(); ++i)
		 {
			 //csj 2010-7-3
			 if((*pObserverList)[i].anObject==NULL || 
				 (*pObserverList)[i].observer==anObject)
			 {

					CDsVariantDataEvent *pEvent = new CDsVariantDataEvent(static_cast<QEvent::Type>(eventType),variant);
					QApplication::postEvent((*pObserverList)[i].observer,pEvent);

			 }
		 }
	 }
 }









CDsMsgEngine g_msgEngine;


IDsMsg *DsGetIMsg()
{
	return dynamic_cast<IDsMsg *>(&g_msgEngine);
}

IDsMsgObserver *DsGetIMsgObserver()
{
	return dynamic_cast<IDsMsgObserver *>(&g_msgEngine);
}
