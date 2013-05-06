#ifndef SCORE_H
#define SCORE_H

class Score
{
private:
	int m_score[2];
public:
	const int NOBODY = 0;
	const int WHITE = 1;
	const int BLACK = 2;

	Score();												
	Score(int whiteScore, int blackScore);							

	static int getOpponent(int player);						

	void setScore(int player, int score);					
	int getScore(int player);								

	const void addScore(int player, int amount);			
	const void substractScore(int player, int amount);		
};

#endif
