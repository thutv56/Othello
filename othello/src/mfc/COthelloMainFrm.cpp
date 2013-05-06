// COthelloMainFrm.cpp : implementation of the COthelloMainFrame class
//

#include "stdafx.h"
#include "Othello.h"

#include "COthelloMainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COthelloMainFrame

IMPLEMENT_DYNCREATE(COthelloMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(COthelloMainFrame, CFrameWnd)
END_MESSAGE_MAP()


// COthelloMainFrame construction/destruction

COthelloMainFrame::COthelloMainFrame()
{
	// TODO: add member initialization code here
}

COthelloMainFrame::~COthelloMainFrame()
{
}


BOOL COthelloMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX;

	return TRUE;
}


// COthelloMainFrame diagnostics

#ifdef _DEBUG
void COthelloMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void COthelloMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// COthelloMainFrame message handlers

