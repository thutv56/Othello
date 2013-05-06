
/**
 **************************************************************************************************************************************************************
 * Othello board class
 **************************************************************************************************************************************************************
 * @file   COthelloBoard.h
 * @author AV (Antoine Villepreux)
 * @date   01/06/2003
 **************************************************************************************************************************************************************/

#ifndef COTHELLOBOARD_H
#define COTHELLOBOARD_H

/**************************************************************************************************************************************************************
 * Includes
 **************************************************************************************************************************************************************/

#include "CPool.h"

/**
 **************************************************************************************************************************************************************
 * Othello board
 **************************************************************************************************************************************************************/
class COthelloBoard
{
/**************************************************************************************************************************************************************
 * Public interface
 **************************************************************************************************************************************************************/

public:

	enum
	{
		WIDTH	= 8,
		HEIGHT	= 8,
		SIZE	= WIDTH*HEIGHT
	};

	enum EDisk
	{
		EMPTY=0,
		BLACK,
		WHITE
	};

	struct CCallback
	{
		virtual void operator()(const COthelloBoard*) = 0;
	};

public:
	
	static			COthelloBoard*	CreateInstance	(EDisk eOwner = WHITE);
	static			COthelloBoard*	CreateInstance	(const COthelloBoard*);
	static	inline	void			DeleteInstance	(COthelloBoard*&);

public:

			void	Save				(const char* filename);
			void	Load				(const char* filename);

			void	ClearBoard			();

			void	AutoPlay			(EDisk ePlayer, int iDepth, int iTimeLimit, int& x, int& y, CCallback* pCallback=0);
			bool	Play				(EDisk ePlayer, int,int);

	inline	int		GetNbDisks			(EDisk ePlayer)				const;
	inline	EDisk	GetDisk				(               int,int)	const;

			bool	CanPlay				(EDisk ePlayer)				const;
			bool	CanPlayPosition		(EDisk ePlayer, int,int)	const;
	inline	bool	IsInside			(               int,int)	const;

	inline	bool	IsGameOver			()							const;
	
private:

/**************************************************************************************************************************************************************
 * Private interface
 **************************************************************************************************************************************************************/

private:
							COthelloBoard	(const COthelloBoard&);
	const COthelloBoard&	operator =		(const COthelloBoard&);

private:

	inline				COthelloBoard		();
	inline	virtual    ~COthelloBoard		();

	static	bool		InitPositions		();

	inline	bool		CanPlayDirection	(EDisk ePlayer, int,int,int,int)	const;
			bool		IsFree				(int,int)							const;
			
			void		DoAutoPlay			(EDisk ePlayer, int iDepth, int iTimeLimit, int& x, int& y);
	static
	inline	EDisk		GetOpponent			(EDisk);

	static 
	inline	int			GetScore			(int,int);
	inline	int			GetScore			(EDisk)	const;

			void		SetDisk				(int,int, EDisk);

			int			Min					(EDisk ePlayer, int iA, int iB, int iDepth);
			int			Max					(EDisk ePlayer, int iA, int iB, int iDepth);

			bool		IsTimeOut			(int)	const;

private:

	typedef	struct { int x,y; }			CPos;
	typedef	CPos						CPosArray	[SIZE];
	typedef	CPos						CDirArray	[8];
	
	static CPosArray					ms_positions;
	static CDirArray					ms_dirs;
    static CPool<COthelloBoard,SIZE>	ms_pool;

	friend class CPool<COthelloBoard,SIZE>;

private:

	CCallback*		m_pCallback;
	unsigned char	m_aaBoard[WIDTH][HEIGHT];
	int				m_aiScore[3];
	int				m_aiNbDisks[3];
	EDisk			m_eFirstPlayer;
	EDisk			m_ePlayer;
	int				m_iTime;
	int				m_iTimeLimit;
};

/**************************************************************************************************************************************************************/

#include "COthelloBoard.inl"

/**************************************************************************************************************************************************************/

#endif

