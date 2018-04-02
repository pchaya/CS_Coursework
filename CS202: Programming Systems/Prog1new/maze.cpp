//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/30/2017
//This implementation file contains the class methods and their definitions.

#include "maze.h"

//Graph_node methods:
Graph_node::Graph_node()
{
    connected_ckpt = NULL;
    prev = NULL;
    next = NULL;
}

Graph_node::Graph_node(Ckpt * to_connect)
{
    Graph_node();
    connected_ckpt = to_connect; 
}

Graph_node::~Graph_node()
{
    //nothing
}

void Graph_node::set_next(Graph_node * next_node)
{
    next = next_node;
}

void Graph_node::set_prev(Graph_node * prev_node)
{
    prev = prev_node;
}

Graph_node * Graph_node::next_node()
{
    return next;
}

Graph_node * Graph_node::prev_node()
{
    return prev;
}

Ckpt * Graph_node::get_connected_ckpt()
{
    return connected_ckpt;
}

//Obj methods
Obj::Obj(int ID_to_set)
    :ID(ID_to_set)
{

}

int Obj::get_ID()
{
    return ID;
}


//List_node methods
List_node::List_node()
    :next(NULL)
{
    data[0] = NULL;
    data[1] = NULL;
}

List_node::~List_node()
{
    //nothing
}

bool List_node::add_item(Obj * p_Obj )      //find index, and set data
{
    bool is_added = false;

    for(int i = 0; i <=1 && !is_added; ++i)
    {
        if(data[i] == NULL)
        {
            data[i] = p_Obj;
            is_added = true;
        }

    } 

    return is_added;
}

List_node * List_node::next_node()
{
    return next;
}

Obj * List_node::get_data(int index)
{
    return data[index];
}

void List_node::set_next(List_node * next_node)
{
    next = next_node;
}

//List methods
List::List()
    :head(NULL)
{

} 
List::~List()
{
    if(head)
    {
        while (head->next_node())
        {
            List_node * temp = head->next_node();
            if(head->get_data(0))
                delete head->get_data(0);
            if(head->get_data(1))
                delete head->get_data(1);

            if(head)
                delete head;
            head = temp;
        }

        if(head->get_data(0))
            delete head->get_data(0);
        if(head->get_data(1))
            delete head->get_data(1);
        if(head)
            delete head;


    }

    

}



void List::add_obj(Obj * p_Obj)
{
    if (!head)
    {
        //create a new node
        head = new List_node;

    }

    //go to last node
    List_node * temp = head;
    while (temp->next_node())
    {
        temp = temp->next_node();
    }

    //add item at last node
    bool was_added = temp->add_item(p_Obj);

    //if node's array was full:
    if (!was_added)
    {
        //create new node
        List_node * temp2 = new List_node;
        temp->set_next(temp2);

        was_added = temp2->add_item(p_Obj);
    }

}



Reward::Reward()
    :Obj(), desc(NULL)  
{

}

Reward::Reward(int ID, char * description)
    :Obj(ID)
{
    desc = new char [strlen(description) +1];
    strcpy(desc, description);
}

void Reward::display_desc()
{
    cout << endl << "Reward: " << desc << endl;
}

//Spinner methods
Spinner::Spinner()
{
    //list of possible rewards
    Reward * reward0 = new Reward(0, (char *)"No reward.");
    Reward * reward1 = new Reward(1, (char *)"Take another turn.");
    Reward * reward2 = new Reward(2, (char *)"Take friend's reward.");
    Reward * reward3 = new Reward(3, (char *)"Go back to start.");

    //add to the reward list
    add_obj(reward0);
    add_obj(reward1);
    add_obj(reward2);
    add_obj(reward3);
}

Reward * Spinner::spin()
{
    int rand_num = rand() % 6;
    switch(rand_num)
    { 
        case 0: cout << "You got: ";
                get_reward(0)->display_desc();
                cout << endl;
                return get_reward(0);

        case 1: cout << "You got: ";
                get_reward(1)->display_desc();
                cout << endl;
                return get_reward(1);

        case 2: cout << "You got: ";
                get_reward(2)->display_desc();
                cout << endl;
                return get_reward(2);

        case 3: cout << "You got: ";
                get_reward(3)->display_desc();
                cout << endl;
                return get_reward(3);

        default: return NULL;

    }

}

Reward * Spinner::get_reward(int ID)
{
    return (Reward *)get_obj(ID);
}


Obj * List::get_obj(int ID)
{
    if (!head) return NULL;
    
    List_node * temp = head;

    while (temp)
    {
        if(temp->get_data(0)->get_ID() == ID)
            return temp->get_data(0);
        else if(temp->get_data(1)->get_ID() == ID)
            return temp->get_data(1);

        else
        {
            List_node * temp2 = temp->next_node();
            temp = temp2;
        }

    }

    return NULL;

}

//Friends_list methods
void Friends_list::add_player(Player * a_player)
{
    if(a_player)
        add_obj(a_player); 

}

Player * Friends_list::get_my_friend(Player * a_player)
{
    if(a_player)
    {
        int my_ID = a_player->get_ID();

        if(my_ID != head->get_data(0)->get_ID())
        {
            return (Player *)head->get_data(0); 
        }
        else
        {
            return (Player *)head->get_data(1);
        }

    }

    return NULL;

}


//Ckpt methods
Ckpt::Ckpt()
    :ID(-1), is_end(false), num_of_connections(0), head(NULL)
{
    //initialized ID with -1 for invalid checkpoint

}

Ckpt::~Ckpt()
{
    if(head)
    {
        while (head->next_node())
        {
            Graph_node * temp = head->next_node();
            delete head;
            head = temp;
        }
        delete head;
    }
}

void Ckpt::init(int new_ID, bool is_end, int num_connections)
{
    ID = new_ID;
    is_end = is_end;
    num_of_connections = num_connections;
    head = NULL;
}

bool Ckpt::add_node(Ckpt * to_set)
{
    //case 1: if list is empty
    // add new node to head, set next to null
    //case 2: if items in list
    // add new node, set old head prev to curr head prev
    if (num_of_connections >= 3)
        return false;
    if (!to_set)
        return true;

    Graph_node * temp = new Graph_node(to_set);

    if (head)
    {
        Graph_node * temp2 = head;
        head = temp;
        temp->set_next(temp2);
        temp2->set_prev(head); 
    }
    else
        head = temp;

    ++num_of_connections;
    return true;
}

int Ckpt::get_ID()
{
    return ID;
}

void Ckpt::display_connected()
{
    if (!head)
        return;
    cout << "Connected destinations to " << ID << ": ";
    Graph_node * temp = head; 

    while(temp)
    {
        cout << temp->get_connected_ckpt()->get_ID() << ", "; 
        temp = temp->next_node();
    }
    cout << endl;

    return;
}

int Ckpt::get_num_of_connections()
{
    return num_of_connections;
}

//Maze methods
Maze::Maze()
{
    num_of_ckpts = rand() % 14 + 5;     //Will choose random # between 0-14, then add 5 to make min. # of checkpoints = 5, and max = 14 + 5 =19.

    adjacency_list = new Ckpt [num_of_ckpts];

    for (int i = 0; i < num_of_ckpts; ++i)
    {
        adjacency_list[i].init(i);
    }

    adjacency_list[num_of_ckpts-1].init(num_of_ckpts-1, true);
}

Maze::~Maze()
{
    if (adjacency_list)
    {
        delete [] adjacency_list;
    }

}

int Maze::build_maze()
{
    //call int num_of_checkpoints = rand() % MAX_SIZE_ARRAY -1; to leave
    //2 cpaces for start/end from main, then
    //pass as parameter. while num_of_checkpoints < 5, keep randomizing
    cout << "Number of checkpoints: " << num_of_ckpts << endl;
   
    //connect the start (index 0)
    insert_edge(&adjacency_list[0], &adjacency_list[1]);
    
    for(int i = 0; i < (num_of_ckpts -1); ++i)
    {
        int rand_checkpoint = 0;
        do
        {
            rand_checkpoint = rand() % (num_of_ckpts -2);
        }while(rand_checkpoint <= 0 || rand_checkpoint == i);

        insert_edge(&adjacency_list[i], &adjacency_list[rand_checkpoint]);
    }
    int i = 1;
    for (i = 1;i<num_of_ckpts;++i)
    {
        //find a random checkpoint that still has less than 3 connections
        if(adjacency_list[i].get_num_of_connections() <3)
        break; 
    }

    //connect that checkpoint to the end.
    insert_edge(&adjacency_list[i], &adjacency_list[num_of_ckpts-1]); 
    cout << "Ending checkpoint: " << num_of_ckpts-1 << endl;

    return num_of_ckpts -1;
}

bool Maze::insert_edge(Ckpt * source, Ckpt * destination)
{
    if (!adjacency_list || !source || !destination)
        return false;

    bool r1 = false;
    bool r2 = false;
    r1 = source->add_node(destination);
    r2 = destination->add_node(source);

    cout << "Connected " << source->get_ID() << " and " << destination->get_ID() << endl;
    if (!r1 || !r2)
        return false;
    else 
        return true;
}


Ckpt * Maze::get_ckpt(int index)
{
    return &adjacency_list[index];
}

int Maze::get_num_of_ckpnts()
{
    return num_of_ckpts;
}


//Player class methods
Player::Player()
    :Obj(0), game_spinner(NULL), game_maze(NULL), location(NULL), friends(NULL), is_done(false)
{

}

Player::Player(int player_num, Spinner * game_spinner, Maze * game_maze, Ckpt * start_location)
    :Obj(player_num), game_spinner(game_spinner), game_maze(game_maze), location(start_location), friends(NULL), is_done(false)
{

}

void Player::take_turn()   //call redeem, then move, then spin
{
    redeem_reward();
    move();
    spin();
}

Reward * Player::get_reward()
{
    return a_reward;
}

void Player::clear_reward()
{
    a_reward = NULL;
}

void Player::set_friends_list(Friends_list * my_friends)
{
    friends = my_friends; 
}

Ckpt * Player::move()     //always called after redeem, and before spin
{
    int to_move_ckpt_index;

    //display connected checkpoints
    cout << "Player" << ID << " can move to: " << endl;
    location->display_connected();

    //move to the checkpoint
    cout << "Please enter the # of the checkpoint to move to: ";
    cin >> to_move_ckpt_index;
    cin.ignore(100, '\n');
    cout << endl;

    location = game_maze->get_ckpt(to_move_ckpt_index);

    if(location == game_maze->get_ckpt(game_maze->get_num_of_ckpnts()))
        is_done = true; 
    return location;

}

bool Player::is_player_done()
{
    return is_done;
}

void Player::spin()      //game class will call the player's spin func.. There is only one instance of spinner ,which each player has access to.
{
    char response = 'n';

    if(!a_reward)
        a_reward = game_spinner->spin(); 

    else if (a_reward)      //existing reward has not been used yet
    {
        cout << endl<< "You already have a reward that you have not used. Replace? (y/n): ";
        cin >> response;
        cin.ignore(100, '\n');
        cout << endl;

        if (response == 'y' || response == 'Y')
        {
            a_reward = game_spinner->spin();
        }
    }
}
void Player::redeem_reward()       //will have switch statement to call the appropriate reward execuation based on reward held. 
{
    //show player's reward
    cout << endl << "Redeeming: ";
    if(!a_reward)
    {
        cout << "You have no reward."<< endl;
        return;
    }

    a_reward->display_desc();
    cout << endl; 

    switch(a_reward->get_ID()) 
    {
        //0: "No reward."
        case 0: break;
                //1: "Take another turn."
        case 1: move(); 
                break;
                //2: "Take friend's reward."
        case 2: {
                    Player * my_friend = friends->get_my_friend(this); 
                    a_reward = my_friend->get_reward(); 
                    my_friend->clear_reward();
                    break;
                }

                //3: "Go back to start."
        case 3: {
                    location = game_maze->get_ckpt(0); 
                    break;
                }
        default: cout << "Invalid reward.." << endl;
                 break;
    }
    a_reward = NULL;

}


//Game class methods:
Game::Game()
{
    game_spinner = new Spinner;
    game_maze = new Maze;
    groups[0] = new Friends_list;
    groups[1] = new Friends_list;

    for (int i = 0; i < 4; ++i)
        players[i] = NULL;
}

Game::~Game()
{
    if(game_spinner)
       delete game_spinner;
    if(game_maze)
       delete game_maze;

    for (int i = 0;i<4;++i)
    {
        if(players[i])
            delete players[i];
    }

    if(groups[0])
       delete groups[0];
    if(groups[1])
       delete groups[1]; 

}

void Game::begin_game()
{
    game_maze->build_maze();

    players[0] = new Player(0,game_spinner,game_maze,game_maze->get_ckpt(0));
    players[1] = new Player(1,game_spinner,game_maze,game_maze->get_ckpt(0));
    players[2] = new Player(2,game_spinner,game_maze,game_maze->get_ckpt(0));
    players[3] = new Player(3,game_spinner,game_maze,game_maze->get_ckpt(0));
    cout << "4 Players created." << endl;

    groups[0]->add_player(players[0]);
    groups[0]->add_player(players[1]);
    groups[1]->add_player(players[2]);
    groups[1]->add_player(players[3]);
    cout << "Player 1 and 2 in Group 1. \nPlayer 3 and 4 in Group 2." << endl;

    players[0]->set_friends_list(groups[0]);
    players[1]->set_friends_list(groups[0]);
    players[2]->set_friends_list(groups[1]);
    players[3]->set_friends_list(groups[1]);
}

void Game::play_game()
{
    cout << "Welcome to the CS Maze game!!" << endl;
    cout << "Player 1 goes first." << endl;

    int num_players_done = 0;
    bool run_again = true;

    while (run_again)
    {
        for(int i = 0;i<4;++i)
        {
            if(players[i]->is_player_done())
                ++num_players_done;

            if(players[i]->is_player_done() == false)
            //allow players to take turns
                players[i]->take_turn();

            if(num_players_done >1)
            {
                cout << "The game is over." << endl;
            }
        }

    }
    

}



