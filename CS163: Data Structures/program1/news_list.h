//Prathyoosha Chaya, CS163, Professor Karla Fant
//Feb. 6 2017
//This header file contains the function prototypes, struct definition,
//constants, and the class interface.

#ifndef _subject_list_      //To prevent from compiling this header file multiple times
#define _subject_list_      //Define after entering once.

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_SIZE_TITLE = 201;
const int MAX_SIZE_DESC = 1001;
const int MAX_SIZE_SOURCE = 21;

struct news
{
    char * title;                //Information on news
    char * topic;
    char * desc;
    float time_stamp;
    char * source;
    bool favorited;             //If a user favorites a story
};

struct news_node
{
    news data;

    news_node * next_topic;     //Links to other nodes (two threads)
    news_node * next_time;

    news_node()
    {
        data.title = NULL;
        data.topic = NULL;
        data.desc = NULL;
        data.time_stamp = 0.0;
        data.source = NULL;
        data.favorited = false;

        next_topic = NULL;
        next_time = NULL;
    }

    ~news_node()
    {
        if (data.title)
        {
            delete [] data.title;
            data.title = NULL;
        }

        if (data.topic)
        {
            delete [] data.topic;
            data.topic = NULL;
        }

        if (data.desc)
        {
            delete [] data.desc;
            data.desc = NULL;
        }

        if (data.source)
        {
            delete [] data.source;
            data.source = NULL;
        }

        if (next_topic)
        {
            delete next_topic;
            next_topic = NULL;
        }

        if (next_time)
        {
            delete next_time;
            next_time = NULL;
        }
    }


};

//News class definition:
class news_list
{
    public:
        news_list();
        ~news_list();
        int add_news(news &);
        bool update_news(char [], news &);
        bool set_TopicOfInterest(char []);
        bool display_all();
        bool display_recent(int);
        bool display_interest();
        int remove_older(int);
        bool favorite_story(char []);

    private:
        news_node * head;
        bool display_all_worker(news_node *);   //Worker function for display_all() wrapper
        void copy_data_to_add(news_node *&, news &);
        char * topic_of_interest;

};

#endif


