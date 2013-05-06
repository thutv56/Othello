
#include "stdafx.h"
#include "Othello.h"
#include "COthelloMainFrm.h"
#include "COthelloDoc.h"
#include "COthelloView.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	APP_LEVEL		(5)
#define	APP_TIME_LIMIT	(3600)
#define	APP_WIDTH		(230)
#define	APP_HEIGHT		(320)

BEGIN_MESSAGE_MAP(COthelloApp, CWinApp)

	ON_COMMAND(ID_APP_ABOUT,	OnAppOptions)
	ON_COMMAND(ID_FILE_NEW,		CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,	CWinApp::OnFileOpen)

END_MESSAGE_MAP()

COthelloApp::COthelloApp()
{
}

COthelloApp theApp;

void COthelloApp::Init()
{
	m_pOthelloBoard	= COthelloBoard::CreateInstance(COthelloBoard::WHITE);
	m_bShowThinking	= FALSE;
	m_uiLevel		= APP_LEVEL;
	m_uiTimeLimit	= APP_TIME_LIMIT * 1000;
}

void COthelloApp::Release()
{
	COthelloBoard::DeleteInstance(m_pOthelloBoard);

	m_bShowThinking	= FALSE;
	m_uiLevel		= APP_LEVEL;
	m_uiTimeLimit	= APP_TIME_LIMIT * 1000;
}

COthelloApp* COthelloApp::GetInstance()
{
	return & theApp;
}

BOOL COthelloApp::InitInstance()
{
	CWinApp::InitInstance();

//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
//	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	CSingleDocTemplate* pDocTemplate;

	pDocTemplate = new CSingleDocTemplate
	(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COthelloDoc),
		RUNTIME_CLASS(COthelloMainFrame),
		RUNTIME_CLASS(COthelloView)
	);

	AddDocTemplate(pDocTemplate);
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo)) return FALSE;

	int x = (GetSystemMetrics(SM_CXSCREEN) - APP_WIDTH)  / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - APP_HEIGHT) / 2;

	m_pMainWnd->MoveWindow(x,y,APP_WIDTH,APP_HEIGHT);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

class COptionsDlg : public CDialog
{
public:

	COptionsDlg();

	enum { IDD = IDD_ABOUTBOX };
	
	INT		m_uiLevel;
	UINT	m_uiTimeLimit;
	BOOL	m_bShowThinking;

	void DoDataExchange(CDataExchange*);

	DECLARE_MESSAGE_MAP()
};

int aLevel[100] = 
{
	 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,
	 1,  1,  1,  1,  1,  1,  1,  2,  2,  2,
	 2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
	 3,  3,  3,  3,  3,  4,  4,  4,  4,  4,
	 4,  4,  4,  4,  4,  5,  5,  5,  5,  5,
	 5,  5,  5,  5,  5,  6,  6,  6,  6,  6,
	 7,  7,  7,  7,  7,  8,  8,  8,  8,  8,
	 9,  9,  9,  9,  9, 10, 10, 10, 10, 10,
	12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
	32, 36, 39, 42, 45, 48, 51, 54, 57, 60
};

bool InitSlide(int* aSlide)
{
	int i=0;

	for(i=0;    i<60;  ++i) aSlide[i] = -1;
	for(i=0;    i<100; ++i) aSlide[aLevel[i]] = i;
	for(i=60-2; i>=0;  --i) if (aSlide[i]==-1) aSlide[i] = aSlide[i+1];

	return true;
}

int Slide2Level(int iSlide)
{
	return aLevel[iSlide];
}

int Level2Slide(int iLevel)
{
	static int aSlide[60];
	static bool dummy = InitSlide(&aSlide[0]);

	return aSlide[iLevel];
}

COptionsDlg::COptionsDlg() : CDialog(COptionsDlg::IDD) 
{
	m_uiLevel		= Level2Slide(COthelloApp::GetInstance()->m_uiLevel);
	m_uiTimeLimit	= COthelloApp::GetInstance()->m_uiTimeLimit / 1000;
	m_bShowThinking	= COthelloApp::GetInstance()->m_bShowThinking;
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Slider(		pDX, IDC_LEVEL_SLIDER,	m_uiLevel);
	DDX_Text(		pDX, IDC_TIME_LIMIT,	m_uiTimeLimit);
	DDX_Check(		pDX, IDC_THINKING,		m_bShowThinking);

	DDV_MinMaxUInt(	pDX, m_uiLevel,		0, 100);
	DDV_MinMaxUInt(	pDX, m_uiTimeLimit, 0, 3600);

	COthelloApp::GetInstance()->m_uiLevel		= Slide2Level(m_uiLevel);
	COthelloApp::GetInstance()->m_uiTimeLimit	= 1000 * m_uiTimeLimit;
	COthelloApp::GetInstance()->m_bShowThinking	= m_bShowThinking;
}

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
END_MESSAGE_MAP()

void COthelloApp::OnAppOptions()
{
	COptionsDlg aboutDlg;
	aboutDlg.DoModal();
}
