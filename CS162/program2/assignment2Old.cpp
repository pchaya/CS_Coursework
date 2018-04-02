//Prathyoosha Chaya, CS 162, 10/17/2016
//This program functions as a translator to convert normal speech into text speech.

#include <iostream>
#include <cstring>

using namespace std;

void read(char original[]);
bool translate3(char [], char []);
bool translate2(char [], char []);
bool translate1(char [], char []);
void split_to_words(char original[], char split_original[]);
void concatenate3(char split_original[][], phrase[]);
void concatenate2(char split_original[][], phrase[]);

int main()
{
	char original[201];
	char split_original[50][20];
	read (original);
	split_to_words(original, split_original); 



	return 0;
}

void read(char original[])
{
	cout << "Please enter an English sentance to convert to text shortcuts: ";
	cin.get(original, 200, '\n');
	cin.ignore(100, '\n');
	
}


void split_to_words(char original[], char split_original[])
{
	int length = strlen(original);
	int row = 0;
	int col = 0;
	for(int i = 0; i <= length; ++i)
	{
		if (!isblank(original[i]))
			split_original[row][col] = original[i];	
		else
		{
			++row;
			split_original[row][col] = original[i];
		}	
	}
 
	cout << split_original;

}
