//Prathyoosha Chaya, CS 162
//Nov. 29, 2016
//This implementation file contains the main function and other functions such as the convert to uppercase function and menu function.

#include "subject_list.h"

int menu();

int main()
{
    subject_list subjects;
    
    bool run_again = true;
    int menu_option = 0;    //for user navigation 
    
    cout << "Welcome to the CS162 archive." << endl;

    while (run_again) //This displays the menu and ask the user of the next step every time a task is completed
    {
        menu_option = menu(); //Receive user chosen option from menu function
    
        switch (menu_option)
        {
            case 1: subjects.display_sort();
                    break;
            case 2: subjects.read_sort();
                    break;
            case 3: run_again = false;
                    break;
            default: cout << "Invalid menu choice." << endl;
                    break;
        } 
    }   

    return 0;
}

//menu function: Outputs the menu for the user to select.
//Parameters: None.
//Return values: Integer of user-inputted menu selection.
int menu ()
{
    int option = 0; 
    cout << endl;
    cout << "\t1: Display all subjects.\n"
            "\t2: Add a new subject.\n"
            "\t3: Quit .\n";
    cout << "Please choose the number of which option to execute: ";
    cin >> option;
    cin.ignore(100, '\n');

    return option;
}



