//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Professor Karla Fant.
//03/19/2017
//This header file includes the table class information along with the node
//structure, entry data structure, along with the function prototypes of the public/private table member functions.

#ifndef _table_
#define _table_

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;

const char filename [20] = "CS_term.txt";

const int MAX_SIZE_NAMES = 100;
const int MAX_SIZE_INFO = 3000;

//entry class for data members of each archive entry
struct entry
{
    char * term_name; // every entry will have keyword
    char * definition;

    //initialize these values when new instance is created
    entry()
    {
        term_name = NULL;
        definition = NULL;
    }


    void set_entry_data(char user_term_name [], char user_definition [])
    {
        term_name = new char [strlen(user_term_name) +1];
        strcpy(term_name, user_term_name);

        definition = new char [strlen(user_definition) +1];
        strcpy(definition, user_definition);
    }  

    ~entry()
    {
        if (term_name)
        {
            delete [] term_name;
            term_name = NULL;
        }

        if (definition)
        {
            delete [] definition;
            definition = NULL;
        }
    }

};


struct entry_node
{
    entry entry_data;
    entry_node * left_entry;
    entry_node * right_entry;

    entry_node()
    {
        left_entry = NULL;
        right_entry = NULL;
    }

    ~entry_node()
    {
        if(left_entry)
        {
            delete left_entry;
            left_entry = NULL;
        }
        if (right_entry)
        {
            delete right_entry;
            right_entry = NULL;
        }
    }

};

class table_archive
{
    public:
        table_archive();
        ~table_archive();
        int insert_entry(entry & user_entry);
        int remove_entry(char []);
        bool display_all();
        bool display_range(char first_char, char last_char);
        int retrieve(char to_retrieve [], entry & retrieved_entry);
        int get_height();
        bool is_efficient(); 
        bool load();
    private:
        void convert_to_upper(char [], char []);
        bool display_a_node(entry_node * a_node); 
        void display_all_worker(entry_node * root); 
        void display_range_worker(entry_node * root, char first_char, char last_char);
        int get_height_worker(entry_node * root);
        void insert_entry_worker(entry_node * to_add, entry_node * & root);
        void retrieve_worker(entry_node * root, char to_retrieve [], entry & retrieved_entry);
        void remove_entry_worker(entry_node * & root, char remove_keyword []);

        entry_node * root;

        ifstream file_in;
};

#endif
