#pragma once


class CDsDataEvent : public QEvent
{
public:
	CDsDataEvent(Type type, void *pdata)
		:QEvent(type)
	{
		m_pData = pdata;
	}

	inline void* data() const { return m_pData; }
protected:
	void* m_pData;
};

class CDsPointerIntEvent : public QEvent
{
public:
	CDsPointerIntEvent(Type type, void *pdata,qptrdiff data)
		:QEvent(type)
	{
		m_pData = pdata;
		m_data = data;
	}
	inline void* pdata() const { return m_pData; }
	inline qptrdiff	 data() const { return m_data; }
protected:
	void*	m_pData;
	qptrdiff		m_data;
};

class CDsPaintEvent : public QPaintEvent
{
public:
	CDsPaintEvent(Type type, void *pdata)
		:QPaintEvent(QRect())
	{
		m_pData = pdata;
	}
	inline void* data() const { return m_pData; }
protected:
	void* m_pData;
};

class CDsStringDataEvent : public QEvent
{
public:
	CDsStringDataEvent(Type type, void *pdata, string strData)
		:QEvent(type)
	{
		m_pData = pdata;
		m_pStrData = strData;
	}
	inline string strData() const { return m_pStrData; }
	inline void* data() const { return m_pData; }

protected:
	void*	m_pData;
	string  m_pStrData;
};

class CDsVariantDataEvent : public QEvent
{
public:
	CDsVariantDataEvent(Type type, QVariant variant)
		:QEvent(type)
	{
		m_variant = variant;
	}

	inline QVariant data() const { return m_variant; }

protected:
	QVariant	m_variant;
};


struct IDsMsg
{
	virtual void SendMsg(int eventType,bool isPost = false) = 0;//仅仅是发出这个通知
	virtual void SendMsg(int eventType,void *pdata,bool isPost = false) = 0;//带验证数据的message
	virtual void SendMsg(int eventType,void *pdata,qptrdiff data,bool isPost = false) = 0;//带验证数据和整型数据的message
	virtual void SendMsg(int eventType,void *pdata,string strData,bool isPost) = 0;	//带验证数据和string数据的message

	virtual void PostMsg(int eventType, QVariant variant = QVariant()) = 0;
	virtual void Release() = 0;
};


IDsMsg *DsGetIMsg();
void DsReleaseMsg();


struct IDsMsgObserver
{
	virtual bool AddObserver(QObject *observer,int eventType,QObject *anObject) = 0;
	virtual void RemoveObserver(int eventType) = 0;
	virtual void RemoveObserver(QObject *observer) = 0;
	virtual void RemoveObserver(QObject *observer,int eventType) = 0;

	//anObject指定发送者
	virtual void SendMsg(QObject *anObject,QEvent *pEvent,bool isPost = false) = 0;
	virtual void SendMsg(QObject *anObject,int eventType,bool isPost = false) = 0;
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,bool isPost = false) = 0;
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,qptrdiff data,bool isPost = false) = 0;
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,string data,bool isPost = false) = 0;
};


IDsMsgObserver *DsGetIMsgObserver();





class QObject;

struct ObserverNode 
{
	QObject	*observer;//
	QObject *anObject;//接受来自这个对象的msg，如果为NULL,则都接受
};

typedef vector<ObserverNode> ObserverList;

class CDsMsgEngine : public QObject,public IDsMsg,public IDsMsgObserver
{
	Q_OBJECT

public:
	CDsMsgEngine(QObject *parent=NULL);
	~CDsMsgEngine();
	void Release(){delete this;};

public://IDsMsg
	virtual void SendMsg(int eventType,bool isPost = false);//仅仅是发出这个通知
	virtual void SendMsg(int eventType,void *pdata,bool isPost = false);//带验证数据的message
	virtual void SendMsg(int eventType,void *pdata,qptrdiff data,bool isPost = false);
	virtual void SendMsg(int eventType,void *pdata,string strData,bool isPost);
	virtual void PostMsg(int eventType, QVariant variant = QVariant());

public://IDsMsgObserver
	virtual bool AddObserver(QObject *observer,int eventType,QObject *anObject);
	virtual void RemoveObserver(int eventType);
	virtual void RemoveObserver(QObject *observer);
	virtual void RemoveObserver(QObject *observer,int eventType);

	//anObject指定发送者
	virtual void SendMsg(QObject *anObject,QEvent *pEvent,bool isPost = false);
	virtual void SendMsg(QObject *anObject,int eventType,bool isPost = false);
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,bool isPost = false);
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,qptrdiff data,bool isPost = false);
	virtual void SendMsg(QObject *anObject,int eventType,void *pdata,string data,bool isPost = false);
protected:
	map<int,ObserverList*> m_msgMapTable;
	typedef map<int,ObserverList*>::iterator MSGMAPITER;//message map iterator
};