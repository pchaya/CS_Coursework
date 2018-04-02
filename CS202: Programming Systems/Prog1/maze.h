//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/18/2017
//This header file includes the class definitions of the checkpoint and maze_node
//class. 

#ifndef _maze_
#define _maze_

#include <iostream>
#include <cctype>
#include <cstring>
#include "stdlib.h"

using namespace std;

const int MAX_SIZE_NAME = 100;
const int MAX_SIZE_ARRAY = 20;  //ADJACENCY LIST SIZE IS 20 ELEMENTS

    
class maze_node
{
    public:
        maze_node();
        ~maze_node(); 

        class checkpoint * adjacent;
        maze_node * next;
        maze_node * prev;
};


//checkpoint (checkpoint) class for maze representation 
class checkpoint: public maze_node
{
    public:
        checkpoint();
        ~checkpoint();
        
    protected:
        void set_checkpoint(char user_name []);

        char * name; // every checkpoint will have name
        maze_node * head;
        bool start_or_finish; //if the checkpoint is the start or end of maze
        int num_of_paths;
    
};

class maze
{
    public:
        maze();
        ~maze();
        int build_maze(int num_of_checkpoints);
        bool display_all(int source);
        checkpoint * get_adjacency_list();
        int insert_checkpoint(char name []);
        int insert_edge(int source, int destination);
    protected:
        checkpoint * adjacency_list;
};

#endif
