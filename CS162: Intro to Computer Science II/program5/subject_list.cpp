//Prathyoosha Chaya, CS162
//Nov. 29 2016
//This implemention file includes class member functions.

#include "subject_list.h"

subject_list::subject_list()
{
    head = NULL;
}

subject_list::~subject_list()
{
    
}


//display_sort function: Displays all subjects sorted with their corresponding learned information, rating, and improv. ideas
//Parameters: None.
//Return values: None.
void subject_list::display_sort ()
{
    int i = 0;
    cout << endl << " archived subjects in database: " << endl;
    cout << "********************************" << endl;
    subject_node * current = head;

    while (current)
    {
        cout << "Subject name: " << current->name << "\n";
        cout << "Information learned: " << current->learned_info << "\n";
        cout << "Rating: " << current->rating << "\n";
        cout << "Improvement ideas: " << current->improve_info;
        cout << endl << endl;
        
        current = current -> next;
    } 
}


/*//Load function: Take information of text file and store into array of char.
//Parameters: None.
//Return values: None.
void subject_list::load()
{
    if (!m_psubjects)
    {
        cout << "Dynamic subject list not allocated." << endl;
        return;
    }
    //Create file input stream variable
    ifstream file_in;
    //Open file for input with string literal filename
    file_in.open("subject.txt");
    if (file_in) //to check if connected
    {
        char temp [SIZE_NAME];
        
        //initial check to set eof
        file_in.get(temp, SIZE_NAME, ';');
        file_in.ignore(100, ';');
    
        subject_node p_subject = new subject_node;
        subject_node * current = NULL;
        subject_node * prev = NULL; 


        //if reading operation is successful
        while (file_in && !file_in.eof())
        {
            strcpy(p_subject->name, temp);

            file_in.get(p_subject->learned_info, SIZE_INFO, ';');
            file_in.ignore(100, ';');
            file_in >> p_subject->rating;
            file_in.ignore(100, ';');
            file_in.get(p_subject->improve_info, SIZE_INFO, '\n');
            file_in.ignore(100,'\n');
            
            if(!head)
            {
                head = p_subject;
                current = head;
                prev = head; 
            }
            if (head) 
            {
                if(strcmp(p_subject-> data -> name, head -> data -> name) > 0)
                    {
                        current = head;
                        head = p_subject;
                        head -> next = current;
                    }
                current = head -> next;
                
                while(current && (strcmp(current -> name, p_subject -> name) < 0)
                {
                    if (!current)
                    {
                        prev -> next = p_subjects; 
                    }   
                    else 
                    {
                        prev -> next = p_subjects;
                        prev = current;
                        current = current -> next; 
                    }            
                }
            p_subject = new subject_node;

            //Move to next subject, then check first element for eof
            file_in.get(temp, SIZE_NAME, ';');
            file_in.ignore(100, ';');
            
        }
        file_in.close();;
    }
    else
        cout << "Error opening file subject.txt." << endl;

}
*/
//read function: Adds new subjects to end of dynamic array.
//Parameters: None.
//Return values: None.
void subject_list::read_sort()
{
    subject_node * p_subject = new subject_node;
    bool correct_rating = false; //to check if rating is between 0-10
       
        cout << "Please enter the name of the new subject: ";
        cin.get(p_subject -> name, SIZE_NAME, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter information learned of the new subject: ";
        cin.get(p_subject->learned_info, SIZE_INFO, '\n');
        cin.ignore(100, '\n');

        while (correct_rating == false)  //if user enters an invalid rating, the rating is not changed.
        {
            cout << "Please enter your rating of understanding this subject (0-10): ";
            cin >> p_subject ->rating;
            if (p_subject ->rating < 0 || p_subject->rating > 10)
                cout << "Invalid rating. Rate from 0-10." << endl;
            else
                correct_rating = true;
        }
        cin.ignore(100, '\n');
        cout << "Please enter improvement ideas for the new subject: ";
        cin.get(p_subject->improve_info, SIZE_INFO, '\n');
        cin.ignore(100, '\n');
        
        char temp[SIZE_NAME];

        subject_node * current = NULL;
        subject_node * prev = NULL; 


        if(!head)
            {
                head = p_subject;
                current = head;
                prev = head; 
            }
        if (head) 
            {
                if(!head->next)
                {
                    if(strcmp(p_subject-> name, head -> name) < 0)
                   {
                        current = head;
                        head = p_subject;
                        head -> next = current;
                   }
                    else if(strcmp(p_subject-> name, head -> name) > 0)
                    {
                        head -> next = p_subject;
                    }
                } 
                
                current = head;
                
                while(current && (strcmp(current -> name, p_subject -> name) < 0))
                {
                    if (!current)
                    {
                        prev -> next = p_subject; 
                    }   
                    else 
                    {
                        prev -> next = p_subject;
                        prev = current;
                        current = current -> next; 
                    }            
                }
            p_subject = new subject_node;

            
        }

}

/*
//write function: Writes contents of array back to file.
//Parameters: None.
//Return values: None.
void subject_list::write()
{
    //Create file output stream variable and index
    ofstream file_out;
    int i = 0;

    //Open file for output with string literal filename. Overwrite everything.
    file_out.open("subject.txt");

    //Check if file has successfully opened.
    if (!file_out)
        cout << "Error opening file." << endl;
    else
    {
        while (i < m_subject_count)
        {
            file_out << m_psubjects[i].name << ";";
            file_out << m_psubjects[i].learned_info << ";";
            file_out << m_psubjects[i].rating << ";";
            file_out << m_psubjects[i].improve_info << "\n";
            ++i;
        }
        file_out.close();
        cout << "Changes sucessfully saved to subject.txt" << endl;
    }
}


//search function: Searches for a match among all the existing subjects in the array.
//Parameters: User inputted subject.
//Return values: Index number of the subject if found, '-1' if not found.
int subject_list::search (char user_subject [])
{
    bool match_found = false;
    cout << endl << endl;

    int search_index = 0; //to store the index of subject's improvement info to be modified
    int return_val = -1;  
    char upper_subject[SIZE_NAME];
    char upper_name[SIZE_NAME];
    
    //Check for matches between user inputted subject and existing subjects
    for (search_index = 0; (search_index < m_subject_count && match_found == false); ++search_index)
    {
        upper_subject[0] = '\0';
        upper_name[0] = '\0';
        convert_upper(user_subject, upper_subject);
        convert_upper(m_psubjects[search_index].name, upper_name);
        
        if (strcmp(upper_subject, upper_name) == 0) //calls convert_upper function, as toupper only converts one character to uppercase
        {
            match_found = true;
            return_val = search_index;
        }

    }

    
    if (match_found == false)
        cout << "Subject not found." << endl;
    
    //cout << return_val;
    return return_val;
}

//remove function: This function removes an existing subject that the user has identified.
//Parameters: None.
//Return Values: None.
void subject_list::remove()
{
    char user_subject[SIZE_INFO]; //for the user's choice of subject
    int subject_index = 0;

    for (int i = 0; i < m_subject_count; ++i)
        cout << m_psubjects[i].name << endl;
    cout << "Please enter the name of the subject above to remove: ";
    cin.get(user_subject, '\n');
    cin.ignore(100, '\n');
    
    subject_index = search(user_subject);
    if(subject_index != -1)
    {
        for (int i = subject_index; i < m_subject_count; ++i)
        {
            strcpy(m_psubjects[i].name, m_psubjects[i+1].name);
            strcpy(m_psubjects[i].learned_info, m_psubjects[i+1].learned_info);
            m_psubjects[i].rating = m_psubjects[i+1].rating;
            strcpy(m_psubjects[i].improve_info, m_psubjects[i+1].improve_info);
        }
    }
    cout << user_subject << " removed." << endl;
}

//convert_upper function: Converts arrays of characters to uppercase to later compare user-inputted subject to existing subjects. Used for search function.
//Parameters: Original array, and uppercase array
//Return values: None.
void subject_list::convert_upper(char source[], char destination[])
{
    int i;
    //int size = sizeof(destination);
    memset(destination, 0, SIZE_NAME);
    //setting all values to NOT null terminating char, so that if previous destination array was shorter than current ("Arrays" vs. "Control Structures"), then the next loop will not terminate early.
    for(i = 0; source[i] != '\0'; ++i) //converts a char array to uppercase for use in other functions.
        destination[i] = toupper(source[i]);
    destination[i+1] = '\0';
}
*/
