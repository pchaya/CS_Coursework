//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/18/2017
//This implementation file includes the function implementations of the
//maze class functions. 

#include "maze.h"

//Constructor/Destructor for checkpoint class

//initialize these values when new instance is created
checkpoint::checkpoint()
    :name(NULL), head(NULL), start_or_finish(false), num_of_paths(0)
{

}

checkpoint::~checkpoint()
{
    if (name)
    {
        delete [] name;
        name = NULL;
    }

    if (head)
    {
        maze_node * temp = head;
        while (temp -> next)
        {
            maze_node * temp2 = temp -> next; 

            delete temp;
            temp = temp2;

        }
        delete head;
        head = NULL;
    }
}

void checkpoint::set_checkpoint(char user_name [])
{
    name = new char [strlen(user_name) +1];
    strcpy(name, user_name);
}

//Constructor/Destructor for maze_node struct
maze_node::maze_node()
    :adjacent(NULL), next(NULL), prev(NULL)
{

}

maze_node::~maze_node()
{
    if(next)
    {
        delete next;
        next = NULL;
    }
    /*
    if(adjacent)
    {
        delete adjacent;
        adjacent = NULL;
    }
    */
}

//Constructor/Destructor for maze class
maze::maze()
{
    adjacency_list = new checkpoint [MAX_SIZE_ARRAY];
}


maze::~maze()
{
    if (adjacency_list)
    {
        for (int i = 0; i < MAX_SIZE_ARRAY; ++i)
        {
            if (&adjacency_list[i])
            {
                delete &adjacency_list[i];
            }
        }
        delete [] adjacency_list;
    }
    
}

int maze::build_maze(int num_of_checkpoints)
{
    //call int num_of_checkpoints = rand() % MAX_SIZE_ARRAY -1; to leave
    //2 cpaces for start/end from main, then
    //pass as parameter. while num_of_checkpoints < 5, keep randomizing
    adjacency_list[0].insert_checkpoint("start");
    adjacency_list[0].insert_edge(0, 1); 

    int i = 1;
    for(i = 1; i <= (num_of_checkpoints/2); ++i)
    {
        int rand_checkpoint = rand() % num_of_checkpoints +1;

        if (adjacency_list[i].num_of_paths <= 3 || adjacency_list[rand_checkpoint].num_of_paths <= 3)
        {
            adjacency_list[i].insert_checkpoint("test");
            adjacency_list[i].insert_edge(i, random_checkpoint);
        }
    }

    adjacency_list[++i].insert_checkpoint("end");

    bool roll_again = false;
    int rand_checkpoint = 0;
    do
    {
        rand_checkpoint = rand() % (num_of_checkpoints/2);
        if (!adjacency_list[rand_checkpoint].head)
            roll_again = true;

        maze_node * temp = adjacency_list[rand_checkpoint].head;
        while (adjacency_list[rand_checkpoint].temp -> next)
        {
            if (temp -> adjacent == adjacency_list[0])
                roll_again = true;
            else
                temp = temp -> next;
        }

    }while(rand_checkpoint !=0 || roll_again);
    adjacency_list[i].insert_edge(i, rand_checkpoint); 
    cout << "Ending checkpoint: " << rand_checkpoint << endl;
}

int maze::insert_checkpoint(char name [])
{
    for (int i = 0; i < MAX_SIZE_ARRAY; ++i)
    {
    //    cout << "entered" << endl;
        if (!adjacency_list[i].name)
        {
            adjacency_list[i].set_checkpoint(name);
    //        cout << "t1" << endl;
             
            //adjacency_list[i].head -> adjacent = &(adjacency_list[destination]);
            //adjacency_list[i].head -> next = NULL;
            return 1;
        }
    }
    return 0; 
}

int maze::insert_edge(int source, int destination)
{
    if (!adjacency_list || !(adjacency_list[source].name) || !(adjacency_list[destination].name))
        return -1;

    maze_node * temp = new maze_node;
    temp -> adjacent = &(adjacency_list[destination]);
    temp -> next = NULL;
    temp -> prev = NULL;

    if (adjacency_list[source].head)
    {
        maze_node * temp2 = adjacency_list[source].head;
        adjacency_list[source].head = temp;
        temp -> next = temp2;
    }
    else
        adjacency_list[source].head = temp;

    ++adjacency_list[source].num_of_paths;

    temp = new maze_node;
    temp -> adjacent = &(adjacency_list[source]);
    temp -> next = NULL;

    if (adjacency_list[destination].head)
    {
        maze_node * temp2 = adjacency_list[destination].head;
        adjacency_list[destination].head = temp;
        temp -> next = temp2;
    }
    else
       adjacency_list[destination].head = temp; 
    
    ++adjacency_list[destination].num_of_paths;
    return 0;
}

bool maze::display_all(int source)
{
    if (!adjacency_list[source].name)
        return false;
    cout << "Vertices adjacent to " << source +1 << ": " << adjacency_list[source].name;
    maze_node * temp = adjacency_list[source].head; 
    for (int i = 0; i < MAX_SIZE_ARRAY; ++i)
    {
        while(temp)
        {
            cout << endl << "Connected to: " << temp -> adjacent -> name; 
            temp = temp -> next;
        }
    }
    cout << endl;

    return true;
}

checkpoint * maze::get_adjacency_list()
{
    return adjacency_list;
}

