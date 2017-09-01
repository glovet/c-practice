/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright            : (C) 2002 by Zhang Yong                         *
 *   email                : z-yong163@163.com                              *
 ***************************************************************************/

// DetailBasicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myicq.h"
#include "DetailBasicDlg.h"
#include "icqclient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailBasicDlg property page

IMPLEMENT_DYNCREATE(CDetailBasicDlg, CPropertyPage)

CDetailBasicDlg::CDetailBasicDlg() : CPropertyPage(CDetailBasicDlg::IDD)
{
	//{{AFX_DATA_INIT(CDetailBasicDlg)
	m_age = 0;
	m_gender = 0;
	m_nick = _T("");
	m_pic = 0;
	m_uin = 0;
	m_country = _T("");
	m_city = _T("");
	m_province = _T("");
	//}}AFX_DATA_INIT
}

CDetailBasicDlg::~CDetailBasicDlg()
{
}


void CDetailBasicDlg::enableAll(BOOL enable)
{
	GetDlgItem(IDC_PIC)->EnableWindow(enable);
	GetDlgItem(IDC_COUNTRY)->EnableWindow(enable);
	GetDlgItem(IDC_GENDER)->EnableWindow(enable);
	GetDlgItem(IDC_PROVINCE)->EnableWindow(enable);
	((CEdit *) GetDlgItem(IDC_NICK))->SetReadOnly(!enable);
	((CEdit *) GetDlgItem(IDC_AGE))->SetReadOnly(!enable);
	((CEdit *) GetDlgItem(IDC_CITY))->SetReadOnly(!enable);
}

void CDetailBasicDlg::setData(IcqInfo *info)
{
	m_pic = info->face;
	m_nick = info->nick.c_str();
	m_age = info->age;
	m_gender = info->gender;
	m_country = info->country.c_str();
	m_province = info->province.c_str();
	m_city = info->city.c_str();
	UpdateData(FALSE);
}


void CDetailBasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailBasicDlg)
	DDX_Control(pDX, IDC_PIC, m_cmbPic);
	DDX_Text(pDX, IDC_AGE, m_age);
	DDX_CBIndex(pDX, IDC_GENDER, m_gender);
	DDX_Text(pDX, IDC_NICK, m_nick);
	DDX_CBIndex(pDX, IDC_PIC, m_pic);
	DDX_Text(pDX, IDC_UIN, m_uin);
	DDX_CBString(pDX, IDC_COUNTRY, m_country);
	DDX_Text(pDX, IDC_CITY, m_city);
	DDX_CBString(pDX, IDC_PROVINCE, m_province);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailBasicDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CDetailBasicDlg)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailBasicDlg message handlers

BOOL CDetailBasicDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_cmbPic.addPics();
	m_cmbPic.SetCurSel(m_pic);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDetailBasicDlg::OnUpdate() 
{
	GetParent()->SendMessage(WM_COMMAND, IDC_UPDATE);
}

void CDetailBasicDlg::OnCancel() 
{
	GetParent()->DestroyWindow();
}
