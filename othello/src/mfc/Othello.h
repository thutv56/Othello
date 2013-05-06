
#pragma once

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "COthelloBoard.h"

class COthelloApp : public CWinApp
{
public:

	COthelloApp();

	virtual BOOL InitInstance();

	void	Init		();
	void	Release		();

	static COthelloApp* GetInstance();

	afx_msg void OnAppOptions();
	DECLARE_MESSAGE_MAP()

public:

	COthelloBoard*	m_pOthelloBoard;
	UINT			m_uiLevel;
	UINT			m_uiTimeLimit;
	BOOL			m_bShowThinking;
};

extern COthelloApp theApp;