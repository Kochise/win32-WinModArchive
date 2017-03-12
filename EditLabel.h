#if !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditLabel window
enum FlashType {None, Text, Background };

class CEditLabel : public CEdit
{
// Construction
public:
	CEditLabel();
	CEditLabel& SetBkColor(COLORREF crBkgnd);
	CEditLabel& SetTextColor(COLORREF crText);
	CEditLabel& SetText(const CString& strText);
	CEditLabel& SetFontBold(BOOL bBold);
	CEditLabel& SetFontName(const CString& strFont);
	CEditLabel& SetFontUnderline(BOOL bSet);
	CEditLabel& SetFontItalic(BOOL bSet);
	CEditLabel& SetFontSize(int nSize);
	CEditLabel& SetFontStrikeOut(BOOL bSet);
	CEditLabel& SetSunken(BOOL bSet);
	CEditLabel& SetBorder(BOOL bSet);
	CEditLabel& FlashText(BOOL bActivate);
	CEditLabel& FlashBackground(BOOL bActivate);
	CEditLabel& SetLink(BOOL bLink);
	CEditLabel& SetLinkCursor(HCURSOR hCursor);

	void SetAutoRedraw(BOOL bSet) { m_bAutoRedraw=bSet; }
	void SetAutoFont(BOOL bSet) { m_bAutoFont=bSet; }
	void CreateFont(void) { ReconstructFont(); }
	void Refresh(void) { RedrawWindow(); }

// Attributes
public:
protected:
	void ReconstructFont();
	COLORREF	m_crText;
	HBRUSH		m_hBrush;
	HBRUSH		m_hwndBrush;
	LOGFONT		m_lf;
	CFont		m_font;
	CString		m_strText;
	BOOL		m_bState;
	BOOL		m_bTimer;
	BOOL		m_bLink;
	BOOL		m_bAutoRedraw,m_bAutoFont;
	FlashType	m_Type;
	HCURSOR		m_hCursor;
			// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
