/**
SPACE WARS
This class is used to handle the file Reading and writing. This is used in the leaderboard display
Author: Ashwin Sankaranarayanan
*/
#ifndef FILE_MANAGER
#define FILE_MANAGER
#include<map>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class FileHandler
{
public:
	/**
	A constructor to initialize the variables
	*/
	FileHandler();
	/**
	Write the score to the file. The player's name and his/her score  are passed which is then written into the file
	*/
	void write(string name,int data);
	void clear();
	/**
	Read the file. It returns a vector of all the players and their corresponding scores. I used this instead of maps as the problem with maps is that they sort themselves. In order to avoid that, i used this
	Return Values: A vector of players and their scores
	*/
	vector < ::pair<string, int> > read();
	/**
	Convert a given string to upper case.
	*/
	string convertUpper(string inpo);
private:
	/**
	The data that is to be written
	*/
	map<string, int> file_data;
	/**
	Data read from the file
	*/
	map<string, int> read_data;
	/**
	The score of the player
	*/
	int score;
	/**
	The name of the player
	*/
	string name;
	/**
	The file stream object
	*/
	ofstream file;
	/**
	Temporary variables used in sorting and reading functions
	*/
	string temp_name;
	int temp_score;


};
#endif