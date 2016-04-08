/**
TICTACTOE
This class is used to display the Board
Author: Ashwin Sankaranarayanan
*/
#ifndef BOARD_DISPLAY
#define BOARD_DISPLAY
#include"Board.h"
#include"ResourceManager.h"
#include<vector>

using namespace std;
//The following structure is used as a easier way to implement a player's data. It has a texture for holding the image, a render flag and coordinates.
struct Player
{
	SDL_Texture* player_texture;
	bool render_flag;
	SDL_Point coord;
};
//The following class displays the board
class DisplayBoard
{
private:
	/*
	final_board   -> The board data
	mresourceloader     -> A ResourceLoader object used to obtain the SDL_Texture for various images
	grenderer   ------> The renderer to which to draw the textures
	playO_texture     -> This is the texture for the Computer. 
	playX_texture ----> This is the texture of the player.
	board_texture   ----> The texture of the board.
	player1_texture,player2_texture ----> Holds the textures of the two players.
	
	
	*/
	Board final_board;
	ResourceLoader mresourceloader;
	SDL_Renderer* grenderer;
	vector<Player> playO_texture;
	vector<Player> playX_texture;
	SDL_Texture* board_texture;
	SDL_Texture* player1_texture;
	SDL_Texture* player2_texture;

public:
	
	void setBoard(Board board);
	void updateBoard(Board board);
	void drawBoard();
	void clearBoard();
	void setRenderer(SDL_Renderer* p_renderer);
	~DisplayBoard();





};
#endif