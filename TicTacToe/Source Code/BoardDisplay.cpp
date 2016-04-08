#include"BoardDisplay.h"
//The following function displays the board.
void DisplayBoard::drawBoard()
{
	//Render the board 
	SDL_RenderCopy(grenderer, board_texture, NULL, NULL);
	//Render the Computer's textures for all the moves made
	for (int i = 0; i < playO_texture.size(); i++)
	{
		SDL_Rect dest_cord;
		dest_cord.x = playO_texture[i].coord.x;
		dest_cord.y = playO_texture[i].coord.y;
		dest_cord.w = 150;
		dest_cord.h = 150;
		SDL_RenderCopy(grenderer, playO_texture[i].player_texture, NULL, &dest_cord);
	}
	//Render the Player's textures for all the moves made
	for (int i = 0; i < playX_texture.size(); i++)
	{
		SDL_Rect dest_cord;
		dest_cord.x = playX_texture[i].coord.x;
		dest_cord.y = playX_texture[i].coord.y;
		dest_cord.w = 150;
		dest_cord.h = 150;
		SDL_RenderCopy(grenderer, playX_texture[i].player_texture, NULL, &dest_cord);
	}
}

void DisplayBoard::setBoard(Board board)
{
	//sets the current board.
	final_board = board;
}
void DisplayBoard::setRenderer(SDL_Renderer* prenderer)
{
	//Set the renderer and load all the textures.
	grenderer = prenderer;
	player1_texture = mresourceloader.loadimage(grenderer, "Assets/images/playX.png");
	player2_texture = mresourceloader.loadimage(grenderer, "Assets/images/playO.png");
	board_texture = mresourceloader.loadimage(grenderer, "Assets/images/tictactoe.png");
	final_board.clear();
}
//The following function is used to update the current positions of a board.
void DisplayBoard::updateBoard(Board board)
{
	
	//Set the players' textures 
	final_board = board;
	int posx = 50, posy = 20;
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0 && i!= 0)
		{
			posx = 50;
			posy += 200;
		}
		if (!final_board.isEmpty(i))
		{
			if (final_board.getValue(i) == 1)
			{
				Player temp_player = { player1_texture, true, { posx, posy } };
				playO_texture.push_back(temp_player);
			}
			if (final_board.getValue(i) == 4)
			{
				Player temp_player = { player2_texture, true, { posx, posy } };
				playO_texture.push_back(temp_player);
			}
		}
		posx += 200;

	}

}
//Clear the board and the player textures

void DisplayBoard::clearBoard()
{
	final_board.clear();
	playO_texture.clear();
	playX_texture.clear();
}
//Destroy the textures used
DisplayBoard::~DisplayBoard()
{
	SDL_DestroyTexture(player1_texture);
	SDL_DestroyTexture(player2_texture);
	SDL_DestroyTexture(board_texture);
	playO_texture.clear();
	playX_texture.clear();
	SDL_DestroyRenderer(grenderer);
}