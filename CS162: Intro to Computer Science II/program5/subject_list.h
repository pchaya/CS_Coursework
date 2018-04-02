//Prathyoosha Chaya, CS 162
//Nov. 29 2016
//This header file contains the function prototypes, constants, struct definition, and the class interface.

#ifndef _subject_list_    //To prevent from compiling this header file multiple times
#define _subject_list_    //Define after entered once

#include <iostream>
//#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

const int SIZE_NAME = 21;
const int SIZE_INFO = 301;

struct subject_node
{
    char name [SIZE_NAME];
    char learned_info [SIZE_INFO];
    int rating;
    char improve_info [SIZE_INFO];

    subject_node * next;
    
    subject_node()
    {
        next = NULL;
        name[0] = '\0';
        learned_info[0] = '\0';
        rating = 0;
        improve_info[0] = '\0';
    }
    ~subject_node()
    {
        if(next)
        {
            delete next;
            next = NULL;
        } 
    }


};

class subject_list
{
    public:
        subject_list();
        ~subject_list();
        void read_sort ();
//        void load ();
        void display_sort ();
//        void write ();
//        int search ();
//        void remove ();

    private:
        subject_node * head;
//        int m_subject_count;
//        int m_max_num_subjects;
        void convert_upper(char source[], char destination[]);

};

#endif
