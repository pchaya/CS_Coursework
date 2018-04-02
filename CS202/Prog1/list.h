//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/18/2017
//This header file includes the class definitions of the list
//class. 

#ifndef _list_
#define _list_

#include <iostream>
#include <cctype>
#include <cstring>
#include "stdlib.h"
#include "maze.h"

using namespace std;

class player: public maze 
{
    public:
        player();
        void set_player_num(int to_set);
        void set_friend_num(int to_set);
        void set_location(int);
        int get_location();
        checkpoint * get_checkpoint();

    protected:
        //checkpoint * current_location;
        int player_num;
        int friend_num;
        int current_location_num;

};

/*
class group
{
    public:
        list();
        ~list();
        add

    private:



};
*/

#endif

