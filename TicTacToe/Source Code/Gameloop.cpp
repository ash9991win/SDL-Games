#include<iostream>
#include"Board.h"
#include"Minimax.h"
#include"MouseHandler.h"
#include"ResourceManager.h"
#include"BoardDisplay.h"
#include<sstream>
//The main game loop
using namespace std;
SDL_Window* gwindow;			//Global window variable
SDL_Renderer* grenderer;		// Global renderer variable
SDL_Texture* gboard_texture;	//Global board texture
SDL_Texture* gcursor_texture;	// Global cursor texture
SDL_Texture* line_texture;		//Line texture ( the image to display when there is a win)

DisplayBoard display_board;		//The DisplayBoard variable
ResourceLoader cursor_loader;	// The common resource loader to load textures.
Board g_board;					// The global board
 int MAX_WIDTH = 640;   
 int MAX_HEIGHT = 640;
Minimax g_minimax;				// The minimax variable
TTF_Font* gfont;				// The Global font
SDL_Color gcolor;				//The global color
MouseHandler g_mousehandler;	//The global mousehanlder


//The following struct is used for storing data about the line to be drawn when there is a win
struct Line_Coord
{
	SDL_Rect line_rect;
	double line_angle;
	SDL_Point rotate_point;
};

//Initialize all systems
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_JPG | IMG_INIT_PNG))
		{
			TTF_Init();
			gwindow = SDL_CreateWindow("TIC TAC TOE", 300, 200, MAX_WIDTH, MAX_HEIGHT, SDL_WINDOW_SHOWN);    //Create the window
			
			SDL_GetWindowSize(gwindow, &MAX_WIDTH, &MAX_HEIGHT);   //Get the window dimensions
			if (gwindow != NULL)
			{
				grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_Surface* icon_surface = IMG_Load("Assets/images/playO.png");   //Set the window icon
				SDL_SetWindowIcon(gwindow, icon_surface);
				if (grenderer != NULL)
					return true;
				else
					return false;
			}
			else
				return false;


		}
		else
			return false;
	}
	else
		return false;

}

//Load the fonts and colors
void loadfont()
{
	gfont = TTF_OpenFont("Assets/fonts/arial.ttf", 28);

	gcolor = { 0x00, 0x00, 0x00, 0xff };

	//Load the cursor icon and the Victory Line
	gcursor_texture = cursor_loader.loadimage(grenderer, "Assets/images/playX.png");
	line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line.png");
}

//Sets the coordinates for the Victory Line and its texture based on which lane has the win arrangement
Line_Coord getLineCoord(int line_no)
{
	Line_Coord temp_line;
	temp_line.line_angle = 0;
	line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line.png");
	switch (line_no)
	{
	case 1: temp_line.line_rect.x = 10;
		temp_line.line_rect.y = 75;
		temp_line.line_rect.w = 600;
		temp_line.line_rect.h = 100;
		temp_line.line_angle = 0;
		
		break;
	case 2: temp_line.line_rect.x = 10;
		temp_line.line_rect.y = 250;
		temp_line.line_rect.w = 600;
		temp_line.line_rect.h = 100;
		temp_line.line_angle = 0;
		break;
	case 3: temp_line.line_rect.x = 10;
		temp_line.line_rect.y = 500;
		temp_line.line_rect.w = 600;
		temp_line.line_rect.h = 100;
		temp_line.line_angle = 0;
		break;
	case 4: 
		line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line_vertical.png");
		temp_line.line_rect.x = 70;
		
		temp_line.line_rect.y = 10;
		temp_line.line_rect.w = 100;
		temp_line.line_rect.h = 600;
		break;
	case 5: 
		line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line_vertical.png");
		temp_line.line_rect.x = 250;
		temp_line.line_rect.y = 10;
		temp_line.line_rect.w = 100;
		temp_line.line_rect.h = 600;
		break;
	case 6:
		line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line_vertical.png");
		temp_line.line_rect.x = 500;
		temp_line.line_rect.y = 10;
		temp_line.line_rect.w = 100;
		temp_line.line_rect.h = 600;
		break;
	case 7: 
		line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line_diagonal.png");
		temp_line.line_rect.x = 10;
		temp_line.line_rect.y = 10;
		temp_line.line_rect.w = 600;
		temp_line.line_rect.h = 600;
		break;
	case 8: 
		line_texture = cursor_loader.loadimage(grenderer, "Assets/images/line_diagonal.png");
		temp_line.line_rect.x = 50;
		temp_line.line_rect.y = 10;
		temp_line.line_rect.w = 500;
		temp_line.line_rect.h = 600;
		break;
	}
	return temp_line;
}

//Display the winning board
void showresult()
{
	display_board.updateBoard(g_board);
	display_board.drawBoard();
	bool retry = false;
	
	SDL_Event temp_event;
	int line_no = g_board.getLineNo();
	Line_Coord line_coord;
	if (line_no > 0)
	{
		line_coord = getLineCoord(line_no);
	}
	else
	{
		line_coord.line_angle = 0;
		line_coord.line_rect = { 0, 0, 0, 0 };
		line_coord.rotate_point = { 0, 0 };
	}
	while (!retry)
	{

		//If clicked reset the board.
		if (SDL_PollEvent(&temp_event) != 0)
		{
			if (temp_event.type == SDL_MOUSEBUTTONUP)
			{
				retry = true;
			}
			else if (temp_event.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(0);
			}

		}
	
		//Lane 7 is the diagonal victory, so flip the line and draw it
		if (line_no != 7)
		{
			SDL_RenderCopy(grenderer, line_texture, NULL, &line_coord.line_rect);
		}
		else
		{
			SDL_RenderCopyEx(grenderer, line_texture, NULL, &line_coord.line_rect, 0, NULL, SDL_FLIP_VERTICAL);
		}
		
		
		if (g_board.checkWin(HUMAN))
		{
			SDL_SetWindowTitle(gwindow, "YOU WIN! Click to reset.");
		}
		else if (g_board.checkWin(COMPUTER))
		{
			SDL_SetWindowTitle(gwindow, "YOU LOSE! Click to reset.");
		}
		else
			SDL_SetWindowTitle(gwindow, "DRAW! Click to reset.");

		SDL_RenderPresent(grenderer);
	}
}

int main(int argc, char** argv)
{
	bool quit = false;
	SDL_Event event;
	g_board.clear();
	bool retry = false;
	//Initialize the SDL framework
	if (init())
	{

		loadfont();
		display_board.setRenderer(grenderer);
		display_board.setBoard(g_board);
		//Loop until a quit message is received.
		while (!quit)
		{
			//If there is a victory or a draw then show the game over result
			if (g_board.isGameOver())
			{
				showresult();
				g_board.clear();

				display_board.clearBoard();
			}

			//Update the board
			SDL_SetWindowTitle(gwindow, "TICTACTOE");
			display_board.updateBoard(g_board);
			SDL_RenderClear(grenderer);

			display_board.drawBoard();
			if (SDL_PollEvent(&event) != 0  )
			{
				if (event.type == SDL_QUIT )
				{
					quit = true;
				}
				else if ( event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
				{
					//If clicked check if the position is whthin bounds and if the cell is empty.
					g_mousehandler.handleEvent(event);
					if (g_mousehandler.checkClicked())
					{
						int index = g_mousehandler.getIndexforClick();
						if (index >= 0 && index < 9 && g_board.isEmpty(index))
						{
							g_board.setPosition(index, -1);
							g_minimax.SetBoard(g_board);
							//Call the minimax algorithm to calculate the next position
							g_minimax.evaluate_current_state(g_board);
							g_board.setPosition(g_minimax.getFinalMove(), 1);
						}
						
					}
				}
			}

			//Display the X icon when the mouse hovers over an empty cell
			if (g_mousehandler.withinBounds() && g_board.isEmpty(g_mousehandler.getIndexforHover()))
			{
				SDL_ShowCursor(0);
				SDL_Rect dest_rect;
				SDL_GetMouseState(&dest_rect.x, &dest_rect.y);
				dest_rect.h = 100;
				dest_rect.w = 100;
				SDL_RenderCopy(grenderer, gcursor_texture, NULL, &dest_rect);
			}
			else
			{
				SDL_ShowCursor(1);
			}
			
			SDL_RenderPresent(grenderer);
		}
	}
	SDL_Quit();
	exit(0);
	return 0;
}

