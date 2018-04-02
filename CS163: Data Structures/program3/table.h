//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//This header file includes the table class information along with the node
//structure, entry data structure, along with the function prototypes of the public/private table member functions.

#ifndef _table_
#define _table_

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;

const char filename [20] = "CS163_pokemon.txt";

const int MAX_SIZE_NAMES = 100;
const int MAX_SIZE_INFO = 3000;

const int HASH_TABLE_SIZE = 37;

//entry class for data members of each archive entry
struct entry
{
    char * keyword; // every entry will have keyword
    //Whether the data item is a Pokemon, Regional info., or a general term
    //Will be 0, 1, or 2 
    int info_type;
    char * background;
    char * evolution;
    int evo_candy;
    char * evo_info;

    //Regional info.
    char * list_of_pokemon;     //list of pokemon in area
    int num_of_unique_pokemon;

    //General pokemon terms
    char * term_info;

    //initialize these values when new instance is created
    entry()
    {
        keyword = NULL;
        info_type = 0;
        background = NULL;
        evolution = NULL;
        evo_candy = 0;
        evo_info = NULL;
        
        list_of_pokemon = NULL;
        num_of_unique_pokemon = 0;
        term_info = NULL;
    }


    void set_entry_data(char user_keyword [], int user_info_type, char user_background [],char user_evolution [], int user_evo_candy, char user_evo_info [], char user_list_of_pokemon [], int user_num_of_unique_pokemon, char user_term_info [])
    {
        keyword = new char [strlen(user_keyword) +1];
        strcpy(keyword, user_keyword);

        info_type = user_info_type;

        background = new char [strlen(user_background) +1];
        strcpy(background, user_background);

        evolution = new char [strlen(user_evolution) +1];
        strcpy(evolution, user_evolution);

        evo_candy = user_evo_candy;

        evo_info = new char [strlen(user_evo_info) +1];
        strcpy(evo_info, user_evo_info);

        list_of_pokemon = new char [strlen(user_list_of_pokemon) +1];
        strcpy(list_of_pokemon, user_list_of_pokemon);

        num_of_unique_pokemon = user_num_of_unique_pokemon;

        term_info = new char [strlen(user_term_info) +1];
        strcpy(term_info, user_term_info);
    }  

    ~entry()
    {
        if (keyword)
        {
            delete [] keyword;
            keyword = NULL;
        }

        if (background)
        {
            delete [] background;
            background = NULL;
        }

        if (evolution)
        {
            delete [] evolution;
            evolution = NULL;
        }

        if (evo_info)
        {
            delete [] evo_info;
            evo_info = NULL;
        }
        
        if (list_of_pokemon)
        {
            delete [] list_of_pokemon;
            list_of_pokemon = NULL;
        }

        if (term_info)
        {
            delete [] term_info;
            term_info = NULL;
        }
    }

};


struct entry_node
{
    entry entry_data;
    entry_node * next_entry;

    entry_node()
    {
        next_entry = NULL;
    }
};

class table_archive
{
    public:
        table_archive();
        ~table_archive();
        int add_info(entry & user_entry);
        int remove_entry(char []);
        bool display_all();
        int retrieve(char []); 
        bool load();
    private:
        int hash_function(char * key);
        void convert_to_upper(char [], char []);
        bool display_a_node(entry_node * a_node); 
        
        entry_node ** hash_table;

        int entry_count;
        ifstream file_in;
        ofstream file_out;
};

#endif
