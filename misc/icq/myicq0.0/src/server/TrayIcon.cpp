// TrayIcon.cpp : implementation file
//

#include "stdafx.h"
#include "TrayIcon.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrayIcon
IMPLEMENT_DYNCREATE(CTrayIcon, CCmdTarget)
CTrayIcon::CTrayIcon()
{
	//��ʼ��NOTIFYICONDATA�ṹ����
	memset(&m_nid, 0 , sizeof(m_nid));
	m_nid.cbSize = sizeof(m_nid);	
}

CTrayIcon::~CTrayIcon()
{
	SetIcon(0,NULL); // ��ϵͳ������ɾ��ͼ��
}

// �趨֪ͨ���ڣ��ô��ڱ����ѱ�����
void CTrayIcon::SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg)
{
    ASSERT(pNotifyWnd==NULL || ::IsWindow(pNotifyWnd->GetSafeHwnd()));
	
    m_nid.hWnd = pNotifyWnd->GetSafeHwnd();
	
    ASSERT(uCbMsg==0 || uCbMsg>=WM_USER);
    m_nid.uCallbackMessage = uCbMsg;
}

BOOL CTrayIcon::SetIcon(UINT uID,LPCSTR lpTip)
{ 
	HICON hicon=NULL;
	if (uID)
	{
		if(lpTip!=NULL)
			strcpy(m_nid.szTip,lpTip);
		hicon = AfxGetApp()->LoadIcon(uID);
	}
	
	UINT msg;
	m_nid.uFlags = 0;
	
	// �趨ͼ��
	if (hicon)
	{
		// �ж���Ҫ��ϵͳ���������ӻ���Ҫɾ��ͼ��
		msg = m_nid.hIcon ? NIM_MODIFY : NIM_ADD;
		m_nid.hIcon = hicon;
		m_nid.uFlags = NIF_ICON|NIF_MESSAGE;
		if(lpTip!=NULL)
			m_nid.uFlags|=NIF_TIP;
	} 
	else 
	{ // ɾ��ͼ��
		if (m_nid.hIcon==NULL)
			return TRUE;   //�ѱ�ɾ��
		msg = NIM_DELETE;
	}	
	
	BOOL bRet = Shell_NotifyIcon(msg, &m_nid);
	if (msg==NIM_DELETE || !bRet)
		m_nid.hIcon = NULL; 
	return bRet;
}

// ȱʡ�¼�������򣬸ó���������һ���˫���¼���
LRESULT CTrayIcon::OnTrayNotification(WPARAM wID,LPARAM lEvent)
{
	if (wID!=m_nid.uID ||(lEvent!=WM_RBUTTONUP && lEvent!=WM_LBUTTONDBLCLK))
		return 0;	
	
	CMenu menu,*pMenu;

	if(!menu.LoadMenu(IDR_POPUP))return 0;
	pMenu=menu.GetSubMenu(0);
	
	if (lEvent==WM_RBUTTONUP)
	{		
		// �����ĵ�ǰλ�õ����˵���
		CPoint mouse;
		GetCursorPos(&mouse);
		::SetForegroundWindow(m_nid.hWnd); 
		::TrackPopupMenu(pMenu->m_hMenu,
			0,
			mouse.x,
			mouse.y,
			0,
			m_nid.hWnd,
			NULL);		
	}	
	else
	{
		::SendMessage(m_nid.hWnd,WM_COMMAND,pMenu->GetMenuItemID(0),0);
	}
	
	return 1; // ��ʾ�¼��ѱ�����
}

/////////////////////////////////////////////////////////////////////////////
// CTrayIcon message handlers
