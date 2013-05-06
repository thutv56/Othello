// COthelloDoc.h : interface of the COthelloDoc class
//


#pragma once

class COthelloDoc : public CDocument
{
protected: // create from serialization only
	COthelloDoc();
	DECLARE_DYNCREATE(COthelloDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~COthelloDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


