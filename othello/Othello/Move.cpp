#include <iostream>
#include "Move.h"

Move :: Move()
{
	m_x = 0;
	m_y = 0;
}

Move :: Move(const Move &m)
{
	m_x = m.m_x;
	m_y = m.m_y;
	m_player = m.m_player;
}

Move :: Move(int x, int y, int player)
{
	m_x = x;
	m_y = y;
	m_player = player;
}

int Move :: getX()
{
	return m_x;
}

int Move :: getY()
{
	return m_y;
}

int Move :: getPlayer()
{
	return m_player;
}