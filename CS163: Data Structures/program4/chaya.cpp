//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//03/19/2017
//This implementation file includes the main function and the menu function.

#include "table.h"

int menu();

int main()
{
    //Instance of term entry and dictionary to pass into functions/call
    //functions
    entry user_entry;
    table_archive dictionary;
   
    entry retrieved_entry;

    bool run_again = true;
    int user_option = 0;
    
    bool bool_result = false; //function returns
   
    int int_result = 0;       //function returns
    
    char first_char = '\0';
    char last_char = '\0';
    char remove_term_name [MAX_SIZE_NAMES];
    char retrieve_term_name [MAX_SIZE_NAMES];
    cout << "*** Welcome to the CS163 CS Dictionary. ***" << endl;
 
    //For add function: 
    char user_term_name [MAX_SIZE_NAMES];
    char user_definition [MAX_SIZE_INFO];


    bool_result = dictionary.load();

    if(!bool_result)
        cout << "File not found.. " << endl;

    while (run_again)   //Displays menu to ask user for next steps
    {
        user_option = menu();
    
        switch (user_option)
        {
            //Case 1: Display all info.
            case 1: bool_result = dictionary.display_all();
                    if (!bool_result)
                        cout << "No entries in dictionary currently." << endl;
                    break;
            //Case 3: Display range
            case 2: cout << "Starting range: ";
                    cin >> first_char;
                    cin.ignore(100, '\n'); 
                    cout << endl << "Ending range: ";
                    cin >> last_char;
                    cin.ignore(100, '\n');
                    cout << endl;
                    bool_result = dictionary.display_range(first_char, last_char);
                    if (!bool_result)
                        cout << "Dictionary is empty.." << endl;
                    break;
            //Case 3: Insert entry.
            case 3: cout << "Insert entry: " << endl;
                    cout << "Term name: ";
                    cin.get(user_term_name, MAX_SIZE_NAMES, '\n');
                    cin.ignore(100, '\n');

                    cout << endl << "Definition: ";
                    cin.get (user_definition, MAX_SIZE_INFO, '\n');
                    cin.ignore(100, '\n');
                    cout << endl;

                    user_entry.set_entry_data(user_term_name, user_definition);
                    int_result = dictionary.insert_entry(user_entry);
                    if (int_result == 0)
                        cout << "Failed to add entry." << endl;
                    break; 
            //Case 3: Remove info. 
            case 4: cout << "Remove a Dictionary entry:";
                    dictionary.display_all(); 
                    cout << "Please enter the name of the entry to remove: ";
                    cin >> remove_term_name;
                    cin.ignore(100, '\n');
                    int_result = dictionary.remove_entry(remove_term_name);
                    if(int_result == 0)
                        cout << "Failed to remove..";
                    break;
            //Case 4: Retrieve info ( 
            case 5: cout << "Retrieve a Dictionary entry:";
                    cout << "Please enter the name of the entry to find: ";
                    cin >> retrieve_term_name;
                    cin.ignore(100, '\n');
                    int_result = dictionary.retrieve(retrieve_term_name, retrieved_entry);
                    if(int_result == 0)
                        cout << "Failed to find " << retrieve_term_name << "from dictionary." << endl;
                    cout << "Term: " << retrieved_entry.term_name << endl;
                    cout << "Definition: " << retrieved_entry.definition << endl;
             
                    break; 
            case 6: int_result = dictionary.get_height();
                    cout << "Height of dictionary: " << int_result << endl;
                    break;
            case 7: bool_result = dictionary.is_efficient();
                    if (bool_result)
                       cout << "Dictionary is balanced!!" << endl;
                    else
                       cout << "Dictionary is not balanced." << endl; 
                    break;
            //Quit  
            case 8: run_again = false;
                    break;

            default: cout << "Invalid menu choice." << endl;
                     break;
        } 
    } 


    return 0;
}

int menu()
{
    int option = 0;
    cout << endl;

        cout << "\t1: Display all info.\n"
            "\t2: Display all info in specified range.\n"
            "\t3: Add Dictionary item.\n"
            "\t4: Remove Dictionary item.\n"
            "\t5: Retrieve info.\n"
            "\t6: Get height of Dictionary structure.\n"
            "\t7: Check efficiency of dictionary.\n"
            "\t8: Quit CS Dictionary." << endl;
            cout << "Please choose the number of which option to execute: ";
        cin >> option;
        cin.ignore(100, '\n');

    return option;
}

