#include"Board.h"
Board::Board()
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = EMPTY;
	}
	fill  = 0;
	empty = 9;
}
//Check if a given position is empty
bool Board::isEmpty(int index)
{
	return (board[index] == 0);

}
//Return the value stored in a position
int Board::getValue(int index)
{
	return board[index];
}
//Returns true if there is a victory or a draw.
bool Board::isGameOver()
{
	if (checkWin(HUMAN) || checkWin(COMPUTER) || (fill >= 9))
	{
		return true;
	}
	else
		return false;
}
int Board::getEmpty()
{
	
	return empty;
}
int Board::getFill()
{
	
	return fill;
}
//Clears a given position
void Board::clearPosition(int i)
{
	board[i] = 0;
	empty++;
	fill--;
}
//Overlaoded operator= so that assignment of a board can be done using =
void Board::operator=(Board p_board)
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = p_board.getValue(i);
	}
	empty = p_board.getEmpty();
	fill = p_board.getFill();


}
//Check if there is a victory for human or a computer
bool Board::checkWin(PLAYER player)
{
	if (player == HUMAN)
	{
		if ((board[0] + board[1] + board[2]) == 3 ||
			(board[3] + board[4] + board[5]) == 3 ||
			(board[6] + board[7] + board[8]) == 3 ||
			(board[0] + board[3] + board[6]) == 3 ||
			(board[1] + board[4] + board[7]) == 3 ||
			(board[2] + board[5] + board[8]) == 3 ||
			(board[0] + board[4] + board[8]) == 3 ||
			(board[2] + board[4] + board[6]) == 3)
		{
			return true;
		}
		else
			return false;


	}
	else if (player == COMPUTER)
	{
		if ((board[0] + board[1] + board[2]) == 12 ||
			(board[3] + board[4] + board[5]) == 12 ||
			(board[6] + board[7] + board[8]) == 12 ||
			(board[0] + board[3] + board[6]) == 12 ||
			(board[1] + board[4] + board[7]) == 12 ||
			(board[2] + board[5] + board[8]) == 12 ||
			(board[0] + board[4] + board[8]) == 12 ||
			(board[2] + board[4] + board[6]) == 12)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
//Clear the board.
void Board::clear()
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = EMPTY;
	}
	fill =  0;
	empty = 9;
}
//Return a high score if computer wins ( used in Minimax)
int Board::evaluate()
{
	
	if (checkWin(COMPUTER))
	{
		return +1;
	}
	else if (checkWin(HUMAN))
	{
		return -1;
	}
	else
		return 0;
	
}
//Sets a position of the board with a given player's id.
void Board::setPosition(int index, int Player_id)
{
	if (isEmpty(index))
	{
		if (Player_id == 1)
		{
			board[index] = COMPUTER;
		}
		else if (Player_id == -1)
		{
			board[index] = HUMAN;
		}
		fill++;
		empty--;
	}
}

/*
The following function returns an integer representation of a victor.
Lines 1,2,3 -> These correspond to horizontal victory lines
Lines 4,5,6 -> These correspond to vertical victory lines
Lines 7,8 -> These correspond to diagonal victory lines

*/
int Board::getLineNo()
{
	if (checkWin(COMPUTER))
	{

		if ((board[0] + board[1] + board[2]) == 12)
		{
			return 1;
		}
		else if ((board[3] + board[4] + board[5]) == 12)
		{
			return 2;
		}
		else if ((board[6] + board[7] + board[8]) == 12)
		{
			return 3;
		}
		else if ((board[0] + board[3] + board[6]) == 12)
		{
			return 4;
		}
		else if ((board[1] + board[4] + board[7]) == 12)
		{
			return 5;
		}
		else if ((board[2] + board[5] + board[8]) == 12)
		{
			return 6;
		}
		else if ((board[0] + board[4] + board[8]) == 12)
		{
			return 7;
		}

		else if ((board[2] + board[4] + board[6]) == 12)
		{
			return 8;
		}
	}
	else
		return -1;
	
	
}