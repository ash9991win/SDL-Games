#include"FileManager.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<cctype>
FileHandler::FileHandler()
{
	score = 0;
	name = "";
}
//Write the passed data onto the file
void FileHandler::write(string name, int data)
{
	//Open in binary append mode
	file.open("SaveData.txt", ios_base::binary | ios_base::app);
	ifstream temp_file;
	//Convert the passed name to upper case letters
	string converted_name = convertUpper(name);
	if (file)
	{
		//If the file exists, we read the contents of the file.
		temp_file.open("SaveData.txt",ios_base::binary | ios_base::app);
		 read();
		//If the name of the current player already exists in the file, then we have to check if the score in the file is greater or less than the current score. If greater, then we do not store the value, else we replace the file score with the current score
		if (file_data.find(converted_name) != file_data.end())
		{
			if (file_data[converted_name] < data)
			{
				file.write((char*)&converted_name, sizeof(string));
				file.write((char*)&data, sizeof(int));
			}
			

		}
		else
		{
			file.write((char*)&converted_name, sizeof(string));
			file.write((char*)&data, sizeof(int));

		}


		

		
	}
	else
		cout << "File Error" << endl;
	file.close();


	
	
	
}

//Read the contents of the file
vector<::pair<string,int>> FileHandler::read()
{
	ifstream file1;
	//Open in binary append mode
	file1.open("SaveData.txt", ios_base::binary | ios_base::app);
	//Clear the data
	file_data.clear();

	if (file1)
	{
		//If the file exists, then read the contents of the file into the file_data map.
		while (!file1.eof())
		{
			file1.read((char*)&temp_name, sizeof(string));
			file1.read((char*)&temp_score, sizeof(int));
			file_data[temp_name] = temp_score;
		}
	}
	else
		cout << "FILE ERROR" << endl;
	file1.close();

	map<int, string> flip_map;
	//When we read the contents of the file, then the values returned should be sorted by the scores. Since we have written into the files as maps, which sort themselves by the key and not the value ( hence they will be sorted my the names), we create a reverse map
	//which has the keys as the scores and the names as the values. So, we obtain all the scores into the vector keys and sort them. Then we create a new vector<pair<string,int>> and populate it according to the scores and names
	vector<int> keys;
	vector<::pair<string, int>> final_result;
	for (map<string, int>::iterator it = file_data.begin(); it != file_data.end(); it++)
	{
		//Populate the keys with the scores present in the file
		keys.push_back(it->second);
		flip_map[it->second] = it->first;
	}
	//Sort the scores
	sort(keys.begin(), keys.end());
	//The reverse iterator is used because we need to go in the descending order and the keys variable has the scores sorted in ascending order
	for (vector<int>::reverse_iterator ir = keys.rbegin(); ir != keys.rend(); ir++)
	{
		//For each score, get the name from the flip_map variable
		final_result.push_back(::make_pair(flip_map[*ir],*ir));
	}
	
	
	return final_result;

	

}


void FileHandler::clear()
{
	file.open("SaveData.txt" );
	file.clear();
	file.close();
}
//Convert the passed string into upper case
string FileHandler::convertUpper(string inp)
{
	string temp_string;
	for (string::iterator it = inp.begin(); it != inp.end(); it++)
	{
		temp_string.push_back(toupper(*it));
	}

	return temp_string;
}