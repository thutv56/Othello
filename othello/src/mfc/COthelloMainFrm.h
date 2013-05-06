// COthelloMainFrm.h : interface of the COthelloMainFrame class
//


#pragma once
class COthelloMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	COthelloMainFrame();
	DECLARE_DYNCREATE(COthelloMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~COthelloMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


