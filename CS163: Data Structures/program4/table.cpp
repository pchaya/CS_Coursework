//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Prof. Karla Fant
//03/19/2017
//This implementation file includes the function implementations of the
//table_archive class functions. 

#include "table.h"

table_archive::table_archive()
{
    file_in.open(filename);
    
    root = NULL;

}


table_archive::~table_archive()
{
    if (root)
    {
        delete root;
        root = NULL;    
    }
    
    file_in.close();
}

int table_archive::insert_entry(entry & user_entry)
{
    //tree management
    //create new node and add data to it
    entry_node * temp = new entry_node;
    temp -> entry_data.set_entry_data(user_entry.term_name, user_entry.definition);

    insert_entry_worker(temp, root); 

    return 1; 
}

void table_archive::insert_entry_worker(entry_node * to_add, entry_node * & root)
{
    if (!root)
    {
        root = new entry_node;
        root -> entry_data.set_entry_data(to_add -> entry_data.term_name, to_add -> entry_data.definition);
        root -> left_entry = NULL;
        root -> right_entry = NULL; 
        //display_a_node(root); 
        return;       
    }

    else if (strcmp(to_add -> entry_data.term_name, root -> entry_data.term_name) < 0) 
        return insert_entry_worker(to_add, root -> left_entry); 
    else if (strcmp(to_add -> entry_data.term_name, root -> entry_data.term_name) >= 0)
        return insert_entry_worker(to_add, root -> right_entry); 
}

int table_archive::remove_entry(char remove_keyword [])
{
    //empty tree
    if (!root)
        return 0;

    char upper_remove_keyword [strlen(remove_keyword) +1];
    convert_to_upper(remove_keyword, upper_remove_keyword);

    remove_entry_worker(root, upper_remove_keyword);
    return 1;
}

void table_archive::remove_entry_worker(entry_node * & root, char remove_keyword [])
{
    //empty tree or item to remove is not found
    if (!root)
        return;
cout << "entered" << endl;
cout << remove_keyword << endl;
    char upper_to_compare [strlen(root -> entry_data.term_name) +1];
    convert_to_upper(root -> entry_data.term_name, upper_to_compare);
cout << upper_to_compare << endl;
    if (strcmp(upper_to_compare, remove_keyword) == 0)
    {
        cout << "found match" << endl;
        //item found and located at 
        //  leaf
        if (!(root -> left_entry) && !(root -> right_entry))
        {
            delete root;
            root = NULL;
        }

        //  internal node with only 1 child (left) or right)
        if (root -> left_entry && !(root -> right_entry))
        {
            entry_node * temp = root -> left_entry;
            delete root;
            root = temp;
        }
        if (root -> right_entry && !(root -> left_entry))
        {
            entry_node * temp = root -> right_entry;
            delete root;
            root = temp;
        }

        //  internal node with 2 children - but right child has no left children
        if (root -> left_entry && root -> right_entry)
        {
            entry_node * temp = root -> right_entry;

            if (!(temp -> left_entry))
            {
                delete root -> entry_data.term_name;
                delete root -> entry_data.definition;
                root -> entry_data.set_entry_data(temp -> entry_data.term_name, temp -> entry_data.definition);
                root -> right_entry = temp -> right_entry;
                delete temp;
            }
        //  internal node with 2 children
            else 
            {
                entry_node * prev = temp;
                while (temp -> left_entry)
                {
                    prev = temp;
                    temp = temp -> left_entry;
                }
                if (temp -> right_entry)
                    prev -> left_entry = temp -> right_entry;
                delete root -> entry_data.term_name;
                delete root -> entry_data.definition;
                root -> entry_data.set_entry_data(temp -> entry_data.term_name, temp -> entry_data.definition);
                delete temp;
            } 
        }
    } 
   
    else if (strcmp(remove_keyword, root -> entry_data.term_name) < 0) 
    {
        cout << "going left" << endl; 
        return remove_entry_worker(root -> left_entry, remove_keyword); 
    }
    else if (strcmp(remove_keyword, root -> entry_data.term_name) > 0)
    {
        cout << "going right" << endl;
        return remove_entry_worker(root -> right_entry, remove_keyword); 
    }
}

int table_archive::retrieve(char to_retrieve [], entry & retrieved_entry) 
{
    if(!root)
    {
        strcpy(retrieved_entry.term_name, "Not found.");
        strcpy(retrieved_entry.definition, "Not found.");
        return 0;    
    }

    cout << "test" << endl;
    retrieve_worker(root, to_retrieve, retrieved_entry); 
    return 1;
}

void table_archive::retrieve_worker(entry_node * root, char to_retrieve [], entry & retrieved_entry)
{
    if (!root)
        return;
    char upper_to_retrieve [MAX_SIZE_NAMES];
    char upper_to_compare [MAX_SIZE_NAMES];
    convert_to_upper(to_retrieve, upper_to_retrieve);
    convert_to_upper(root -> entry_data.term_name, upper_to_compare);
    cout << "t2" << endl;
    if (strcmp(upper_to_retrieve, upper_to_compare) == 0)
    {
        retrieved_entry.set_entry_data(root -> entry_data.term_name, root -> entry_data.definition);
        cout << retrieved_entry.term_name;
        cout << retrieved_entry.definition;
        return;       
    }
    else if (strcmp(upper_to_retrieve, upper_to_compare) < 0) 
        return retrieve_worker(root -> left_entry, to_retrieve, retrieved_entry); 
    else if (strcmp(upper_to_retrieve, upper_to_compare) > 0)
        return retrieve_worker(root -> right_entry, to_retrieve, retrieved_entry); 

}


bool table_archive::display_all()
{
    bool result = false;
    if (!root)
        return result;

    display_all_worker(root);

    result = true;
    return result;
}

void table_archive::display_all_worker(entry_node * root)
{
    if (!root)
        return;
    
    display_all_worker(root -> left_entry);

    cout << "Term: " << root -> entry_data.term_name << endl
        << "Definition: " << root -> entry_data.definition << endl;
    cout << endl;
        display_all_worker(root -> right_entry);
}

bool table_archive::display_range(char first_char, char last_char)
{
    bool result = false;
    if (!root)
        return result;
 
    char upper_first_char = toupper(first_char);
    char upper_last_char = toupper(last_char);

    display_range_worker(root, upper_first_char, upper_last_char);

    cout << "g" << endl;
    result = true;
    return result;
}

void table_archive::display_range_worker(entry_node * root, char first_char, char last_char)
{
    if (!root)
        return;
      display_range_worker(root -> left_entry, first_char, last_char);

    if (*(root -> entry_data.term_name) >= first_char && (*(root -> entry_data.term_name) <= last_char))
    {
        cout << "Term: " << root -> entry_data.term_name << endl
            << "Definition: " << root -> entry_data.definition << endl;
        cout << endl;
    }
    
    display_range_worker(root -> right_entry, first_char, last_char);
}

bool table_archive::display_a_node(entry_node * a_node)
{
    if(!a_node)
        return false;

    cout << "Term: " << a_node -> entry_data.term_name << endl
        << "Definition: " << a_node -> entry_data.definition << endl;

    return true;

}

int table_archive::get_height()
{
    if (!root)
        return 0;
    
    return get_height_worker(root);    
}

int table_archive::get_height_worker(entry_node * root)
{
    if (!root)
        return 0;

    return max(get_height_worker(root -> left_entry), get_height_worker(root -> right_entry)) + 1;

}

bool table_archive::is_efficient()
{
    int height_left = get_height_worker(root -> left_entry);
    int height_right = get_height_worker(root -> right_entry);

    if ((height_left - height_right) <= 1 && (height_left - height_right) >= -1)
        return true;

    return false;
}

bool table_archive::load()
{
    if (!file_in)
        return false;
  
    //temporary arrays to read into
    char temp_term_name [MAX_SIZE_NAMES];
    char temp_definition [MAX_SIZE_INFO];

    //initial check to set eof
    file_in.get(temp_term_name, MAX_SIZE_NAMES -1, ':');
    file_in.ignore(100, ':');
   
    //cout << temp_term_name << endl; 
    //cout << "1..";
    if (!file_in.eof())
    {
        //if reading operation is successful
        //read the record
        file_in.get(temp_definition, MAX_SIZE_INFO - 1, '\n');
        file_in.ignore(100, '\n');
    }

    else return true;   //end of items, leave recursion

    entry temp_entry;
    
    temp_entry.set_entry_data(temp_term_name, temp_definition);
    strcpy(temp_entry.term_name, temp_term_name);
    strcpy(temp_entry.definition, temp_definition);
   
    entry_node * temp = new entry_node;
    temp -> entry_data.set_entry_data(temp_entry.term_name, temp_entry.definition);

    //tree management
    insert_entry_worker(temp, root); 

    return load();


}

//convert_upper function: Converts arrays of characters to uppercase to later compare user-inputted topic to existing topics.
//Parameters: Original array, uppercase array.
//Return Values: None.
void table_archive::convert_to_upper(char source[], char destination[])
{
    int i;
    memset (destination, 0, strlen(destination));
    
    for (i = 0; source[i] != '\0'; ++i) //converts char array to uppercase for conparison use in other functions
        destination[i] = toupper(source[i]);
    destination[i+1] = '\0';

}
