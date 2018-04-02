//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//03/19/2017
//This implementation file includes the main function and the menu function.

#include "graph.h"

int menu();

int main()
{
    //Instance of graph to pass into functions/call
    //functions
    graph map;
   

    bool run_again = true;
    int user_option = 0;
    
    bool bool_result = false; //function returns
   
    int int_result = 0;       //function returns
    
    char name [MAX_SIZE_NAME];
    int destination;
    int source;
    cout << "*** Welcome to the CS163 Map. ***" << endl;
 

    while (run_again)   //Displays menu to ask user for next steps
    {
        user_option = menu();
    
        switch (user_option)
        {
            //Case 1: Add vertex.
            case 1: cout << "Please enter the name of the vertex to insert: ";
                    cin.get(name, MAX_SIZE_NAME, '\n');
                    cin.ignore(100, '\n');
                    cout << endl; 
                    int_result = map.insert_vertex(name);
                    break;

            //Case 2: Add edge
            case 2: cout << "Please enter vertex to connect (ex.: 3): ";
                    cin >> source;
                    cin.ignore(100, '\n'); 
                    cout << endl << "Vertex to connect " << source << " to (ex.: 2): ";
                    cin >> destination;
                    cin.ignore(100, '\n');
                    cout << endl;
                    bool_result = map.insert_edge(source -1, destination -1);
                    if (int_result == -1)
                        cout << source << " or " << destination << " does not exist in map." << endl;
                    break;
            //Case 3: Display vertex path.
            case 3: cout << "Vertex to display path of (ex.: 2): " << endl;
                    cin >> source;
                    cin.ignore(100, '\n');

                    cout << endl;

                    bool_result = map.display_all(source - 1);
                    if (!bool_result)
                        cout << "Map at " << source << " does not exist." << endl;
                    break; 
            //Quit  
            case 4: run_again = false;
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

        cout << "\t1: Insert a vertex.\n"
            "\t2: Insert an edge.\n"
            "\t3: Display possible directions from a vertex.\n"
            "\t4: Quit CS Map." << endl;
            cout << "Please choose the number of which option to execute: ";
        cin >> option;
        cin.ignore(100, '\n');

    return option;
}

