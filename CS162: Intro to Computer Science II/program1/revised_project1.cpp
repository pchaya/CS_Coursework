#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int maxInput = 101;

char getChar();
void getString(char str[]);

int main() 

{
float cost;
float costTotal;
char name[maxInput];
char cont = 'y';
char correct;

/*cout.setf(ios::fixed, ios::floatfield);
cout.setf(ios::showpoint);
cout.precision(2);*/
while (toupper(cont) == 'Y')
    {
    cout << "Enter the Product Name:" << endl;
    getString(name);
    cout << "The product is " << name << endl;
    cout << "Is this corrrect? Enter y/n:" << endl;
    correct = getChar();
    //Validates that the input is either y or n
    while ((toupper(correct) != 'Y') && (toupper(correct) != 'N')) //toupper alows for lowercase or upercase inputs
        {
        cout << "Please enter either y or n:" << endl;
        correct = getChar();
        }
    while (toupper(correct) == 'N')
        {
        cout << "Enter the Product Name again:" << endl;
        getString(name);
        cout << "The product is " << name << endl;
        cout << "Is this corrrect? Enter y/n:" << endl;
        correct = getChar();
        }  

    /*cout << "Enter the Product Cost in dollars and cents (e.g. 1.75)" << endl;
    cout << name << " is $" << cost << "." << endl;
    cout << name << "Is this correct? y/n" endl;
    cout << "Your running total is:" << costTotal << endl;*/
    cout << "Do you want to continue? Enter y/n:" << endl;
    cont = toupper(getChar());
    while (cont != 'Y' && cont != 'N')
        {
        cout << "Please enter either y or n:" << endl;
        cont = toupper(getChar());
        }

    }
}

char getChar()
{
    char character;

    cin >> character;
    while (!cin)
    {
        cout << "Illegal input, please enter a valid character:" << endl;
        cin >> character; 
    }
	cin.ignore(maxInput, '\n');
    return character;
}

void getString(char str[])
{
    cin.get(str, maxInput, '\n');
    while (!cin)
    {
        cin.clear();
        cin.ignore(maxInput, '\n');
        cout << "Illegal input, please try again:" << endl;
        cin.get(str, maxInput);
    }
}




