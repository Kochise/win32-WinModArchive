// WinModArchiveDlg.h : header file
//

#if !defined(AFX_WINMODARCHIVEDLG_H__6E43B22C_F93B_4E5F_B031_6F99E5F778FC__INCLUDED_)
#define AFX_WINMODARCHIVEDLG_H__6E43B22C_F93B_4E5F_B031_6F99E5F778FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EditLabel.h"

/////////////////////////////////////////////////////////////////////////////
// CWinModArchiveDlg dialog

class CWinModArchiveDlg : public CDialog
{
// Construction
public:
	CWinModArchiveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinModArchiveDlg)
	enum { IDD = IDD_WINMODARCHIVE_DIALOG };
	CEditLabel m_oEditIn;
	CButton m_oButRun;
	CButton m_oButIn;
	CStatic m_oWndStatus;
	CStatic m_oWndProgress;
	CString m_oStrIn;
	CString m_oStrOut;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinModArchiveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

  void SelectRun(void);

// Implementation
protected:
	HICON m_hIcon;
  BOOL  m_bTestDestination;

	// Generated message map functions
	//{{AFX_MSG(CWinModArchiveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButIn();
	afx_msg void OnButRun();
	afx_msg void OnChangeTxtOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINMODARCHIVEDLG_H__6E43B22C_F93B_4E5F_B031_6F99E5F778FC__INCLUDED_)
