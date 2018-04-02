//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//This implementation file includes the main function and the menu function.

#include "table.h"

int menu();

int main()
{
    //Instance of pokemon entry and pokedex to pass into functions/call
    //functions
    entry user_entry;
    table_archive pokedex;
    
    bool run_again = true;
    int user_option = 0;
    
    bool bool_result = false; //function returns
   
    int int_result = 0;       //function returns
    

    char  remove_keyword [MAX_SIZE_NAMES];
    char retrieve_keyword [MAX_SIZE_NAMES];
    cout << "*** Welcome to the CS163 Pokedex. ***" << endl;
 
    //For add function: 
    char user_keyword [MAX_SIZE_NAMES];
    int user_info_type = 0; 
    char user_background [MAX_SIZE_INFO];
    char user_evolution [MAX_SIZE_NAMES];
    int user_evo_candy = 0;
    char user_evo_info [MAX_SIZE_INFO];
    char user_list_of_pokemon [MAX_SIZE_INFO];
    int user_num_of_unique_pokemon = 0;
    char user_term_info [MAX_SIZE_INFO];


    bool_result = pokedex.load();

    if(!bool_result)
        cout << "File not found.. " << endl;

    while (run_again)   //Displays menu to ask user for next steps
    {
        user_option = menu();
    
        switch (user_option)
        {
            //Case 1: Display all info.
            case 1: bool_result = pokedex.display_all();
                    if (!bool_result)
                        cout << "No entries in Pokedex currently." << endl;
                    break;
            //Case 2: Add info.
            case 2: cout << "Add entry: " << endl;
                    cout << "Term: ";
                    cin.get (user_keyword, MAX_SIZE_NAMES, '\n');
                    cin.ignore(100, '\n');
                    
                    cout << endl << "What type of info is this term? : ";
                    cout << endl << "0: A Pokemon.";
                    cout << endl << "1: A regional term.";
                    cout << endl << "2: A general term.";
                    cout << endl << "Please enter the corresponding number: ";
                    cin >> user_info_type;
                    cin.ignore(100, '\n');
                  
                    if (user_info_type == 0)
                    {
                        cout << endl << "Background: ";
                        cin.get (user_background, MAX_SIZE_INFO, '\n');
                        cin.ignore(100, '\n');
                    
                        cout << endl << "Evolution: ";
                        cin.get (user_evolution, MAX_SIZE_NAMES, '\n');
                        cin.ignore(100, '\n');
                    
                        cout << endl << "Candy necessary for evolution: ";
                        cin >> user_evo_candy;
                        cin.ignore(100, '\n');
                    
                        cout << endl << "Evolution info: ";
                        cin.get (user_evo_info, MAX_SIZE_INFO, '\n');
                        cin.ignore(100, '\n');
                    
                    } 
                    
                    if(user_info_type == 1)
                    {
                        cout << endl << "Regional term:";
                        cout << endl << "List of Pokemon in area: ";
                        cin.get (user_list_of_pokemon, MAX_SIZE_INFO, '\n');
                        cin.ignore(100, '\n');
                   
                        cout << endl << "Number of unique pokemon: ";
                        cin >> user_num_of_unique_pokemon;
                        cin.ignore(100, '\n');
                    } 

                    if (user_info_type == 2)
                    {
                        cout << endl << "General term:";
                        cout << endl << "Term info: ";
                        cin.get (user_term_info, MAX_SIZE_INFO, '\n');
                        cin.ignore(100, '\n');
                    }
                    
                    user_entry.set_entry_data(user_keyword, user_info_type, user_background, user_evolution, user_evo_candy, user_evo_info, user_list_of_pokemon, user_num_of_unique_pokemon, user_term_info);
                    int_result = pokedex.add_info(user_entry);
                    if (int_result == 0)
                        cout << "Failed to add entry." << endl;
                    break; 
            //Case 3: Remove info. 
            case 3: cout << "Remove a Pokedex entry:";
                    pokedex.display_all(); 
                    cout << "Please enter the keyword of the entry to remove: ";
                    cin >> remove_keyword;
                    cin.ignore(100, '\n');
                    int_result = pokedex.remove_entry(remove_keyword);
                    if(int_result == 0)
                        cout << "Failed to remove..";
                    break;
            //Case 4: Retrieve info ( 
            case 4: cout << "Retrieve a Pokedex entry:";
                    cout << "Please enter the keyword of the entry to find: ";
                    cin >> retrieve_keyword;
                    cin.ignore(100, '\n');
                    int_result = pokedex.retrieve(retrieve_keyword);
                    if(int_result == 0)
                        cout << "Failed to find " << retrieve_keyword << "from Pokedex." << endl;
             
                    break; 
            //Quit  
            case 5: run_again = false;
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
            "\t2: Add additional info.\n"
            "\t3: Remove info.\n"
            "\t4: Retrieve info.\n"
            "\t5: Quit Pokedex." << endl;
            cout << "Please choose the number of which option to execute: ";
        cin >> option;
        cin.ignore(100, '\n');

    return option;
}

