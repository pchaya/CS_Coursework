#include "cs163_graph.h"
using namespace std;

/* Implement these three functions for this lab */
table::table(int size)
{
      //Allocate the adjacency list and set each
    adjacency_list = new vertex [size];
    
    list_size = size;
    
    for (int i = 0; i < size; ++i)
    { 
        adjacency_list[i].entry = NULL;
        adjacency_list[i].head  = NULL;
    } 
    
    //head pointer to NULL
}

//Store the vertex at this location.
int table::insert_vertex(const journal_entry & to_add)
{
        //Place your code here
    bool is_added = false;
    int result = 0;
    int i = 0;
    for (i = 0; i < list_size && !is_added; ++i)
    {
        if (!adjacency_list[i].entry)
        {
            adjacency_list[i].entry = new journal_entry;
            result = adjacency_list[i].entry->copy_entry(to_add);
            is_added = true;
        }        
    }

    if (is_added && result == 0)
    {
        delete adjacency_list[i].entry;
        adjacency_list[i].entry = NULL;
    }

    return result;
}

//Attach an edge to a vertex
int table::insert_edge(char * current_vertex, char * to_attach)
{
    //Attach this vertices edge to the specified vertex
    int index_current = find_location(current_vertex);
    int index_to_attach = find_location(to_attach);

    //cout << index_current << " " << index_to_attach << endl;

    //adjacency_list[index_current]->head = 
    return 0;
}

//Display all vertices adjacent to the one specified
int table::display_adjacent(char * key_value)
{
    return 0;
}

//Find a location in the graph
//Consider this a helper function foro all of the other member functions!
int table::find_location(char * key_value)
{
    //return the location of this particular key value 
    for (int i = 0; i < list_size; ++i)
    {
        if (adjacency_list[i].entry -> compare(key_value))
            return i;
    }
  
    return 0;
}


