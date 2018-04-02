//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/18/2017
//This implementation file includes the function implementations of the
//list class functions. 

#include "list.h"

player::player()
    :player_num(0), current_location_num(0)
{
    
}

void player::set_player_num(int to_set)
{
    player_num = to_set;
}

void player::set_friend_num(int to_set)
{
    friend_num = to_set;
}

void player::set_location(int to_set)
{
    current_location_num = to_set;
}

int player::get_location()
{
    return current_location_num;
} 

checkpoint * player::get_checkpoint()
{
    return &adjacency_list[current_location_num];
}


