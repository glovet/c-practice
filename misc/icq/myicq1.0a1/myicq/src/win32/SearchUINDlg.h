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

#if !defined(AFX_SEARCHUINDLG_H__33CDFEC4_1E67_4427_95EA_BA7187F55896__INCLUDED_)
#define AFX_SEARCHUINDLG_H__33CDFEC4_1E67_4427_95EA_BA7187F55896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchUINDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchUINDlg dialog

class CSearchUINDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CSearchUINDlg)

// Construction
public:
	CSearchUINDlg();
	~CSearchUINDlg();

	QID m_qid;

// Dialog Data
	//{{AFX_DATA(CSearchUINDlg)
	enum { IDD = IDD_SEARCH_UIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSearchUINDlg)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSearchUINDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHUINDLG_H__33CDFEC4_1E67_4427_95EA_BA7187F55896__INCLUDED_)
