// Connection.h: interface for the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTION_H__AF7E2030_88FA_425B_9656_FD9916803A9A__INCLUDED_)
#define AFX_CONNECTION_H__AF7E2030_88FA_425B_9656_FD9916803A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "udt.h" 
using namespace UDT;
class Notify
{
public:
	virtual void  OnPeerConnected(TPeerPtr pConnection,bool bSuccess) = 0;           
	virtual void  OnPeerDisConnected(TPeerPtr pConnection) = 0;
	virtual void  OnPeerData(TPeerPtr pConnection,const char* pData, int ilen) = 0;
protected:
private:
};
using namespace UDT;
class CConnection :public TPeer
{
	Notify*  m_pNotify;
	TPeerMng *m_pMng;
public:
	CConnection(TPeerMng *pMng,unsigned int iPeerId):TPeer(pMng, iPeerId)
	{
		m_pMng = pMng;
	}
	virtual ~CConnection(){}
	void SetNotify(Notify* p){m_pNotify = p;}
	
	virtual void  OnPeerConnected(bool bSuccess)
	{ 
		TPeerPtr p = m_pMng->GetPeerInstance(GetPeerId());
		m_pNotify->OnPeerConnected(p,bSuccess);
	}
	virtual void  OnPeerDisConnected()
	{
		TPeerPtr p = m_pMng->GetPeerInstance(GetPeerId());
		m_pNotify->OnPeerDisConnected(p);
	}
	virtual void  OnPeerData(const char* pData, int ilen)
	{
		TPeerPtr p = m_pMng->GetPeerInstance(GetPeerId());
		m_pNotify->OnPeerData(p,pData,ilen);
	}
};
class T_ConnectMng
	:public TPeerMng
{
public:
	T_ConnectMng(unsigned int iMyId, const sockaddr* name, int namelen):TPeerMng(iMyId,name,namelen){};
	virtual ~T_ConnectMng(){};

	UDT::TPeerPtr PeerFactory(int iPeerId,int iTemplateType)
	{
		 return UDT::TPeerPtr((UDT::TPeer*)new CConnection(this,iPeerId)); 
	}
};
//typedef TPeerMngTemplate<CConnection> T_ConnectMng;

#endif // !defined(AFX_CONNECTION_H__AF7E2030_88FA_425B_9656_FD9916803A9A__INCLUDED_)
