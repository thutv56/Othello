// COthelloView.h : interface of the COthelloView class
//

#pragma once

class COthelloView : public CView 
{
protected: // create from serialization only
	COthelloView();
	DECLARE_DYNCREATE(COthelloView)

// Attributes
public:
	COthelloDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~COthelloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

/**************************************************************************************************************************************************************/

public:

	afx_msg void OnLButtonUp	(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp	(UINT nFlags, CPoint point);
	afx_msg void OnFileNew		();
	afx_msg void OnFileOpen		();
	afx_msg void OnFileSave		();
	afx_msg void OnFileSaveAs	();

	void DrawBackground		(CClientDC& dc);
	void DrawPieces			(CClientDC& dc, const COthelloBoard* pBoard,  bool bFast);
	void DrawPiece			(CClientDC& dc, int x, int y, COLORREF color, bool bFast);
	void DrawSearchingTag	(CClientDC& dc);
	void DrawScoringTag		(CClientDC& dc, const COthelloBoard* pBoard);

	void Draw				(const COthelloBoard*);

	void AutoPlay			(int ePlayer);
	void Play				(int x, int y);
	
	int m_iLastX;
	int m_iLastY;

/**************************************************************************************************************************************************************/

};

#ifndef _DEBUG  // debug version in COthelloView.cpp
inline COthelloDoc* COthelloView::GetDocument() const
   { return reinterpret_cast<COthelloDoc*>(m_pDocument); }
#endif

