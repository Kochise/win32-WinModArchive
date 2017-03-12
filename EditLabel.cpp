// EditLabel.cpp : implementation file
//

#include "stdafx.h"
#include "EditLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditLabel

CEditLabel::CEditLabel()
{
	m_crText = GetSysColor(COLOR_WINDOWTEXT);
	m_hBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);

	m_font.CreateFontIndirect(&m_lf);
	m_bTimer = FALSE;
	m_bState = FALSE;
	m_bLink = TRUE;
	m_bAutoRedraw=TRUE;m_bAutoFont=TRUE;
	m_hCursor = NULL;
	m_Type = None;

	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}


CEditLabel::~CEditLabel()
{
	m_font.DeleteObject();
	::DeleteObject(m_hBrush);
}

CEditLabel& CEditLabel::SetText(const CString& strText)
{
	SetWindowText(strText);
	return *this;
}

CEditLabel& CEditLabel::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}

CEditLabel& CEditLabel::SetFontBold(BOOL bBold)
{	
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}

CEditLabel& CEditLabel::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}

CEditLabel& CEditLabel::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;	
}

CEditLabel& CEditLabel::SetFontStrikeOut(BOOL bSet)
{
	m_lf.lfStrikeOut = bSet;
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;	
}

CEditLabel& CEditLabel::SetSunken(BOOL bSet)
{
	if (!bSet)
		ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_DRAWFRAME);
	else
		ModifyStyleEx(0,WS_EX_STATICEDGE,SWP_DRAWFRAME);
		
	return *this;	
}

CEditLabel& CEditLabel::SetBorder(BOOL bSet)
{
	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
		
	return *this;	
}

CEditLabel& CEditLabel::SetFontSize(int nSize)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}


CEditLabel& CEditLabel::SetBkColor(COLORREF crBkgnd)
{
	if (m_hBrush)
		::DeleteObject(m_hBrush);
	
	m_hBrush = ::CreateSolidBrush(crBkgnd);
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}

CEditLabel& CEditLabel::SetFontName(const CString& strFont)
{	
	strcpy(m_lf.lfFaceName,strFont);
	if(m_bAutoFont) ReconstructFont();
	if(m_bAutoRedraw) RedrawWindow();
	return *this;
}


BEGIN_MESSAGE_MAP(CEditLabel, CEdit)
	//{{AFX_MSG_MAP(CEditLabel)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditLabel message handlers

HBRUSH CEditLabel::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called

	if
  (
       (CTLCOLOR_STATIC == nCtlColor)
    || (CTLCOLOR_EDIT   == nCtlColor)
  )
	{
//		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
	}


	if (m_Type == Background)
	{
		if (!m_bState)
			return m_hwndBrush;
	}

	return m_hBrush;
}

void CEditLabel::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}


CEditLabel& CEditLabel::FlashText(BOOL bActivate)
{
	if (m_bTimer)
	{
		SetWindowText(m_strText);
		KillTimer(1);
	}

	if (bActivate)
	{
		GetWindowText(m_strText);
		m_bState = FALSE;
		
		m_bTimer = TRUE;
		SetTimer(1,500,NULL);
		m_Type = Text;
	}

	return *this;
}

CEditLabel& CEditLabel::FlashBackground(BOOL bActivate)
{

	if (m_bTimer)
		KillTimer(1);

	if (bActivate)
	{
		m_bState = FALSE;

		m_bTimer = TRUE;
		SetTimer(1,500,NULL);

		m_Type = Background;
	}

	return *this;
}


void CEditLabel::OnTimer(UINT nIDEvent) 
{
	m_bState = !m_bState;

	switch (m_Type)
	{
		case Text:
			if (m_bState)
				SetWindowText("");
			else
				SetWindowText(m_strText);
		break;

		case Background:
			InvalidateRect(NULL,FALSE);
			UpdateWindow();
		break;
	}
	
	CEdit::OnTimer(nIDEvent);
}

CEditLabel& CEditLabel::SetLink(BOOL bLink)
{
	m_bLink = bLink;

	if (bLink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

void CEditLabel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CString strLink;

//	GetWindowText(strLink);
//	ShellExecute(NULL,"open",strLink,NULL,NULL,SW_SHOWNORMAL);
		
	CEdit::OnLButtonDown(nFlags, point);
}

BOOL CEditLabel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CEdit::OnSetCursor(pWnd, nHitTest, message);
}

CEditLabel& CEditLabel::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
	return *this;
}

