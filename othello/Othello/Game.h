#ifndef GAME_H
#define GAME_H

#include "Move.h"
#include "Position.h"
#include "Score.h"

class Game
{
private:
	Position m_position[];
	Game();
	void Reset();

	bool makeMove(Move m);
	bool takeBackMove();

	int getSquare(int x, int y);
	int getScore(int player);

	Move getLastMove();
	Move getMove(int i);

	bool moveIsLegal(Move m);
	bool moveIsPossible(int player);
	bool moveIsAtAllPossible();
	int getMoveNumber();
	int getWhoseTurn();
	Move TurnedByLastMove();

	bool Identical(Game g);
};

#endif