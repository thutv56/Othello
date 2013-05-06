#ifndef POSITION_H
#define POSITION_H

#include "Move.h"
#include "Score.h"

class Position
{
private:
	int m_board[7][7];
	Move m_lastmove;
	Score m_score;
public:
	Position();
	Position(Position p, Move m);

	int getSquare(int x, int y);				
	int getScore(int player);					

	Move getLastMove();							

	bool moveIsLegal(Move m);						
	bool moveIsPossible(Move m);					
	bool moveIsAtAllPossible();
};

#endif