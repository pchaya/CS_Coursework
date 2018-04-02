//Prathyoosha Chaya, CS 163, Professor Karla Fant
//Feb. 6 2017
//This implementation file contains the main function and other utility functions such as the menu function and convert to upper.

#include "news_list.h"

int menu();
void convert_upper(char source[], char destination[]);

int main()
{
    news user_story;  //Instance of the news object for user to pass into functions.
    news_list news_archive;

    bool run_again = true;
    int menu_option = 0;
    int integer_result = 0; //For function returns
    bool result = false;

    //Variables for creating user_story object to pass into add_story function.    
    char temp_title [MAX_SIZE_TITLE];
    char temp_topic [MAX_SIZE_TITLE];
    char temp_desc [MAX_SIZE_DESC];
    char temp_source [MAX_SIZE_SOURCE];
    char temp_topicOfInterest [MAX_SIZE_TITLE];
    char temp_fav_story_title [MAX_SIZE_TITLE];
    char is_favorite = 'n';
    int latest_time_hrs = 0;

    cout << "Welcome to the CS163 news archive." << endl;
    result = false;
    while (!result)
    {
        temp_topicOfInterest[0] = '\0';
        cout << "What is your topic of interest (news, weather, or traffic): ";
        cin.get(temp_topicOfInterest, MAX_SIZE_TITLE-1);
        cin.ignore(100, '\n');
        result = news_archive.set_TopicOfInterest(temp_topicOfInterest);
        if (!result)
            cout << "Not a valid topic, enter again." << endl;
    }

    while (run_again) //Displays menu to ask user for next steps after each completed task
    {
        
        menu_option = menu();    //Recieve user-chosen option from menu function
        switch (menu_option)
        {
            case 1: cout << endl << "Please enter title of news story: "; //Title set
                    cin.get(temp_title, MAX_SIZE_TITLE-1);
                    cin.ignore(100, '\n');
                    user_story.title = new char [strlen(temp_title)+1];
                    strcpy(user_story.title, temp_title);
                    
                    cout << "Title: " << user_story.title;

                    //Topic set
                    cout << endl << "Please enter topic of story (news, weather, or traffic): ";
                    char temp_topic_upper[MAX_SIZE_TITLE-1]; //To store upper ver. for comparison
                    cin.get(temp_topic, MAX_SIZE_TITLE-1);
                    cin.ignore(100, '\n');
                    //Comparing to 3 possible topic options
                    convert_upper(temp_topic_upper, temp_topic);
                    if (strcmp(temp_topic_upper, "NEWS") == 0)
                    {
                        strcpy(temp_topic, "News");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    } 
                    if (strcmp(temp_topic_upper,"WEATHER") == 0)
                    {
                        strcpy(temp_topic, "Weather");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    }
                    if (strcmp(temp_topic_upper, "TRAFFIC") == 0)
                    {
                        strcpy(temp_topic, "Traffic");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    }

                    //Description set
                    cout << endl << "Please enter description of news story: ";
                    cin.get(temp_desc, MAX_SIZE_DESC-1);
                    cin.ignore(100, '\n');
                    user_story.desc = new char [strlen(temp_desc)+1];
                    strcpy(user_story.desc, temp_desc);

                    //Time stamp set
                    cout << endl << "Please enter how many hrs ago the story occured (ex.: 6): ";
                    cin >> user_story.time_stamp;
                    cin.ignore(100, '\n');

                    //Source set
                    cout << endl << "Please enter the source of news (ex.: KOIN): "; 
                    cin.get(temp_source, MAX_SIZE_SOURCE-1);
                    cin.ignore(100, '\n');
                    user_story.source = new char [strlen(temp_source)+1];
                    strcpy(user_story.source, temp_source);

                    //Determining if favorite (can also be set later)
                    cout << endl << "Would you like to favorite this story? (y/n): ";
                    cin >> is_favorite;
                    cin.ignore(100, '\n');
                    if (is_favorite == 'y' || is_favorite == 'Y')
                        user_story.favorited = true;
                    else
                        user_story.favorited = false;  

                    integer_result = news_archive.add_news(user_story);
                    if (!integer_result)
                        cout << "\nPlease set a topic of interest." << endl;

                    break;
            case 2: result = false;
                    cout << endl;
                    result = news_archive.display_all();
                    if (!result)
                        cout << "No news items in archive." << endl;
                    cout << "Please enter the nane of the story you would like to update: ";
                    cin.get(temp_fav_story_title, MAX_SIZE_TITLE -1); 
                    cin.ignore(100, '\n');
                    
                    cout << endl << "Please enter new title of news story: "; //Title set
                    cin.get(temp_title, MAX_SIZE_TITLE-1);
                    cin.ignore(100, '\n');
                    user_story.title = new char [strlen(temp_title)+1];
                    strcpy(user_story.title, temp_title);

                    //Topic set
                    cout << endl << "Please enter new topic of story (news, weather, or traffic): ";
                    cin.get(temp_topic, MAX_SIZE_TITLE-1);
                    cin.ignore(100, '\n');
                    //Comparing to 3 possible topic options
                    convert_upper(temp_topic_upper, temp_topic);
                    if (strcmp(temp_topic_upper, "NEWS") == 0)
                    {
                        strcpy(temp_topic, "News");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    } 
                    if (strcmp(temp_topic_upper,"WEATHER") == 0)
                    {
                        strcpy(temp_topic, "Weather");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    }
                    if (strcmp(temp_topic_upper, "TRAFFIC") == 0)
                    {
                        strcpy(temp_topic, "Traffic");
                        user_story.topic = new char [strlen(temp_topic)+1];
                        strcpy(user_story.topic, temp_topic);
                    }

                    //Description set
                    cout << endl << "Please enter new description of news story: ";
                    cin.get(temp_desc, MAX_SIZE_DESC-1);
                    cin.ignore(100, '\n');
                    user_story.desc = new char [strlen(temp_desc)+1];
                    strcpy(user_story.desc, temp_desc);

                    //Time stamp set
                    cout << endl << "Please enter how many hrs ago the story occured (ex.: 6): ";
                    cin >> user_story.time_stamp;
                    cin.ignore(100, '\n');

                    //Source set
                    cout << endl << "Please enter the new source of news (ex.: KOIN): "; 
                    cin.get(temp_source, MAX_SIZE_SOURCE-1);
                    cin.ignore(100, '\n');
                    user_story.source = new char [strlen(temp_source)+1];
                    strcpy(user_story.source, temp_source);

                    //Determining if favorite (can also be set later)
                    cout << endl << "Would you like to favorite this story? (y/n): ";
                    cin >> is_favorite;
                    cin.ignore(100, '\n');
                    if (is_favorite == 'y' || is_favorite == 'Y')
                        user_story.favorited = true;
                    else
                        user_story.favorited = false;  


                    result = news_archive.update_news(temp_fav_story_title, user_story);
                    if (!result)
                        cout << "No news in the archive." << endl;
                    break;

            case 3: result = false;
                    while (!result)
                    {
                        temp_topicOfInterest[0] = '\0';
                        cout << "Please select a topic of interest (news, weather, or traffic): ";
                        cin.get(temp_topicOfInterest, MAX_SIZE_TITLE-1);
                        cin.ignore(100, '\n');
                        result = news_archive.set_TopicOfInterest(temp_topicOfInterest);
                        if (!result)
                            cout << "Not a valid topic, enter again." << endl;
                    }
                    break;

            case 4: result = false;
                    cout << endl;
                    result = news_archive.display_all();
                    if (!result)
                        cout << "No news items in archive." << endl;
                    cout << "Please enter the nane of the story you would like to favorite.: ";
                    cin.get(temp_fav_story_title, MAX_SIZE_TITLE -1); 
                    cin.ignore(100, '\n');
                    result = news_archive.favorite_story(temp_fav_story_title);
                    if (!result)
                        cout << "No news in the archive." << endl;
                    break;

            case 5: integer_result = 0;
                    cout << "Stories older than __ hours should be replaced: (ex.: 7): ";
                    cin >> latest_time_hrs;
                    cin.ignore(100, '\n');
                    cout << endl;
                    integer_result = news_archive.remove_older(latest_time_hrs);
                    if (integer_result <= 0)
                        cout << "No news in archive." << endl;
                    break;

            case 6: result = false;
                    result = news_archive.display_all();
                    break;
                             
            
            case 7: result = false;
                    cout << "How recent would you like your news to be in hours? (ex. 4): ";
                    cin >>  latest_time_hrs;
                    cin.ignore(100, '\n');
                    cout << endl;
                    result = news_archive.display_recent(latest_time_hrs);
                    
                    if (!result)
                        cout << "No news items archived." << endl;
                    break;

            case 8: result = false;
                    result = news_archive.display_interest();
                    
                    if (!result)
                        cout << "No news items archived." << endl;
                    break;

            case 9: cout << "Thank you for using news archive.\n\n";
                    run_again = false;
                    break;
            default: cout << "Invalid menu choice." << endl;
                     break;
        }
    }  
    return 0; 
}

//menu function: Outputs the menu for the user to select
//Parameters: None.
//Return Values: Integer of user-inputted menu selection.
int menu()
{
    int option = 0;
    cout << endl;
    cout << "\t1: Add a news story.\n"
        "\t2: Update a news story.\n"
        "\t3: Set a topic of interest.\n"
        "\t4: Favorite a story.\n"
        "\t5: Remove older stories.\n"
        "\t6: Display all (chronologically).\n"
        "\t7: Display recent.\n"
        "\t8: Display interested topic's stories.\n"
        "\t9: Quit news archive.\n";
    cout << "Please choose the number of which option to execute: ";
    cin >> option;
    cin.ignore(100, '\n');

    return option;
}


//convert_upper function: Converts arrays of characters to uppercase to later compare user-inputted topic to existing topics.
//Parameters: Original array, uppercase array.
//Return Values: None.
void convert_upper(char source[], char destination[])
{
    int i;
    memset (destination, 0, MAX_SIZE_TITLE);
    
    for (i = 0; source[i] != '\0'; ++i) //converts char array to uppercase for conparison use in other functions
        destination[i] = toupper(source[i]);
    destination[i+1] = '\0';

}
