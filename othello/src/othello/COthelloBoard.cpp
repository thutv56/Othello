
//!
/**
 **************************************************************************************************************************************************************
 * Othello board class implementation
 **************************************************************************************************************************************************************
 * @file   COthelloBoard.cpp
 * @author AV (Antoine Villepreux)
 * @date   01/06/2003
 **************************************************************************************************************************************************************/

/**************************************************************************************************************************************************************
 * Includes
 **************************************************************************************************************************************************************/

#include <afxwin.h>
#include <cassert>
#include "COthelloBoard.h"
#include "CConfigFile.h"

/**************************************************************************************************************************************************************
 * Defines
 **************************************************************************************************************************************************************/

#define INF_SCORE	INT_MAX

/**************************************************************************************************************************************************************
 * Statics
 **************************************************************************************************************************************************************/

COthelloBoard::CPosArray					COthelloBoard::ms_positions;
COthelloBoard::CDirArray					COthelloBoard::ms_dirs = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };
CPool<COthelloBoard,COthelloBoard::SIZE>	COthelloBoard::ms_pool;



/**
 **************************************************************************************************************************************************************
 * Othello board initialization
 **************************************************************************************************************************************************************
 * @param ePlayer human player color
 * @return new board
 **************************************************************************************************************************************************************/
COthelloBoard* COthelloBoard::CreateInstance(EDisk ePlayer)
{
	COthelloBoard* pBoard = ms_pool.New();

	pBoard->ClearBoard();

	pBoard->m_pCallback		= 0;
	pBoard->m_iTimeLimit	= 0;
	pBoard->m_iTime			= 0;
	pBoard->m_eFirstPlayer	= ePlayer;
	pBoard->m_ePlayer		= ePlayer;

	return pBoard;
}

/**
 **************************************************************************************************************************************************************
 * Othello board recopy initialization
 **************************************************************************************************************************************************************
 * @param pBoard pointer to another board
 * @return new board
 **************************************************************************************************************************************************************/
COthelloBoard* COthelloBoard::CreateInstance(const COthelloBoard* pBoard)
{
	COthelloBoard* pClone = ms_pool.New();

	memcpy(&pClone->m_aaBoard[0][0], &pBoard->m_aaBoard[0][0], SIZE * sizeof(unsigned char));
	
	pClone->m_iTimeLimit		=	pBoard->m_iTimeLimit;
	pClone->m_iTime				=	pBoard->m_iTime;

	pClone->m_pCallback			=	pBoard->m_pCallback;
	pClone->m_ePlayer			=	pBoard->m_ePlayer;

	pClone->m_aiScore[WHITE]	=	pBoard->m_aiScore[WHITE];
	pClone->m_aiScore[BLACK]	=	pBoard->m_aiScore[BLACK];
	pClone->m_aiScore[EMPTY]	=	pBoard->m_aiScore[EMPTY];

	pClone->m_aiNbDisks[WHITE]	=	pBoard->m_aiNbDisks[WHITE];
	pClone->m_aiNbDisks[BLACK]	=	pBoard->m_aiNbDisks[BLACK];
	pClone->m_aiNbDisks[EMPTY]	=	pBoard->m_aiNbDisks[EMPTY];

	return pClone;
}

/**
 **************************************************************************************************************************************************************
 * Init an array of board positions
 **************************************************************************************************************************************************************
 * @return boolean anchor to help static call
 **************************************************************************************************************************************************************/
bool COthelloBoard::InitPositions()
{
	int i=0;

	CPosArray b;

	for(int x=0; x<COthelloBoard::WIDTH;  ++x)
	for(int y=0; y<COthelloBoard::HEIGHT; ++y)
	{
		b[i].x = x;
		b[i].y = y;

		++i;
	}

	/**
	 *	0  8 16 24 32 40 48 56
	 *	1  9 17 25 33 41 49 57
	 *	2 10 18 26 34 42 50 58
	 *	3 11 19 27 35 43 51 59
	 *	4 12 20 28 36 44 52 60
	 *	5 13 21 29 37 45 53 61
	 *	6 14 22 30 38 46 54 62
	 *	7 15 23 31 39 47 55 63
	 */

	// The positions are sorted in order of importance

	int p[COthelloBoard::SIZE] = 
	{
		 0,  7, 63, 56, 18, 21, 45, 42,  2,  5, 23, 47, 61, 58, 40, 16,
		 3,  4, 31, 39, 60, 59, 32, 24, 19, 20, 29, 37, 44, 43, 34, 26,
		11, 12, 30, 38, 52, 51, 33, 25, 10, 13, 22, 46, 53, 50, 41, 17,
		 1,  6, 15, 55, 62, 57, 48,  8,  9, 14, 54, 49, 27, 28, 36, 35
	};

	// Check if we didnt't forget a position (DEBUG)

	int iVerify = 0;

	for(int k=0; k<COthelloBoard::SIZE; ++k)
	for(int i=0; i<COthelloBoard::SIZE; ++i)
	{
		if (p[i]==iVerify)
		{
			++iVerify;
			break;
		}
	}

	assert(iVerify == COthelloBoard::SIZE);

	for(int i=0; i<COthelloBoard::SIZE; ++i)
	{
		ms_positions[i].x = b[p[i]].x;
		ms_positions[i].y = b[p[i]].y;
	}

	return true;
}

/**
 **************************************************************************************************************************************************************
 * Clean othello board
 **************************************************************************************************************************************************************/
void COthelloBoard::ClearBoard()
{
	static bool bDummy = InitPositions();

	// Init scores

	m_aiScore	[BLACK] = 0;
	m_aiScore	[WHITE] = 0;
	m_aiScore	[EMPTY] = 0;

	m_aiNbDisks	[BLACK] = 0;
	m_aiNbDisks	[WHITE] = 0;
	m_aiNbDisks	[EMPTY] = SIZE;

	// Empty board

	for(int x=0; x<WIDTH;  ++x)
	for(int y=0; y<HEIGHT; ++y)
	{
		m_aaBoard[x][y]   = EMPTY;
		m_aiScore[EMPTY] += GetScore(x,y);
	}

	// Populate board

	int x0 = ((int)(WIDTH / 2)) - 1;

	SetDisk(x0,   x0,   WHITE);
	SetDisk(x0+1, x0,   BLACK);
	SetDisk(x0+1, x0+1, WHITE);
	SetDisk(x0,   x0+1, BLACK);

	m_ePlayer  = m_eFirstPlayer;
}

/**
 **************************************************************************************************************************************************************
 * Can this player play at the given position ?
 **************************************************************************************************************************************************************
 * @param ePlayer player 
 * @param x x-coordinate
 * @param y y-coordinate
 * @return true if playable
 **************************************************************************************************************************************************************/
bool COthelloBoard::CanPlayPosition(EDisk ePlayer, int x, int y) const
{
	if (!IsFree(x,y))
	{
		return false;
	}

	for(int iDir=0; iDir<8; ++iDir)
	{
		if (CanPlayDirection(ePlayer, x, y, ms_dirs[iDir].x, ms_dirs[iDir].y))
		{
			return true;
		}
	}

	return false;
}

/**
 **************************************************************************************************************************************************************
 * Does this player score in a given direction when playing at the given position ?
 **************************************************************************************************************************************************************
 * @param ePlayer player 
 * @param x0 x-coordinate
 * @param y0 y-coordinate
 * @param dx dx-direction vector
 * @param dy dy-direction vector
 * @return true if playable
 **************************************************************************************************************************************************************/
bool COthelloBoard::CanPlayDirection(EDisk ePlayer, int x0, int y0, int dx, int dy) const
{
	int iCondition = 0;

	int x = x0;
	int y = y0;

	while (iCondition < 2)
	{
		x += dx;
		y += dy;
		
		if (!IsInside(x,y))
		{
			return false;
		}

		if (GetDisk(x,y)==GetOpponent(ePlayer))
		{
			iCondition = 1;
			continue;
		}

		if (GetDisk(x,y)==ePlayer)
		{
			++iCondition;
			break;
		}

		break;
	}

	return (iCondition == 2);
}

/**
 **************************************************************************************************************************************************************
 * Play at the given position
 **************************************************************************************************************************************************************
 * @param ePlayer player 
 * @param x0 x-coordinate
 * @param y0 y-coordinate
 * @return true if playable
 **************************************************************************************************************************************************************/
bool COthelloBoard::Play(EDisk ePlayer, int x0, int y0)
{
	if (ePlayer != m_ePlayer)
	{
		return false;
	}

	if (!IsFree(x0,y0))
	{
		return false;
	}

	bool bHasPlayed = false;

	for(int iDir=0; iDir<8; ++iDir)
	{
		int dx = ms_dirs[iDir].x;
		int dy = ms_dirs[iDir].y;

		if (!CanPlayDirection(ePlayer,x0,y0,dx,dy))
		{
			continue;
		}

		bHasPlayed = true;

		SetDisk(x0,y0,ePlayer);

		int x = x0 + dx;
		int y = y0 + dy;

		while (GetDisk(x,y) != ePlayer)
		{
			SetDisk(x,y,ePlayer);

			x += dx;
			y += dy;
		}
	}

	if (bHasPlayed)
	{
		if (CanPlay(GetOpponent(ePlayer)))
		{
			m_ePlayer = GetOpponent(ePlayer);
		}

		if (m_pCallback)
		{
			(*m_pCallback)(this);
		}

		return true;
	}

	return false;
}

/**
 **************************************************************************************************************************************************************
 * Can this player play this round
 **************************************************************************************************************************************************************
 * @param ePlayer player
 * @return true if playable
 **************************************************************************************************************************************************************/
bool COthelloBoard::CanPlay(EDisk ePlayer) const
{
	for(int i=0; i<SIZE; ++i)
	{
		if (CanPlayPosition(ePlayer,ms_positions[i].x,ms_positions[i].y))
		{
			return true;
		}
	}

	return false;
}

/**
 **************************************************************************************************************************************************************
 * Let computer play
 **************************************************************************************************************************************************************
 * @param ePlayer player
 * @param iDepth search depth
 * @param iTimeLimit maximum time to give a solution
 * @param x x-coordinate of played position or -1 if cannot play
 * @param y y-coordinate of played position or -1 if cannot play
 * @param pCallback called for each search iteration
 **************************************************************************************************************************************************************/
void COthelloBoard::AutoPlay(EDisk ePlayer, int iDepth, int iTimeLimit, int& x, int& y, CCallback* pCallback)
{
	m_pCallback = pCallback;

	while ((ePlayer == m_ePlayer) && !IsGameOver())
	{
		m_iTimeLimit	= iTimeLimit;
		m_iTime			= GetTickCount();

		DoAutoPlay(ePlayer, iDepth, iTimeLimit, x, y);
	}

	m_pCallback = 0;
}

/**
 **************************************************************************************************************************************************************
 * Let computer play.
 * Implementation details
 **************************************************************************************************************************************************************
 * @param ePlayer player
 * @param iDepth search depth
 * @param iTimeLimit maximum time to give a solution
 * @param x x-coordinate of played position or -1 if cannot play
 * @param y y-coordinate of played position or -1 if cannot play
 **************************************************************************************************************************************************************/
void COthelloBoard::DoAutoPlay(EDisk ePlayer, int iDepth, int iTimeLimit, int& x, int& y)
{
	int iPosition	= -1;
    int iBestScore	= -INF_SCORE;

	x = -1;
	y = -1;

	for(int i=0; i<SIZE; ++i)
	{
		COthelloBoard* pNextBoard = CreateInstance(this);

		if (pNextBoard->Play(ePlayer,ms_positions[i].x,ms_positions[i].y))
		{
			int iScore = pNextBoard->Max(ePlayer, -INF_SCORE, INF_SCORE, iDepth);

			if (iScore >= iBestScore)
			{
				iBestScore	= iScore;
				iPosition	= i;
			}
		}

		DeleteInstance(pNextBoard);
	}

	if (iPosition != -1)
	{
		x = ms_positions[iPosition].x;
		y = ms_positions[iPosition].y;

		if (!Play(ePlayer, x, y))
		{
			assert(0);
		}
	}
}

/**
 **************************************************************************************************************************************************************
 * Min/Max algorithm
 **************************************************************************************************************************************************************
 * @param ePlayer player
 * @param iDepth current depth
 * @return score
 **************************************************************************************************************************************************************/
int COthelloBoard::Max(EDisk ePlayer, int iA, int iB, int iDepth)
{
	if (IsTimeOut(iDepth))
	{
		return GetScore(ePlayer);
	}

	if (IsGameOver())
	{
		int iDiff = GetNbDisks(ePlayer) - GetNbDisks(GetOpponent(ePlayer));
        
		return (iDiff>0) ? INF_SCORE : (iDiff<0) ? -INF_SCORE : 0;
	}

	COthelloBoard* pNextBoard = CreateInstance(this);
		
	int iBestScore = -INF_SCORE;

	for(int i=0; i<SIZE; ++i)
	{
		if (pNextBoard->Play(GetOpponent(ePlayer), ms_positions[i].x, ms_positions[i].y))
		{
			int iScore = pNextBoard->Min(GetOpponent(ePlayer), iA, iB, iDepth-1);

			if (iScore > iBestScore)
			{
				iBestScore = iScore;
			}

			DeleteInstance(pNextBoard);
			pNextBoard = CreateInstance(this);
		}
	}

	DeleteInstance(pNextBoard);
	
	return -iBestScore;
}

/**
 **************************************************************************************************************************************************************
 * Min/Max algorithm
 **************************************************************************************************************************************************************
 * @param ePlayer player
 * @param iDepth current depth
 * @return score
 **************************************************************************************************************************************************************/
int COthelloBoard::Min(EDisk ePlayer, int iA, int iB, int iDepth)
{
	COthelloBoard* pNextBoard = CreateInstance(this);
		
	int iBestScore = -INF_SCORE;

	for(int i=0; i<SIZE; ++i)
	{
		if (pNextBoard->Play(GetOpponent(ePlayer), ms_positions[i].x, ms_positions[i].y))
		{
			int iScore = pNextBoard->Max(GetOpponent(ePlayer), iA, iB, iDepth-1);

			if (iScore > iBestScore)
			{
				iBestScore = iScore;
			}

			DeleteInstance(pNextBoard);
			pNextBoard = CreateInstance(this);
		}
	}

	DeleteInstance(pNextBoard);
	
	return -iBestScore;
}

/**
 **************************************************************************************************************************************************************
 * Is it time to stop search ?
 **************************************************************************************************************************************************************
 * @param current search depth
 * @return true id time to stop the search
 **************************************************************************************************************************************************************/
bool COthelloBoard::IsTimeOut(int iDepth) const
{
	if (iDepth <= 0)
	{
		return true;
	}

	if ((int)(GetTickCount()-m_iTime) > m_iTimeLimit)
	{
		return true;
	}

	return false;
}

/**
 **************************************************************************************************************************************************************
 * Set disk at given position.
 * No verification is made on the coordinates and their validity
 **************************************************************************************************************************************************************
 * @param x board x-coordinates
 * @param y board y-coordinates
 * @param eDisk disk
 **************************************************************************************************************************************************************/
void COthelloBoard::SetDisk(int x, int y, EDisk eDisk)
{
	m_aiScore	[m_aaBoard[x][y]] -= GetScore(x,y);
	m_aiNbDisks	[m_aaBoard[x][y]] -= 1;

	m_aaBoard[x][y] = eDisk;

	m_aiScore	[eDisk] += GetScore(x,y);
	m_aiNbDisks	[eDisk] += 1;
}

/**
 **************************************************************************************************************************************************************
 * Save current board to file
 **************************************************************************************************************************************************************
 * @param filename 
 **************************************************************************************************************************************************************/
void COthelloBoard::Save(const char* filename)
{
	CConfigFile cfg(filename, CConfigFile::WRITE);

	cfg.Set("CURRENT_PLAYER",	(int)m_ePlayer	);
	cfg.Set("CURRENT_TIME",		m_iTime			);
	cfg.Set("TIME_LIMIT",		m_iTimeLimit	);

	cfg.Set("SCORE0",			m_aiScore[0]	);
	cfg.Set("SCORE1",			m_aiScore[1]	);
	cfg.Set("SCORE2",			m_aiScore[2]	);
	
	cfg.Set("NBDISKS0",			m_aiNbDisks[0]	);
	cfg.Set("NBDISKS1",			m_aiNbDisks[1]	);
	cfg.Set("NBDISKS2",			m_aiNbDisks[2]	);
	
	for(int x=0; x<WIDTH;  ++x)
	for(int y=0; y<HEIGHT; ++y)
	{
		char strKey[1024];
		sprintf(strKey,"%dx%d",x,y);
		cfg.Set(strKey,(int)m_aaBoard[x][y]);
	}
}

/**
 **************************************************************************************************************************************************************
 * Load board from file
 **************************************************************************************************************************************************************
 * @param filename
 **************************************************************************************************************************************************************/
void COthelloBoard::Load(const char* filename)
{
	CConfigFile cfg(filename, CConfigFile::READ);

	m_ePlayer		= (EDisk)	cfg.Get<int>("CURRENT_PLAYER");
	m_iTime			=			cfg.Get<int>("CURRENT_TIME");
	m_iTimeLimit	=			cfg.Get<int>("TIME_LIMIT");

	m_aiScore[0]	=			cfg.Get<int>("SCORE0");
	m_aiScore[1]	=			cfg.Get<int>("SCORE1");
	m_aiScore[2]	=			cfg.Get<int>("SCORE2");

	m_aiNbDisks[0]	=			cfg.Get<int>("NBDISKS0");
	m_aiNbDisks[1]	=			cfg.Get<int>("NBDISKS1");
	m_aiNbDisks[2]	=			cfg.Get<int>("NBDISKS2");

	for(int x=0; x<WIDTH;  ++x)
	for(int y=0; y<HEIGHT; ++y)
	{
		char strKey[1024];
		sprintf(strKey,"%dx%d",x,y);
		m_aaBoard[x][y] = cfg.Get<int>(strKey);
	}
}

/**************************************************************************************************************************************************************/


