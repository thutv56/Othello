// COthelloView.cpp : implementation of the COthelloView class
//

#include "stdafx.h"
#include "Othello.h"

#include "COthelloDoc.h"
#include "COthelloView.h"

#include "CViewBrushes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**************************************************************************************************************************************************************/

#define	DX0					10
#define	DY0					50

#define	DX					25
#define	DT					4

#define W					8
#define H					8

#define	COLOR_APP_BCKG		RGB(215, 217, 212)
#define	COLOR_BCKG			RGB( 71, 159,  77)
#define	COLOR_TEXT_BCKG		RGB(255, 255, 255)
#define	COLOR_WHITE			RGB(255, 255, 255)
#define	COLOR_BLACK			RGB( 60,  40,   7)
#define COLOR_LAST_MOVE		RGB(120,  50,  10)

#define BOARD				(COthelloApp::GetInstance()->m_pOthelloBoard)

// COthelloView

IMPLEMENT_DYNCREATE(COthelloView, CView)

BEGIN_MESSAGE_MAP(COthelloView, CView)
	//{{AFX_MSG_MAP(COthelloView)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()

// COthelloView construction/destruction

/**************************************************************************************************************************************************************/

COthelloView::COthelloView()
{
	theApp.Init();

	m_iLastX = -100;
	m_iLastY = -100;
}

/**************************************************************************************************************************************************************/

void COthelloView::DrawPiece(CClientDC& dc, int x, int y, COLORREF color, bool bFast)
{
	if (bFast)
	{
		dc.FillSolidRect
		(
			DX0+DX*x+DT+3,
			DY0+DX*y+DT+3,
			DX-2*DT-6,
			DX-2*DT-6,
			color
		);
	}
	else
	{
		CBrushToggle brush(&dc,color);

		dc.Ellipse
		(
			DX0+DX*x+DT,
			DY0+DX*y+DT,
			DX0+DX*x+DX-DT,
			DY0+DX*y+DX-DT
		);

		dc.FloodFill
		(
			DX0+DX*x+DT+(DX/2)-DT, 
			DY0+DX*y+DT+(DX/2)-DT,
			RGB(0,0,0)
		);
	}

}

/**************************************************************************************************************************************************************/

void COthelloView::DrawBackground(CClientDC& dc)
{
	dc.FillSolidRect(0,0,400,400,COLOR_APP_BCKG);
	dc.FillSolidRect(DX0,DY0,W*DX,H*DX,COLOR_BCKG);

	{
		CPenToggle pen(&dc,1,RGB(139,153,140));

		for(int w=0; w<W+1; ++w)
		{
			dc.MoveTo(1+DX0+DX*w,	1+DY0);
			dc.LineTo(1+DX0+DX*w,	1+DY0+DX*H);
		}

		for(int h=0; h<H+1; ++h)
		{
			dc.MoveTo(1+DX0,		1+DY0+DX*h);
			dc.LineTo(1+DX0+DX*W,	1+DY0+DX*h);
		}
	}

	for(int w=0; w<W+1; ++w)
	{
		dc.MoveTo(DX0+DX*w,	DY0);
		dc.LineTo(DX0+DX*w,	DY0+DX*H);
	}

	for(int h=0; h<H+1; ++h)
	{
		dc.MoveTo(DX0,		DY0+DX*h);
		dc.LineTo(DX0+DX*W,	DY0+DX*h);
	}
}

/**************************************************************************************************************************************************************/

void COthelloView::DrawPieces(CClientDC& dc, const COthelloBoard* pBoard, bool bFast)
{
	for(int w=0; w<W; ++w)
	for(int h=0; h<H; ++h)
	{
		if (pBoard->GetDisk(w,h) == COthelloBoard::BLACK)
		{
			DrawPiece(dc,w,h,COLOR_BLACK,bFast);
		}
		else if (pBoard->GetDisk(w,h) == COthelloBoard::WHITE)
		{
			DrawPiece(dc,w,h,COLOR_WHITE,bFast);
		}
		else
		{
			dc.FillSolidRect(DX0+DX*w+DT,DY0+DX*h+DT,DX-2*DT,DX-2*DT,COLOR_BCKG);
		}
	}
}

/**************************************************************************************************************************************************************/

void COthelloView::DrawSearchingTag(CClientDC& dc)
{
	dc.FillSolidRect(DX0,2*DT,(DX0+DX*W)-(DX0),(DY0-2*DT)-(2*DT),COLOR_TEXT_BCKG);

	dc.MoveTo(DX0,		2*DT);
	dc.LineTo(DX0+DX*W,	2*DT);

	dc.MoveTo(DX0,		DY0-2*DT);
	dc.LineTo(DX0+DX*W,	DY0-2*DT);

	dc.MoveTo(DX0,		2*DT);
	dc.LineTo(DX0,		DY0-2*DT);

	dc.MoveTo(DX0+DX*W,	2*DT);
	dc.LineTo(DX0+DX*W,	DY0-2*DT);

	static CRect rec(DX0+1, 2*DT+1, DX0+DX*W-1, DY0-2*DT-1);

	dc.DrawText(" Searching...",13,rec,DT_LEFT);
}

/**************************************************************************************************************************************************************/

void COthelloView::DrawScoringTag(CClientDC& dc, const COthelloBoard* pBoard)
{
	char strScore[128];

	int iScoreB = pBoard->GetNbDisks(COthelloBoard::BLACK);
	int iScoreW = pBoard->GetNbDisks(COthelloBoard::WHITE);

	if ((!BOARD->CanPlay(COthelloBoard::WHITE)) && (!BOARD->CanPlay(COthelloBoard::BLACK)))
	{
		if (iScoreB > iScoreW)
		{
			sprintf(strScore," Black : %d  /  White : %d\n %s", iScoreB, iScoreW, "Game over - Black win");
		}
		else if (iScoreW > iScoreB)
		{
			sprintf(strScore," Black : %d  /  White : %d\n %s", iScoreB, iScoreW, "Game over - White win");
		}
		else
		{
			sprintf(strScore," Black : %d  /  White : %d\n %s", iScoreB, iScoreW, "Game over - Tied");
		}
	}
	else
	{
		sprintf(strScore," Black : %d  /  White : %d\n %s", iScoreB, iScoreW, "You play");
	}

	dc.FillSolidRect(DX0,2*DT,(DX0+DX*W)-(DX0),(DY0-2*DT)-(2*DT),COLOR_TEXT_BCKG);

	dc.MoveTo(DX0,		2*DT);
	dc.LineTo(DX0+DX*W,	2*DT);

	dc.MoveTo(DX0,		DY0-2*DT);
	dc.LineTo(DX0+DX*W,	DY0-2*DT);

	dc.MoveTo(DX0,		2*DT);
	dc.LineTo(DX0,		DY0-2*DT);

	dc.MoveTo(DX0+DX*W,	2*DT);
	dc.LineTo(DX0+DX*W,	DY0-2*DT);

	static CRect rec(DX0+1, 2*DT+1, DX0+DX*W-1, DY0-2*DT-1);

	dc.DrawText(strScore,(int)strlen(strScore),rec,DT_LEFT);
}

/**************************************************************************************************************************************************************/

void COthelloView::Draw(const COthelloBoard* pBoard)
{
	CClientDC dc(this);

	DrawBackground	(dc);
	DrawScoringTag	(dc,BOARD);
	DrawPieces		(dc,BOARD,false);
}

/**************************************************************************************************************************************************************/

struct CCallback : public COthelloBoard::CCallback
{
	CCallback(COthelloView* pView) : m_pView(pView)
	{
		m_pDC = new CClientDC(pView);
	}

	~CCallback()
	{
		if (m_pDC) delete m_pDC;
	}

	virtual void operator()(const COthelloBoard* pBoard)
	{
		if (m_pDC)
		{
			m_pView->DrawPieces(*m_pDC,pBoard,true);
		}
	}

	CClientDC*		m_pDC;
	COthelloView*	m_pView;
};

/**************************************************************************************************************************************************************/

void COthelloView::AutoPlay(int ePlayer)
{
	CClientDC dc(this);
	
	if (COthelloApp::GetInstance()->m_bShowThinking)
	{
		DrawBackground(dc);
	}
	else
	{
		DrawPieces(dc,BOARD,false);
	}

	DrawSearchingTag(dc);

	int x,y;

	CCallback callback(this);
			
	m_iLastX = -100;
	m_iLastY = -100;

	BOARD->AutoPlay
	(
		(COthelloBoard::EDisk)ePlayer,

		min
		(
			(int)COthelloApp::GetInstance()->m_uiLevel,
			BOARD->GetNbDisks(COthelloBoard::EMPTY)-1
		),
		
		COthelloApp::GetInstance()->m_uiTimeLimit,

		x,y,

		(COthelloApp::GetInstance()->m_bShowThinking) ? (&callback) : 0
	);

	if (x!=-1 && y!=-1)
	{
		m_iLastX = x;
		m_iLastY = y;
	}

	if (COthelloApp::GetInstance()->m_bShowThinking)
	{
		DrawBackground(dc);
	}

	DrawPieces(dc,BOARD,false);
	DrawScoringTag(dc,BOARD);
	DrawPiece(dc,m_iLastX,m_iLastY,COLOR_LAST_MOVE,false);
}

/**************************************************************************************************************************************************************/

void COthelloView::Play(int x, int y)
{
	if ((!BOARD->CanPlay(COthelloBoard::WHITE)) && (!BOARD->CanPlay(COthelloBoard::BLACK)))
	{
		BOARD->ClearBoard();

		m_iLastX = -100;
		m_iLastY = -100;
	
		Draw(BOARD);
	}
	else if (BOARD->CanPlayPosition(COthelloBoard::WHITE, x, y))
	{
		BOARD->Play(COthelloBoard::WHITE,x,y);

		AutoPlay(COthelloBoard::BLACK);
	}
}

void COthelloView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int x = (int)((point.x - DX0) / DX);
	int y = (int)((point.y - DY0) / DX);

	Play(x,y);
	
	CView::OnLButtonUp(nFlags, point);
}

void COthelloView::OnRButtonUp(UINT nFlags, CPoint point)
{		
	if ((!BOARD->CanPlay(COthelloBoard::WHITE)) && (!BOARD->CanPlay(COthelloBoard::BLACK)))
	{
		BOARD->ClearBoard();

		m_iLastX = -100;
		m_iLastY = -100;
	
		Draw(BOARD);
	}
	else
	{
		AutoPlay(COthelloBoard::WHITE);
		AutoPlay(COthelloBoard::BLACK);
	}

	CView::OnRButtonUp(nFlags, point);
}

void COthelloView::OnFileNew()
{
	BOARD->ClearBoard();

	Draw(BOARD);
}

void COthelloView::OnFileOpen()
{
	CString newName;

	if (!COthelloApp::GetInstance()->DoPromptFileName(newName, AFX_IDS_OPENFILE, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
	{
		return;
	}

	BOARD->Load(newName.GetBuffer());

	Draw(BOARD);
}


void COthelloView::OnFileSave()
{
	CString newName("");

	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocument()->GetDocTemplate();
		ASSERT(pTemplate != NULL);

		if (!COthelloApp::GetInstance()->DoPromptFileName(newName, AFX_IDS_SAVEFILE, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
		{
			return;
		}
	}

	CWaitCursor wait;

	BOARD->Save(newName.GetBuffer());

	Draw(BOARD);

}

void COthelloView::OnFileSaveAs()
{
	CString newName("");

	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocument()->GetDocTemplate();
		ASSERT(pTemplate != NULL);

		if (!COthelloApp::GetInstance()->DoPromptFileName(newName, AFX_IDS_SAVEFILE, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
		{
			return;
		}
	}

	CWaitCursor wait;

	BOARD->Save(newName.GetBuffer());

	Draw(BOARD);
}

/**************************************************************************************************************************************************************/

COthelloView::~COthelloView()
{
	theApp.Release();
}

BOOL COthelloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COthelloView drawing

void COthelloView::OnDraw(CDC* /*pDC*/)
{
	COthelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	Draw(BOARD);
}


// COthelloView diagnostics

#ifdef _DEBUG
void COthelloView::AssertValid() const
{
	CView::AssertValid();
}

void COthelloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COthelloDoc* COthelloView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COthelloDoc)));
	return (COthelloDoc*)m_pDocument;
}
#endif //_DEBUG


// COthelloView message handlers
