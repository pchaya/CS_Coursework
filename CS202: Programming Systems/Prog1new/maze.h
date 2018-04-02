//Prathyoosha Chaya, CS202 PROGRAMMING SYSTEMS, Prof. Karla Fant
//04/30/2017
//This header file contains the class definitions.

#ifndef _maze_h_
#define _maze_h_

#include <iostream>
#include <cstring>
#include <cctype>
#include "stdlib.h"

using namespace std;

const int MAX_NUM_OF_CKPT = 20; 

//forward declarations
class Ckpt;
class Friends_list;


class Graph_node
{
    public:
        Graph_node();
        Graph_node(Ckpt * to_connect);
        ~Graph_node();
        void set_next(Graph_node * next_node);
        void set_prev(Graph_node * prev_node);
        Graph_node * next_node();
        Graph_node * prev_node();
        Ckpt * get_connected_ckpt();

    private:
        Ckpt * connected_ckpt;
        Graph_node * prev;
        Graph_node * next;

};

class Obj   //generic object, parent to player and reward, so that we can have a general List class
{
    public:
        Obj(int ID_to_set = -1);
        int get_ID();

    protected:
        int ID;


};

class List_node
{
    public:
        List_node();
        ~List_node(); 
        bool add_item(Obj * p_Obj);      //find index, and set data
        List_node * next_node();
        Obj * get_data(int index);
        void set_next(List_node * next_node);

   private:
        Obj * data [2];
        List_node * next;
};

class List
{
    public:
        List();
        ~List();
        void add_obj(Obj * p_Obj);
        Obj * get_obj(int ID); 

    protected:
        List_node * head;       //linked list of arrays
};

class Reward:public Obj
{
    public:
        Reward();
        Reward(int ID, char * description);
        void display_desc();
                
    private:
        char * desc;

};


class Spinner: public List      //list of rewards to be spun
{
    public:
        Spinner();
        Reward * spin();
        Reward * get_reward(int ID);


};

class Maze
{
    public:
        Maze();
        ~Maze();
        int build_maze();
        bool insert_edge(Ckpt * source, Ckpt * destination);
        Ckpt * get_ckpt(int ID);
        int get_num_of_ckpnts();

    private:
        Ckpt * adjacency_list;
        int num_of_ckpts;
};


class Ckpt 
{
    public:
        //initialize ID with -1 for invalid checkpoint
        Ckpt();
        ~Ckpt();
        void init(int new_ID, bool is_end = false, int num_connections = 0);
        bool add_node(Ckpt * to_set);
        int get_ID();
        void display_connected();
        int get_num_of_connections();

    private:
        int ID;
        bool is_end;
        int num_of_connections;
        Graph_node * head;


};

//an individual player, each player contains their location, reward, and a list
//of their friends.
class Player:public Obj
{
    public:
        Player();
        Player(int player_num, Spinner * game_spinner, Maze * game_maze, Ckpt * start_location);
        void take_turn();   //call redeem, then move, then spin
        Reward * get_reward();
        void clear_reward();
        void set_friends_list(Friends_list * my_friends);
        bool is_player_done();
                
    private:
        //int player_num; in Obj class
        Ckpt * move();                          //always called after redeem, and before spin
        void spin();      //game class will call the player's spin func.. There is only one instance of spinner ,which each player has access to.
        void redeem_reward();       //will have switch statement to call the appropriate reward execuation based on reward held. 

        //private members
        Reward * a_reward;
        Spinner * game_spinner;
        Maze * game_maze;
        Ckpt * location;
        //Player * next;
        Friends_list * friends;     //linked list of arrays

        bool is_done;
};


class Friends_list: public List     //player implementation of LL of Arrays
{
    public:
        void add_player(Player * a_player);
        Player * get_my_friend(Player * a_player);

};

class Game
{
    public:
        Game();
        ~Game();
        void begin_game();
        void play_game();

    private:
        Spinner * game_spinner;
        Maze * game_maze;
        Friends_list * groups [2];
    
        Player * players [4];
};

#endif
