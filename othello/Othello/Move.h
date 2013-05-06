#ifndef MOVE_H
#define MOVE_H

class Move
{
private:
	int m_x, m_y;
	int m_player;
public:
	Move();
	//Move(Move m);
	Move(int x, int y, int player);

	int getX();								
	int getY();								
	int getPlayer();						
};

#endif