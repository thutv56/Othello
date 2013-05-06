
/**************************************************************************************************************************************************************/

class CBrushToggle
{
public:

	CBrushToggle(CClientDC* pDC, const COLORREF& color)
	{
		m_pDC = pDC;
		m_brush1.CreateSolidBrush(color);
		m_pTempBrush = (m_originalBrush.FromHandle((HBRUSH)m_pDC->SelectObject(m_brush1)));
	}

	~CBrushToggle()
	{
		m_pDC->SelectObject(&m_originalBrush);
	}

private:
	
	CClientDC*	m_pDC;
	CBrush  	m_brush1;
	CBrush  	m_originalBrush;
	CBrush* 	m_pTempBrush;
};

/**************************************************************************************************************************************************************/

class CPenToggle
{
public:

	CPenToggle(CClientDC* pDC, int iWidth, const COLORREF& color)
	{
		m_pDC = pDC;
		m_pen1.CreatePen(PS_SOLID,iWidth,color);
		m_pTempPen = m_originalPen.FromHandle((HPEN)m_pDC->SelectObject(m_pen1));
	}

	~CPenToggle()
	{
		m_pDC->SelectObject(m_pTempPen);
	}

private:
	
	CClientDC*	m_pDC;
	CPen  		m_pen1;
	CPen  		m_originalPen;
	CPen* 		m_pTempPen;
};

/**************************************************************************************************************************************************************/
