//Prathyoosha Chaya, CS163, Professor Karla Fant
//Feb. 6 2017
//This implementation file includes class member functions.

#include "news_list.h"

news_list::news_list()
{
    head = NULL;
    topic_of_interest = NULL;
}

news_list::~news_list()
{
    if (head)
    {
        delete head;
        head = NULL;
    }
}

//add_news function: Adds a new story to the list
//Parameters: News story details from client to add
//Return Values: Integer value for error handling
int news_list::add_news (news & to_add)
{
    if (!topic_of_interest) //if topic of interest function has not successfully assigned interested topic
        return 0;
    if (!head)      //Empty list
    {
        head = new news_node;
        news_node * current = head;
        
        //copy over data
        copy_data_to_add(head, to_add);
        
        //empty list, so set nexts to null.
        current -> next_topic = NULL;
        current -> next_time = NULL;
    }
    
    else if (!head -> next_time) //One item in list
    {
        news_node * temp = head;

        //Adding based on time
        if (to_add.time_stamp < (head -> data.time_stamp))
        {
            temp = head -> next_time;
            head -> next_time = new news_node;
            copy_data_to_add(head -> next_time, to_add);
            
            head -> next_time -> next_time = temp;
        }

        else if (to_add.time_stamp >= (head -> data.time_stamp))
        {
            news_node * current = head -> next_time;
            current -> next_time = new news_node;
            copy_data_to_add(current -> next_time, to_add);
            current -> next_time -> next_time = NULL;
        } 
        //Adding based on topic
        if (strcmp(to_add.topic, topic_of_interest) == 0)
        {
            temp = head -> next_topic;
            head -> next_topic = new news_node;
            copy_data_to_add(head -> next_topic, to_add);
            
            head -> next_time -> next_topic = temp;
        }
        
        else if (strcmp(to_add.topic, topic_of_interest) != 0)
        {
            news_node * current = head -> next_topic;
            current -> next_topic = new news_node;
            copy_data_to_add(current -> next_topic, to_add);
            current -> next_topic -> next_topic = NULL;
        }
    }

    else    //Multiple items in list.
    {
        news_node * current = head;
        news_node * temp = current;
        bool has_added = false;  //to see if it has been added, used for adding to end.

        //Adding based on time:
        //Adding at head
        if ((to_add.time_stamp) <= (head -> data.time_stamp))
        {
            temp = head -> next_time;
            head -> next_time = new news_node;
            copy_data_to_add(head -> next_time, to_add);
            head -> next_time -> next_time = temp; 

            has_added = true;  
        }

        while (current -> next_time) //traversal
        {
           //adding after head 
           if ((to_add.time_stamp) <= (current -> next_time -> data.time_stamp))
           {
                temp = head -> next_time;
                head = new news_node; 
                copy_data_to_add(head, to_add);
                head -> next_time = temp;
               has_added = true; 
           } 
            
           else
               current = current -> next_time;
        }
        
        //Adding to end (hasn't entered prev. cases):
        if (!has_added)
        {
            while (current)
                current = current -> next_time;
            current -> next_time = new news_node;
            copy_data_to_add(current -> next_time, to_add);
            current -> next_time -> next_time = NULL;
        }


        //Traversing again to sort by topic
        current = head;
        temp = head;
        has_added = false;
        
        //Adding at head (does not require traversal)
        if (strcmp(to_add.topic, topic_of_interest) == 0)
        {
            temp = head -> next_topic;
            head -> next_topic = new news_node;
            copy_data_to_add(head -> next_topic, to_add);
            head -> next_topic -> next_topic = temp;
            has_added = true;
        }
        
        while (current -> next_topic)
        {
           //Adding after head
           if (strcmp(to_add.topic, current -> next_topic -> data.topic) == 0)
           {
                temp = current -> next_topic;
                current -> next_topic = new news_node;
                copy_data_to_add(current -> next_topic, to_add);
                current -> next_topic -> next_topic = temp;
                has_added = true;
           } 

           else
               current = current -> next_topic;
        }
        
        //Add to end of list
        if (!has_added)
        {
            while (current)
                current = current -> next_topic; //To make sure that current points to end of list
            current -> next_topic = new news_node;
            copy_data_to_add(current -> next_topic, to_add);
            current -> next_topic -> next_topic = NULL;
        } 
    }
    return 1;
}

//update_news function: This function allows the user to change any pre-existing news stories.
//Parameters: char array of user inputted title (to determine which story to update), and struct with information from user of changed information.
//Return Values: Boolean value, success or fail (at empty list).
bool news_list::update_news(char user_input [], news & to_add)
{
    if (!head)
      return false;
    news_node * current = head;

    while (current && !(strcmp(user_input, current -> data.title) == 0))
        current = current -> next_time;
      
    copy_data_to_add(current, to_add);
    return true; 

} 


//set_TopicOfInterest function: Sets the topic of interest of the user, to be used when displaying news in sorted order by topic.
//Parameters: Char array of user input.
//Return Values: Boolean value of if topic set was successful or not.
bool news_list::set_TopicOfInterest(char userTopic [])
{
    char upper_userTopic [MAX_SIZE_TITLE];
    //convert_upper(upper_userTopic, userTopic);  //upper_userTopic is now uppercase ver. of user's topic choice
    int i;
    memset (upper_userTopic, 0, MAX_SIZE_TITLE);
    
    for (i = 0; userTopic[i] != '\0'; ++i) //converts char array to uppercase for conparison use in other functions
        upper_userTopic[i] = toupper(userTopic[i]);
    upper_userTopic[i+1] = '\0';
    
   
    bool set_success = false;

    //Comparing to 3 possible topic choices:
    if(strcmp(upper_userTopic, "NEWS") == 0)
    {
        topic_of_interest = new char [strlen(upper_userTopic)+1];
        strcpy(topic_of_interest, "News");
        set_success = true;
    }
    else if(strcmp(upper_userTopic, "WEATHER") == 0)
    {
        topic_of_interest = new char [strlen(upper_userTopic)+1];
        strcpy(topic_of_interest, "Weather");
        set_success = true;
    }
    else if(strcmp(upper_userTopic, "TRAFFIC") == 0)
    {
        topic_of_interest = new char [strlen(upper_userTopic)+1];
        strcpy(topic_of_interest, "Traffic");
        set_success = true;
    }
     
    //cout << topic_of_interest;    
    return set_success;

}

//display_all function: Displays all of the news stories in chronological order. Wrapper function for display_all_worker function. To prevent from passing in a pointer to the list as a parameter.
//Parameters: None.
//Return Value: Boolean value of success or failure (empty list)
bool news_list::display_all()
{
    bool display_result = false;
    cout << endl << "********************************" << endl;
    display_result = display_all_worker(head);
    return display_result;
}

//display_all_worker function: Recursively displays all news stories in chronological order
//Parameters: Pointer to starting node
//Return Value: Boolean value, success or failure (empty list)
bool news_list::display_all_worker(news_node * current)
{
    if (!current)
        return false;
    if (current)
    {   
        cout << endl;
        if (current -> data.favorited)
            cout << "** FAVORITED!! **" << endl;
        cout << "Title: " << current -> data.title << endl
             << "Topic: " << current -> data.title << endl
             << "Description: " << current -> data.desc << endl
             << current -> data.time_stamp << " hrs. ago." << endl
             << "Source: " << current -> data.source << endl;
    }
    display_all_worker(current -> next_time);
    return true;
}

//display_recent function: displays all stories until the specified time stamp passed in as a parameter.
//Parameters: The latest time to display news stories by.
//Return Values: Boolean value, success or failure (empty list)
bool news_list::display_recent(int latest_time)
{
    if (!head)
        return false;
    news_node * current = head;
    cout << endl << "********************************" << endl;

    while(current && ((current -> data.time_stamp) < latest_time))
    {
        cout << endl;
        if (current -> data.favorited)
            cout << "** FAVORITED!! **" << endl;
        cout << "Title: " << current -> data.title << endl
             << "Topic: " << current -> data.title << endl
             << "Description: " << current -> data.desc << endl
             << current -> data.time_stamp << " hrs. ago." << endl
             << "Source: " << current -> data.source << endl;
    }       
   return true; 
}

//display_interest function: displays all news stories that are categorized under the same topic is the one the user has picked as being interested in.
//Parameters: None.
//Return Values: Boolean value, success marker (failure if topic of interest is not specified or list is empty.)
bool news_list::display_interest()
{
    if (!head || !topic_of_interest)
        return false;
    news_node * current = head;
    cout << endl << "********************************" << endl;

    while(current && (strcmp(current -> data.topic, topic_of_interest)))
    {
        cout << endl;
        if (current -> data.favorited)
            cout << "** FAVORITED!! **" << endl;
        cout << "Title: " << current -> data.title << endl
             << "Topic: " << current -> data.title << endl
             << "Description: " << current -> data.desc << endl
             << current -> data.time_stamp << " hrs. ago." << endl
             << "Source: " << current -> data.source << endl;
    }       
   return true; 
}

//remove_older function: This function removes all news stories older than a specified time stamp.
//Parameters: The time stamp to keep stories up until - specified by user.
//Return Values: Integer value of the number of items removed. if the value is >= 0 then it is considered success (with 0 meaning no items are removed), and -1 is returned if the list is empty. 
int news_list::remove_older(int latest_timestamp) 
{
    if (!head)
        return -1;
    news_node * current = head -> next_time;
    news_node * prev = current;
    int remove_count = 0;
    while(current && (current->data.time_stamp < latest_timestamp))
    {
        prev = current;
        current = current -> next_time;
    }
    news_node * temp = current;
    while (current)
    {
        temp = current -> next_time;
        delete current;
        prev -> next_time = temp;
        current = temp;
        ++remove_count;
    }
    return remove_count;
}

//favorite_story function: Allows the user to mark a story as their favorite, which will be distinguished when displaying.
//Parameters: The char array of user input to match the favorite story's name.
//Return Value: Boolean, success/failure (empty list)
bool news_list::favorite_story(char user_input [])
{
   if (!head)
      return false;
   news_node * current = head;
   int i;
   char user_input_upper [MAX_SIZE_TITLE];
   
   while (current)
   {
       if (strcmp(current -> data.title, user_input) == 0)
          current -> data.favorited = true;
       else
          current = current -> next_time; 
    }
    return true;
}


//copy_data_to_add function: Copies the data to add from user to the data of the current node
//Parameters: Node to copy into, source news data (from user)
//Return Values: None. 
void news_list::copy_data_to_add(news_node *& current, news & to_add)
{
    cout << to_add.title;
    //copy over data for dynamic char arrays
    current -> data.title = new char [strlen(to_add.title)+1];
    strcpy(current -> data.title, to_add.title);

    current -> data.topic = new char [strlen(to_add.topic)+1];
    strcpy(current -> data.topic, to_add.topic);

    current -> data.desc = new char [strlen(to_add.desc)+1];
    strcpy(current -> data.desc, to_add.desc);
 
    current -> data.source = new char [strlen(to_add.source)+1];
    strcpy(current -> data.source, to_add.source);
   
    //copy time stamp and set favorited info. archive num. is not set here.
    current -> data.time_stamp = to_add.time_stamp;
    
    current -> data.favorited = false;
} 


