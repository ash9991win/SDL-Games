/**
TICTACTOE
This class is used to use Minimax Algorithm for computing the next valid move
Author: Ashwin Sankaranarayanan
*/
#ifndef MINIMAX_H
#define MINIMAX_H
#include"Board.h"
class Minimax
{
private:
	/*
	g_board ---> The board data
	g_move   ---> The final move
	*/
	Board g_board;
	int g_move;
public:
	
	void SetBoard(Board board);
	int minimax(Board board, int player);
	void evaluate_current_state(Board board);
	int getFinalMove();
};

#endif