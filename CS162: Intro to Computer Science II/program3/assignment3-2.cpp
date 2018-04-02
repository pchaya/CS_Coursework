//Prathyoosha Chaya, CS 162, Coleen Toth
/* The purpose of this program is to archive the user's data on subjects learned in CS162 so far. Functionality: User can add new subjects, display all old subjects&information, edit ratings on understanding, and create/load new improvement ideas. */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

const int SIZE_NAME = 21;
const int SIZE_INFO = 301;

struct subject
{
    char name[SIZE_NAME];
    char learned_info[SIZE_INFO];
    int rating;
    char improve_info[SIZE_INFO];
};

//Function prototypes
void read (subject a_subject[], int& subject_count);
void display (subject a_subject[], int subject_count);
void write (subject a_subject[], int& subject_count);
int menu ();
void add_subject(subject a_subject[], int& subject_count);
void edit_rating (subject a_subject[], int subject_count);
void improvement_ideas (subject a_subject[], int subject_count);
void convert_upper(char source[], char destination[]);


int main()
{
    subject a_subject[20];
    int subject_count = 0;
    int menu_option = 0;
    bool run_again = true;
 
    cout << "Welcome to the CS162 archive." << endl;
    read(a_subject, subject_count);
   

    while (run_again) //This display the menu and ask the user of the next step every time a task is completed
    {
        menu_option = menu(); //Receive user chosen option from menu function
    
        switch (menu_option)
        {
            case 1: display(a_subject, subject_count);
                    break;
            case 2: add_subject(a_subject, subject_count);
                    break;
            case 3: edit_rating(a_subject, subject_count);
                    break; 
            case 4: improvement_ideas(a_subject, subject_count);
                    break;
            case 5: write(a_subject, subject_count);
                    run_again = false;
                    break; 
            case 6: run_again = false;
                    break;
            default: cout << "Invalid menu choice." << endl;
                    break;
        } 
    }    
}

//menu function: Outputs the menu for the user to select.
//Parameters: None.
//Return values: Integer of user-inputted menu selection.
int menu ()
{
    int option = 0; 
    cout << endl;
    cout << "\t1: Display all subjects.\n"
            "\t2: Add a new subject.\n"
            "\t3: Edit ratings of subjects.\n"
            "\t4: Create/Load improvement ideas.\n"
            "\t5: Save to archive and quit.\n"
            "\t6: Quit WITHOUT saving.\n";
    cout << "Please choose the number of which option to execute: ";
    cin >> option;
    cin.ignore(100, '\n');

    return option;
}

//read function: Take information of text file and store into array of char.
//Parameters: Array of structs "a_subject", and array index counter by reference.
//Return values: None.
void read (subject a_subject[], int& subject_count)
{
    //Create file input stream variable
    ifstream file_in;
    //Open file for input with string literal filename
    file_in.open("subject.txt");
    
    if (file_in) //to check if connected
    {
        //initial check to set eof
        file_in.get(a_subject[subject_count].name, SIZE_NAME, ';');
        file_in.ignore(100, ';');

        //if reading operation is successful
        while (file_in && !file_in.eof() && subject_count <= 20)
        {
            file_in.get(a_subject[subject_count].learned_info, SIZE_INFO, ';');
            file_in.ignore(100, ';');
            file_in >> a_subject[subject_count].rating;
            file_in.ignore(100, ';');
            file_in.get(a_subject[subject_count].improve_info, SIZE_INFO, '\n');
            file_in.ignore(100, '\n');
            ++subject_count; //Move to next subject, then check first element for eof

            file_in.get(a_subject[subject_count].name, SIZE_NAME, ';');
            file_in.ignore(100, ';');
        }
        file_in.close();;       
    }
    else
        cout << "Error opening file subject.txt. " << endl;
}

//display function: Displays all subjects with their corresponding learned information, rating, and improv. ideas
//Parameters: Array of structs "a_subject", and array index counter by value.
//Return values: None.
void display (subject a_subject[], int subject_count)
{
    int i = 0;
    cout << endl << subject_count << " archived subjects in database: " << endl;
    cout << "********************************" << endl;
    while (i < subject_count)
    {
        cout << "Subject name: " << a_subject[i].name << "\n";
        cout << "Information learned: " << a_subject[i].learned_info << "\n";
        cout << "Rating: " << a_subject[i].rating << "\n";
        cout << "Improvement ideas: " << a_subject[i].improve_info;
        cout << endl << endl;
        ++i;
    } 
}

//write function: Writes contents of array back to file.
//Parameters: Array of structs "a_subject", and array index counter by reference.
//Return values: None.
void write (subject a_subject[], int& subject_count)
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
        while (i <subject_count)
        {
            file_out << a_subject[i].name << ";";
            file_out << a_subject[i].learned_info << ";";
            file_out << a_subject[i].rating << ";";
            file_out << a_subject[i].improve_info << "\n";
            ++i;
        }
        file_out.close();
        cout << "Changes sucessfully saved to subject.txt" << endl;
    }
}

//add_subject function: Adds new subjects to end of array.
//Parameters: Array of structs "a_subject", and array index counter by reference.
//Return values: None.
void add_subject(subject a_subject[], int& subject_count)
{
    bool correct_rating = false; //to check if rating is between 0-10
    if (subject_count < 20)
    {
        cout << "Please enter the name of the new subject: ";
        cin.get(a_subject[subject_count].name, SIZE_NAME, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter information learned of the new subject: ";
        cin.get(a_subject[subject_count].learned_info, SIZE_INFO, '\n');               
        cin.ignore(100, '\n');

        while (correct_rating == false)  //if user enters an invalid rating, the rating is not changed.
        {
            cout << "Please enter your rating of understanding this subject (0-10): ";
            cin >> a_subject[subject_count].rating;
            if (a_subject[subject_count].rating < 0 || a_subject[subject_count].rating > 10)
                cout << "Invalid rating. Rate from 0-10." << endl;
            else
                correct_rating = true;
        }
        cin.ignore(100, '\n');
        cout << "Please enter improvement ideas for the new subject: ";
        cin.get(a_subject[subject_count].improve_info, SIZE_INFO, '\n');
        cin.ignore(100, '\n');

        ++subject_count; //Increase current number of subjects
    }
    else
        cout << "Subjects full." << endl;
}
//edit_rating function: Edits rating of any previously entered subjects.
//Parameters: Array of structs "a_subject", and array index counter by value.
//Return values: None.
void edit_rating (subject a_subject[], int subject_count)
{
    char user_subject[SIZE_NAME]; //for the user's choice of subject
    bool match_found = false;
    cout << endl;

    for (int i = 0; i < subject_count; ++i)
        cout << a_subject[i].name << ", " << a_subject[i].rating << endl;
    cout << "Please enter the name of the subject's rating you would like to change: ";
    cin.get(user_subject, '\n');
    cin.ignore(100, '\n');
        
    int rating_index = 0; //to store the index of subject's rating to be modified
    char upper_subject[SIZE_NAME];
    char upper_name[SIZE_NAME];
    
    //Check for matches between user inputted subject and existing subjects
    for (rating_index = 0; (rating_index < subject_count && match_found == false); ++rating_index)
    {
        upper_subject[0] = '\0';
        upper_name[0] = '\0';
        convert_upper(user_subject, upper_subject);
        convert_upper(a_subject[rating_index].name, upper_name);

        if (strcmp(upper_subject, upper_name) == 0) //calls convert_upper function, as toupper only converts one character to uppercase
        {
            match_found = true;
            cout << endl << "Please enter new rating: ";
            cin >> a_subject[rating_index].rating;
            cin.ignore(100, '\n');
            cout << "Rating changed." << endl;
        }
    }
    
    if (match_found == false)
        cout << "Subject not found." << endl;
}

//improvement_ideas function: Displays improvement ideas and adds new improvements to previous subjects.
//Parameters: Array of structs "a_subject", and array index counter by value.
//Return values: None.
void improvement_ideas (subject a_subject[], int subject_count)
{
    char user_subject[SIZE_INFO]; //for the user's choice of subject
    bool match_found = false;
    cout << endl << endl;

    for (int i = 0; i < subject_count; ++i)
        cout << a_subject[i].name << ": " << a_subject[i].improve_info << "\n" << endl;
    cout << "Please enter the name of the subject's improvement info you would like to change: ";
    cin.get(user_subject, '\n');
    cin.ignore(100, '\n');
        
    int improve_index = 0; //to store the index of subject's improvement info to be modified
    char upper_subject[SIZE_NAME];
    char upper_name[SIZE_NAME];
    
    //Check for matches between user inputted subject and existing subjects
    for (improve_index = 0; (improve_index < subject_count && match_found == false); ++improve_index)
    {
        upper_subject[0] = '\0';
        upper_name[0] = '\0';
        convert_upper(user_subject, upper_subject);
        convert_upper(a_subject[improve_index].name, upper_name);
        
        if (strcmp(upper_subject, upper_name) == 0) //calls convert_upper function, as toupper only converts one character to uppercase
        {
            const int remaining_length = (SIZE_NAME-1) - strlen(a_subject[improve_index].improve_info);
            char new_idea[remaining_length]; //create new array for user-inputted idea to be appended to end of existing ideas
            
            match_found = true;
            cout << endl << "Please enter a new improvement idea: ";
            cin.get(new_idea, '\n');
            strcat(a_subject[improve_index].improve_info, new_idea);
            cin.ignore(100, '\n');
            cout << "Info updated." << endl;
        }
    } 
    if (match_found == false)
        cout << "Subject not found." << endl;
}

//convert_upper function: Converts arrays of characters to uppercase to later compare user-inputted subject to existing subjects.
//Parameters: Original array, and uppercase array
//Return values: None.
void convert_upper(char source[], char destination[])
{
    for(int j = 0; j < SIZE_NAME; ++j)
    {
        destination[j] = 'a';
        destination[j+1] = '\0';  
    }
    //setting all values to NOT null terminating char, so that if previous destination array was shorter than current ("Arrays" vs. "Control Structures"), then the next loop will not terminate early.
    for(int i = 0; source[i] != '\0'; ++i) //converts a char array to uppercase for use in other functions.
    {
        destination[i] = toupper(source[i]);
        destination[i+1] = '\0';
    }
}

