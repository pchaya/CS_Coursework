//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/18/2017
//This implementation file includes the main function and the menu function.

#include "maze.h"
#include "list.h"

int menu(int current_player);

int main()
{
    //Instance of graph to pass into functions/call
    //functions
    maze map;

    //create player instances 
    player p1;
    player p2;
    player p3;
    player p4;

    //set player numbers and friends
    p1.set_player_num(1);
    p1.set_friend_num(2); 
    p2.set_player_num(2);
    p2.set_friend_num(1);
    p3.set_player_num(3);
    p3.set_friend_num(4);
    p4.set_player_num(4);
    p4.set_friend_num(3);

    bool run_again = true;
    int user_option = 0;
    
   
    int int_result = 0;       //function returns
    
    char name [MAX_SIZE_NAME];
    cout << "*** Welcome to the CS202 Maze. ***" << endl;

    //BUILD MAP
    int num_of_checkpoints = 0;
    do
    {
        num_of_checkpoints = rand() % MAX_SIZE_ARRAY -1;  //to leave 2 spaces for start/end

    }while (num_of_checkpoints < 5);

    int ending_checkpoint = map.build_maze(num_of_checkpoints);

    for(int i = 0; i < num_of_checkpoints; ++i)
        map.display_all(i);
   
    int current_player = 1; 

    while (run_again)   //Displays menu to ask user for next steps
    {
        user_option = menu(current_player);
    
        switch (user_option)
        {
            //Case 1: Move
            case 1: 
                switch(current_player)
                {
                    case 1:map.display_all(p1.get_location());
                           break;
                    case 2:map.display_all(p2.get_location());
                           break;
                    case 3:map.display_all(p3.get_location());
                           break;
                    case 4:map.display_all(p4.get_location());
                           break;

                } 
                cout << "Where would you like to move: (enter #) ";
                cin >> user_option;
                switch(current_player)
                {
                    case 1:p1.set_location(user_option);
                           break;
                    case 2:p2.set_location(user_option);
                           break;
                    case 3:p3.set_location(user_option);
                           break;
                    case 4:p4.set_location(user_option);
                           break;

                } 
                current_player = (++current_player) % 4;

                if(p1.get_location() == ending_checkpoint)
                {
                    run_again = false;
                    cout << "Player 1 has won." << endl;
                }

                else if(p2.get_location() == ending_checkpoint)
                {
                    run_again = false;
                    cout << "Player 2 has won." << endl;
                }
                
                else if(p3.get_location() == ending_checkpoint)
                {
                    run_again = false;
                    cout << "Player 3 has won." << endl;
                }              

                else if(p4.get_location() == ending_checkpoint)
                {
                    run_again = false;
                    cout << "Player 4 has won." << endl;
                }              

                break;

               //go back to start
            case 3:
                    switch(current_player)
                    {
                        case 1:p1.set_location(0);
                        case 2:p2.set_location(0);
                        case 3:p3.set_location(0);
                        case 4:p4.set_location(0);

                    } 
                    cout << "Player " << current_player << " resetted." << endl;
                    current_player = (++current_player) % 4;
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

int menu(int current_player)
{
    int option = 0;
    cout << endl;
    cout << "Player #" << current_player << "'s turn:" << endl; 
        cout << "\t1: Move.\n"
            //"\t2: Use a reward.\n"
            "\t2: Go back start.\n"
            "\t3: Quit game. "<< endl;
            cout << "Please choose the number of which option to execute: ";
        cin >> option;
        cin.ignore(100, '\n');

    return option;
}

