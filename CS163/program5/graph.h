//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//03/19/2017
//This header file includes the graph class information along with the vertex
//structure, node structure, along with the function prototypes of the public/private table member functions.

#ifndef _graph_
#define _graph_

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

const int MAX_SIZE_NAME = 100;
const int MAX_SIZE_ARRAY = 10;  //ADJACENCY LIST SIZE IS 10 ELEMENTS

//entry class for data members of each vertex
struct vertex
{
    char * name; // every entry will have name
    struct node * head;
    bool visited;
    
    vertex();
    ~vertex();

    void set_vertex(char user_name [])
    {
        name = new char [strlen(user_name) +1];
        strcpy(name, user_name);
    }  

};

    
struct node
{
    vertex * adjacent;
    node * next;

    node();
    ~node(); 

};

class graph
{
    public:
        graph();
        ~graph();
        int insert_vertex(char name []);
        int insert_edge(int source, int destination);
        bool display_all(int source);
    private:

        vertex * adjacency_list;

};

#endif
