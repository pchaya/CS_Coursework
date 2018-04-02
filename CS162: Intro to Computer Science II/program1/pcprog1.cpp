//Prathyoosha Chaya, CS162 PSU Prof. Colleen Toth, 10/11/2016
// This program calculates the number of pokemon collected and battles completed to level up. 
#include <iostream>
using namespace std;
/*
void userData (int& totalXP, int& collectedXP, float& battleRate, bool& isLuckyEgg)
void calcPokemon (int& totalXP, int& collectedXP, float& battleRate, bool& isLuckyEgg)tes XP requi
void displayResults (int battleNum, int collectedPokemon)
*/

int main()
{
cout << "This program calculates XP requirements for leveling up." << endl;

//Declare and initialize variables
char runAgain = 'y';
unsigned int totalXP, collectedXP, reqXP, collectedPokemon, evoNum, evoXP, battleNum, battleXP = 0;
float battleRate = 0;
char isLuckyEgg = '\0';

//while loop condition to allow for running again
while (runAgain == 'y' || runAgain == 'Y')
{
	/*userdata (totalXP, collectedXP, battleRate, isLuckyEgg);
	calcPokemon (totalXP, collectedXP, battleRate, isLuckyEgg);
	displayResults(totalXP, collectedXP, battleRate, is
	Was going to use functions, but decided not to as functions are only being called once.*/
	//Read user data:
	cout << "Please enter the total XP required to level up: "; 
	cin >> totalXP;
	cin.ignore(100, '\n');
	cout << endl << "Please enter how much XP is collected so far: ";
	cin >> collectedXP;
	cin.ignore(100, '\n');
	cout << endl  << "Please enter the battle rate in %(1-100%) ";
	cin >> battleRate;
	cin.ignore(100, '\n');
	cout << "Is there a lucky egg (y/n): ";
	cin >> isLuckyEgg;
	cin.ignore (100, '\n');
	//check for input failure
	if (battleRate < 1)
		battleRate = battleRate *100;
	if (isLuckyEgg == 'y' || isLuckyEgg == 'n'|| isLuckyEgg == 'N' || isLuckyEgg == 'Y')
	{		
	
		reqXP = totalXP - collectedXP;

		if(isLuckyEgg == 'y' || isLuckyEgg == 'Y')
			reqXP = reqXP / 2;


		collectedPokemon = reqXP /100; //assuming no evolutions yet
		
		if(collectedPokemon >= 50)
		{
			evoNum = collectedPokemon / 50;
			evoXP = evoNum * 500;
			reqXP = reqXP - evoXP;
		}

		if (battleRate >= 0)
		{
			battleXP = (reqXP * battleRate/100);
				battleNum = battleXP / 100;
			reqXP = reqXP - battleXP;
		}
	
		collectedPokemon = reqXP / 100; // doing this again to update collectedPokemon value
	
		//display results
		cout << endl;
		cout << "Number of Pokemon collected: " << collectedPokemon << endl;
		cout << "Number of evolved: " << evoNum << endl;
		cout << "Number of battles: " <<  battleNum << endl;
		
	}

	else
		cout << "Invalid Input.";
	cout << "Do you want to run again? (y/n) ";
	cin >> runAgain;
	cin.ignore(100, '\n');

} 


return 0;
}
