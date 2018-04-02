//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Prof. Karla Fant
//03/19/2017
//This implementation file includes the function implementations of the
//graph class functions. 

#include "graph.h"

//Constructor/Destructor for vertex struct

//initialize these values when new instance is created
vertex::vertex()
{
    name = NULL;
    head = NULL;
    visited = false;
}

vertex::~vertex()
{
    if (name)
    {
        delete [] name;
        name = NULL;
    }

    if (head)
    {
        delete head;
        head = NULL;
    }
}

//Constructor/Destructor for node struct
node::node()
{
    next = NULL;
    adjacent = NULL;
}

node::~node()
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

//Constructor/Destructor for graph class
graph::graph()
{
    adjacency_list = new vertex [MAX_SIZE_ARRAY];
}


graph::~graph()
{
    if (adjacency_list)
    {
        for (int i = 0; i < MAX_SIZE_ARRAY; ++i)
        {
            if (adjacency_list[i].head)
            {
                node * temp = adjacency_list[i].head;
                while (temp -> next)
                {
                    node * temp2 = temp -> next; 

                    delete temp;
                    temp = temp2;

                } 
            }
        }
        delete [] adjacency_list;
    }
    
}

int graph::insert_vertex(char name [])
{
    for (int i = 0; i < MAX_SIZE_ARRAY; ++i)
    {
    //    cout << "entered" << endl;
        if (!adjacency_list[i].name)
        {
            adjacency_list[i].set_vertex(name);
    //        cout << "t1" << endl;
             
            //adjacency_list[i].head -> adjacent = &(adjacency_list[destination]);
            //adjacency_list[i].head -> next = NULL;
            return 1;
        }
    }
    return 0; 
}

int graph::insert_edge(int source, int destination)
{
    if (!adjacency_list || !(adjacency_list[source].name) || !(adjacency_list[destination].name))
        return -1;

    node * temp = new node;
    temp -> adjacent = &(adjacency_list[destination]);
    temp -> next = NULL;

    if (adjacency_list[source].head)
    {
        node * temp2 = adjacency_list[source].head;
        adjacency_list[source].head = temp;
        temp -> next = temp2;
    }
    else
        adjacency_list[source].head = temp;

    temp = new node;
    temp -> adjacent = &(adjacency_list[source]);
    temp -> next = NULL;

    if (adjacency_list[destination].head)
    {
        node * temp2 = adjacency_list[destination].head;
        adjacency_list[destination].head = temp;
        temp -> next = temp2;
    }
    else
       adjacency_list[destination].head = temp; 
    
    return 0;
}

bool graph::display_all(int source)
{
    if (!adjacency_list[source].name)
        return false;
    cout << "Vertices adjacent to " << source +1 << ": " << adjacency_list[source].name;
    node * temp = adjacency_list[source].head; 
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

