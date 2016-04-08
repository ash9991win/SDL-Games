/**
TICTACTOE 
The following class processes the main board
Author: Ashwin Sankaranarayanan
*/
#ifndef BOARD_H
#define BOARD_H
#include<vector>
using namespace std;

enum PLAYER { EMPTY, HUMAN, COMPUTER = 4 };
class Board
{
public:
	/*
	board --> An array storing the information about the board
	empty  -> The number of empty cells
	fill ---> The number of occupied cells
	*/
	int board[9];
	int empty;
	int fill;


	Board();
	void operator=(Board r_board);
	void setPosition(int index, int player_id);
	void clearPosition(int index);
	int getEmpty();
	int getFill();
	bool isEmpty(int index);
	bool checkWin(PLAYER player);
	void clear();
	bool isGameOver();
	int getValue(int index);
	int evaluate();
	int getLineNo();

};
#endif