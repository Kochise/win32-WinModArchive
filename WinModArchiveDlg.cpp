// WinModArchiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinModArchive.h"
#include "WinModArchiveDlg.h"

#include "SkinProgress.h"
#include "c_repertoire.h"
#include "PathDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinModArchiveDlg dialog

CWinModArchiveDlg::CWinModArchiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinModArchiveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinModArchiveDlg)
	m_oStrIn = _T("");
	m_oStrOut = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinModArchiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinModArchiveDlg)
	DDX_Control(pDX, IDC_TXT_OUT, m_oEditIn);
	DDX_Control(pDX, IDC_BUT_RUN, m_oButRun);
	DDX_Control(pDX, IDC_BUT_IN, m_oButIn);
	DDX_Control(pDX, IDC_STA_STATUS, m_oWndStatus);
	DDX_Control(pDX, IDC_STA_PROGRESS, m_oWndProgress);
	DDX_Text(pDX, IDC_TXT_IN, m_oStrIn);
	DDX_Text(pDX, IDC_TXT_OUT, m_oStrOut);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinModArchiveDlg, CDialog)
	//{{AFX_MSG_MAP(CWinModArchiveDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_IN, OnButIn)
	ON_BN_CLICKED(IDC_BUT_RUN, OnButRun)
	ON_EN_CHANGE(IDC_TXT_OUT, OnChangeTxtOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinModArchiveDlg message handlers

BOOL CWinModArchiveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
  m_oButIn.EnableWindow(TRUE);
  m_bTestDestination = FALSE;
  SelectRun();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinModArchiveDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinModArchiveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinModArchiveDlg::OnButIn() 
{
  CString     l_oStrBoite(_T("Répertoire Source"));
  CString     l_oStrTitre(_T("Cherchez l'emplacement des fichiers à traiter..."));
  CPathDialog l_oDlgPathSelect(l_oStrBoite, l_oStrTitre, m_oStrIn);
  CFile       l_oFileTempo;
  CString     l_oStrFileNameTempo;

  if(l_oDlgPathSelect.DoModal() == IDOK)
  { // Si c'est OK
    m_oStrIn = l_oDlgPathSelect.GetPathName() + "\\";        // On récupère le répertoire sélectionné
    m_oStrIn.Replace("\\\\", "\\");

    // Si Source est vide, on utilise le répertoire Destination comme Source
    if(m_oStrIn.IsEmpty() == FALSE)
    {
      // Si on vient de prendre le répertoire Source en Destination, on vérifie si on peut écrire dedans
      l_oStrFileNameTempo = m_oStrIn + _T("test.tmp");
      if(l_oFileTempo.Open(l_oStrFileNameTempo, CFile::modeWrite|CFile::modeCreate))
      { // Si on a ouvert le fichier, c'est que l'écriture est possible
        l_oFileTempo.Close();
        l_oFileTempo.Remove(l_oStrFileNameTempo);

        m_bTestDestination = TRUE;
      }
      else
      {
        m_bTestDestination = FALSE;
      }
    }
    else
    {
      m_bTestDestination = FALSE;
    }
  }else{}

  // On met à jours les champs de la fenêtre
  UpdateData(FALSE);

  SelectRun();
}

void CWinModArchiveDlg::OnButRun() 
{
  m_oButIn.EnableWindow(FALSE);
  m_oButRun.EnableWindow(FALSE);



	
  m_oButRun.EnableWindow(TRUE);
  m_oButIn.EnableWindow(TRUE);
}

void CWinModArchiveDlg::OnChangeTxtOut() 
{
  SelectRun();	
}

void CWinModArchiveDlg::SelectRun(void)
{
  UpdateData(TRUE);

  if(m_oStrIn.IsEmpty() == FALSE)
  {
    if(m_oStrOut.IsEmpty() == FALSE)
    {
      if(m_oStrOut.FindOneOf("\\:+-") == (-1))
      {
        m_oEditIn.SetBkColor(RGB(255, 255, 255));
        m_oButRun.EnableWindow(TRUE);
      }
      else
      {
        if(m_bTestDestination == TRUE)
        {
          m_oEditIn.SetBkColor(RGB(255, 255, 255));
        }
        else
        {
          m_oEditIn.SetBkColor(RGB(255, 127, 31));
        }
        m_oButRun.EnableWindow(FALSE);
      }
    }
    else
    {
      m_oEditIn.SetBkColor(RGB(255, 255, 255));
      m_oButRun.EnableWindow(FALSE);
    }
  }
  else
  {
    m_oButRun.EnableWindow(FALSE);
  }
}
