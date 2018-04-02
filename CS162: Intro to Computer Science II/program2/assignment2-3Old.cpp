//Prathyoosha Chaya, Cs 162, 10/17/2016
//This program functions as a translator to convert normal speech into text speech.

#include <iostream>
#include <cstring>

using namespace std;

//Function prototypes
void read(char original[]);
int  split_to_words(char original[], char split_original[][50]);
void concatenate3 (char split_original[][50], char phrase[], int starting_wordIndex);
void concatenate2 (char split_original[][50], char phrase[], int starting_wordIndex);
bool translate3(char phrase[], char translation[]);
bool translate2(char phrase[], char translation[]);
bool translate1(char word[], char translation[]);


int main()
{
	while (run_again = 'y' || run_again == 'Y')
	{
		char original[201] = "\0";
		char split_original[20][50];
		char phrase[201] = "\0";
		char final_translation[201] = "\0";

		int word_count = 0;
		int current_wordIndex = 0;
		int remaining_words = 0;

		bool is_translated = false;
		char run_again = 'y';

		read (original);
		word_count = split_to_words(original, split_original); 
		
		remaining_words = word_count;
		char translation[201] = "\0";

		while(remaining_words != 0)
		{		
			if(remaining_words >= 3)
			{
				concatenate3(split_original, phrase, current_wordIndex);
				if(translate3(phrase, translation) == true)
				{
					strcat(final_translation, translation);
					current_wordIndex += 3;
					remaining_words = word_count - current_wordIndex;
				}
			}
			else if (remaining_words >= 2)
			{
				concatenate2(split_original, phrase, current_wordIndex);
				if(translate2(phrase, translation) == true)
				{
					strcat(final_translation, translation);
					current_wordIndex += 2;
					remaining_words = word_count - current_wordIndex;
				}
			}
			else if (remaining_words >= 1)
			{
				translate2(phrase, translation);
				strcat(final_translation, translation);
				current_wordIndex += 1;
				remaining_words = word_count - current_wordIndex;
			}
		}
		
		cout << endl << final_translation;
		
		cout << endl << "Would you like to run again? (y/n): ";
		cin >> run_again;
		cin.ignore(100, '\n');
	}	

	return 0;
}
void read(char original[])
{
	cout << "Please enter an English sentance to convert to text shortcuts: ";
	cin.get(original, 200, '\n');
	cin.ignore(100, '\n');
	
}


int  split_to_words(char original[], char split_original[][50])
{
	int length = strlen(original);
	int wordIndex = 0;
	int letterIndex = 0;
	bool entered_once = false;
	for(int i = 0; i <= length; ++i)
	{
		if (!isspace(original[i]))
		{
			entered_once = false;
			split_original[wordIndex][letterIndex] = original[i];	
			letterIndex++;
		}

		else if (entered_once == false)  //checking for entered once to avoid problems when there are multiple spaces between words
		{
			split_original[wordIndex][letterIndex] = '\0';
			++wordIndex;
			letterIndex = 0;   //set index new word's first letter to 0
			entered_once = true;
		}
	}
 	return wordIndex+1; //returns number of words

}

void concatenate3 (char split_original[][50], char phrase[], int starting_wordIndex)
{
	strcat(phrase, split_original[starting_wordIndex]);
	strcat(phrase, " ");
	strcat(phrase, split_original[starting_wordIndex+1]);
	strcat(phrase, " ");
	strcat(phrase, split_original[starting_wordIndex+2]);
}

void concatenate2 (char split_original[][50], char phrase[], int starting_wordIndex)
{
	strcat(phrase, split_original[starting_wordIndex]);
	strcat(phrase, " ");
	strcat(phrase, split_original[starting_wordIndex+1]);
}


bool translate3(char phrase[], char translation[])
{
	bool is_translated = true;
	if (strcmp(phrase, "let me know") == 0)
		strcpy(translation, "lmk");
	else if (strcmp(phrase, "Let me know") == 0)
		strcpy(translation, "Lmk");
	else if (strcmp(phrase, "by the way") == 0)
		strcpy(translation, "btw");
	else if (strcmp(phrase, "By the way") == 0)
		strcpy(translation, "Btw");
	else
		is_translated = false;

	return is_translated;
}


bool translate2(char phrase[], char translation[])
{
	bool is_translated = true;
	if (strcmp(phrase, "good luck") == 0)
		strcpy(translation, "gl");
	else if (strcmp(phrase, "Good luck") == 0)
		strcpy(translation, "Gl");
	else if (strcmp(phrase, "see you") == 0)
		strcpy(translation, "cu");
	else if (strcmp(phrase, "See you") == 0)
		strcpy(translation, "Cu");
	else
		is_translated = false;

	return is_translated;
}

bool translate1(char word[], char translation[])
{
	bool is_translated = true;
	if (strcmp(word, "see") == 0)
		strcpy(translation, "c");
	else if (strcmp(word, "See") == 0)
		strcpy(translation, "C");
	else if (strcmp(word, "you") == 0)
		strcpy(translation, "u");
	else if (strcmp(word, "You") == 0)
		strcpy(translation, "U");
	else if (strcmp(word, "later") == 0)
		strcpy(translation, "l8r");
	else if (strcmp(word, "Later") == 0)
		strcpy(translation, "L8r");
	else
	{
		is_translated = false;
		strcpy(translation, word);   //Since translate1 function is the last check, it returns the original word if there is no match.
	}
	
	return is_translated;
}
