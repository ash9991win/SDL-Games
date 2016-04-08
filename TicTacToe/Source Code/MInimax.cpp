#include"Minimax.h"
//The main algorithm for calculating the next move
int Minimax::minimax(Board board, int player) {

	//if the game is over ( either player has won or it results in a draw) return the calculated score
	if (board.isGameOver())
	{
		return (board.evaluate() * player);
	}
	
	int temp_move = -1;
	int temp_score = -2;

	for (int i = 0; i < 9; i++) {
		if (board.isEmpty(i))
		{
			//if the board is not empty, set the current player's mark in that position and call minimax on the newly generated board. This section repeats recursively till a final score is obtained.
			board.setPosition(i, player);
			int current_score = -minimax(board, player*-1);

			//Choose the maximum score among the resultant scores and the corresponding move.
			if (current_score > temp_score) {
				temp_score = current_score;
				temp_move = i;
			}
			//Reset the changes
			board.clearPosition(i);
		}
	}
	if (temp_move == -1) return 0;
	return temp_score;
	
}

void Minimax::evaluate_current_state(Board board) {
	int temp_move = -1;
	int temp_score = -2;
	//For  a current board, generate the Computer's turn for each and every empty square and calculate the minimax for it.
	for (int i = 0; i < 9; ++i) {
		if (board.isEmpty(i))
		{
			board.setPosition(i, 1);
			int current_score = -minimax(board, -1);
			board.clearPosition(i);
			//Choose the highest score and its corresponding move.
			if (current_score > temp_score) {
				temp_score = current_score;
				temp_move = i;
			}
		}
	}
	//Set the final move
	g_move = temp_move;
}
//Returns the move to be made
int Minimax::getFinalMove()
{
	return g_move;
}
//Sets the board 
void Minimax::SetBoard(Board board)
{
	g_board = board;
}