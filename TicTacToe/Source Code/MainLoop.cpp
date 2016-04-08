#include"Tree.h"
#include<iostream>
#include<algorithm>
Board g_board;
bool human = false;
int counter = 0;
bool game_over = false;
vector<int> score_list;
vector<int> moves_list;
int g_score = -1;
int g_move;
struct MoveandScore
{
	int m_move;
	int m_score;
};
MoveandScore minimax(Board board, bool player);


int getMaxIndex(vector<int> p_inp)
{
	int max_index = 0;
	for (int i = 0; i < p_inp.size(); i++)
	{
		if (p_inp[max_index] < p_inp[i])
			max_index = i;
	}

	return max_index;
}
int getMinIndex(vector<int> p_inp)
{

	int min_index = 0;
	for (int i = 0; i < p_inp.size(); i++)
	{
		if (p_inp[min_index] > p_inp[i])
			min_index = i;
	}

	return min_index;
}
void evaluate_current_state(Board board);
void evaluate_current_State(Board board)
{
	

;
			MoveandScore ms_temp = minimax(board, false);
		

			
			
	
	
	g_move = ms_temp.m_move;
}
MoveandScore minimax(Board board, bool player)
{
	MoveandScore temp_best_score = { -1, 2 };
	if (board.isGameOver() || board.getFill() == 9)
	{
		temp_best_score.m_score = board.evaluate();
		return temp_best_score;
	}
	if (player)
	{
		temp_best_score.m_score = -2;
	}
	else
	{
		temp_best_score.m_score = +2;

	}

	
	
	
	 board.getEmptySpots();
	Board temp_board = board;
	vector<int>::iterator empty_spots_iterator = board.empty_spot_vector.begin();
	while (empty_spots_iterator != board.empty_spot_vector.end())
	{
		board.setPosition(*empty_spots_iterator, player);
		MoveandScore current_score = minimax(board, !player);

		

				if (!player)
				{
					if (current_score.m_score > temp_best_score.m_score)
					{
						temp_best_score.m_score = current_score.m_score;
						temp_best_score.m_move = *empty_spots_iterator;
					}
				}
				else
				{
					if (current_score.m_score < temp_best_score.m_score)
					{
						temp_best_score.m_score = current_score.m_score;
						temp_best_score.m_move = *empty_spots_iterator;
					}
				}
				empty_spots_iterator++;
			
	}

	board.empty_spot_vector.clear();
	

	return temp_best_score;
}

void displayBoard(Board board)
{
	
	for (int i = 0; i < 7;)
	{
		cout << "      " << board.getValue(i) << " | " << board.getValue(i + 1) << " | " << board.getValue(i+2) << endl;
		i += 3;
	}
	
}
void gameLoop()
{
	int temp;
	while (!g_board.isGameOver())
	{
		displayBoard(g_board);
		cin >> temp;
		g_board.setPosition(temp, true);
		

		evaluate_current_State(g_board);
		g_board.setPosition(g_move, false);
	}
	
}
int main(int argc, char** argv)
{
	int temp;

	bool quit = false;
	g_board.clear();
	int count = 0;
	char option;
	while (!quit)
	{
		gameLoop();
		g_board.clear();
		cout << "PLAY ANOTHER GAME?" << endl;
		cin >> option;
		if (option == 'y')
		{
			gameLoop();
		}
		else
		{
			quit = true;
		}
		
		
	}
	cout << "HELLO" << endl;

}