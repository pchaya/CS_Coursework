//Prathyoosha Chaya, CS 163 DATA STRUCTURES, Prof. Karla Fant
//This implementation file includes the function implementations of the
//table_archive class functions. 

#include "table.h"

table_archive::table_archive()
{
    file_in.open(filename);

    hash_table = new entry_node * [HASH_TABLE_SIZE];

    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        hash_table[i] = NULL;
    }    

    entry_count = 0;
}


table_archive::~table_archive()
{
    if (hash_table)
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            entry_node * temp = NULL;

            while (hash_table[i])
            {
                temp = hash_table[i] -> next_entry;
                delete hash_table[i];
                hash_table[i] = temp;
            }

        }
        
        delete [] hash_table;
        hash_table = NULL;
    }
    
    file_in.close();
}

int table_archive::hash_function(char * key)
{
    int sum = 0; 
    char upper_key [strlen(key) +1];

    convert_to_upper(key, upper_key);

    for (int i = 0; i < strlen(upper_key); ++i)
        sum += (upper_key[i]*50); //hash function multiplying by a constant 50 to increase range of possible sum before finding index through modulus op.

    return sum % HASH_TABLE_SIZE;
}

int table_archive::add_info(entry & user_entry)
{
    if (!hash_table)
       return 0;
     
    //create new node and add data to it
    entry_node * temp = new entry_node;
    temp -> entry_data.set_entry_data(user_entry.keyword, user_entry.info_type, user_entry.background, user_entry.evolution, user_entry.evo_candy, user_entry.evo_info, user_entry.list_of_pokemon, user_entry.num_of_unique_pokemon, user_entry.term_info);


    int hash_index = hash_function(temp -> entry_data.keyword);

    cout  << endl << hash_index << endl;

    //list management
    if (!hash_table[hash_index])
    {
        hash_table[hash_index] = temp;
    } 
    
    else if (hash_table[hash_index])
    {
        entry_node * temp2 = hash_table[hash_index];
        hash_table[hash_index] = temp;
        hash_table[hash_index] -> next_entry = temp2; 
    }
   
     display_a_node(hash_table[hash_index]);

    return 1; 
}

int table_archive::remove_entry(char remove_keyword [])
{
    if(!hash_table)
       return 0; 

    int hash_index = hash_function(remove_keyword);
    if(hash_table[hash_index])
    {
        char upper_to_remove [MAX_SIZE_NAMES];
        char upper_to_cmp [MAX_SIZE_NAMES];
        convert_to_upper(remove_keyword, upper_to_remove); 
        convert_to_upper(hash_table[hash_index] -> entry_data.keyword, upper_to_cmp);
        
        if(strcmp(upper_to_cmp, upper_to_remove) == 0)
        {
            cout << "*** TO REMOVE: ***" << endl; 
            display_a_node(hash_table[hash_index]);
            entry_node * temp = hash_table[hash_index] -> next_entry;
            delete hash_table[hash_index];
            hash_table[hash_index] = temp;
            return 1;
        }

        entry_node * current = hash_table[hash_index];

        while (current -> next_entry)
        {
            convert_to_upper(current -> next_entry -> entry_data.keyword, upper_to_cmp);

            if (strcmp(upper_to_cmp, upper_to_remove) == 0)
            {
                cout << "**TO REMOVE: ***" <<endl;
                display_a_node(current);
                entry_node * temp2 = current -> next_entry -> next_entry;
                delete current -> next_entry;
                current -> next_entry = temp2;
                
                return 1;
            }
            else
                current = current -> next_entry;
        }
    }
    return 0;
}



int table_archive::retrieve(char to_retrieve [])
{
    if(!hash_table)
       return 0;

    int hash_index = hash_function(to_retrieve);
    if(hash_table[hash_index])
    {
        char upper_to_retrieve [MAX_SIZE_NAMES];
        char upper_to_cmp [MAX_SIZE_NAMES];
        convert_to_upper(to_retrieve, upper_to_retrieve); 
        convert_to_upper(hash_table[hash_index] -> entry_data.keyword, upper_to_cmp);
/*
        if(strcmp(upper_to_cmp, upper_to_retrieve) == 0)
        {
            display_a_node(hash_table[hash_index]);
            return 1; 
        }
*/
        entry_node * current = hash_table[hash_index];

        while (current)
        {
            convert_to_upper(current -> entry_data.keyword, upper_to_cmp);

            if (strcmp(upper_to_cmp, upper_to_retrieve) == 0)
            {
                display_a_node(current);
                return 1;
            }
            else
                current = current -> next_entry;
        }

    }

    return 0;
}

bool table_archive::display_all()
{
    int entry_num = 0;
    bool result = false;
    if (!hash_table)
        return result;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {   
        if (hash_table[i])
        {
            entry_node * current = hash_table[i]; 
            while (current)
            {
                cout << endl << ++entry_num << ":" << endl; //display # before entry
                display_a_node(current);
                current = current -> next_entry;
            } 
        }
    }
    
    result = true;
    return result;
}

bool table_archive::display_a_node(entry_node * a_node)
{
    if(!a_node)
        return false;

    cout << "Term: " << a_node -> entry_data.keyword << endl;

    //Display based on type of info:
    if(a_node -> entry_data.info_type == 0) 
    {
        cout << "This is a Pokemon." << endl
            << "Background: " << a_node -> entry_data.background << endl
            << "Evolves to: " << a_node -> entry_data.evolution << endl
            << "Candy required for evolution: " << a_node -> entry_data.evo_candy << endl
            << "Additional info: " << a_node -> entry_data.evo_info << endl;
    }

    else if (a_node -> entry_data.info_type == 1)
    {
        cout << "This is regional info." << endl
            << "List of Pokemon in area: " << a_node -> entry_data.list_of_pokemon << endl
            << "Number of unique Pokemon types: " << a_node -> entry_data.num_of_unique_pokemon << endl;
    }

    else if (a_node -> entry_data.info_type == 2)
    {
        cout << "This is a general Pokemon term: " << endl
            << "Info. on term: " << a_node -> entry_data.term_info << endl;
    }

    else cout << "Info not of valid type" << endl;

    return true;

}


bool table_archive::load()
{

    if (!file_in)
        return false;
    
    //temporary arrays to read into
    char temp_keyword [MAX_SIZE_NAMES];
    int temp_info_type = 0; 
    char temp_background [MAX_SIZE_INFO];
    char temp_evolution [MAX_SIZE_NAMES];
    int temp_evo_candy = 0;
    char temp_evo_info [MAX_SIZE_INFO];
    char temp_list_of_pokemon [MAX_SIZE_INFO];
    int temp_num_of_unique_pokemon = 0;
    char temp_term_info [MAX_SIZE_INFO];

    //initial check to set eof
    file_in.get(temp_keyword, MAX_SIZE_NAMES - 1, ';');
    file_in.ignore(100, ';');
    
    cout << "1..";
    if (!file_in.eof())
    {
        //if reading operation is successful
        //read the record
        file_in >> temp_info_type;
        file_in.ignore(100, ';');

    
        if(temp_info_type == 0)
        {
            file_in.get(temp_background, MAX_SIZE_INFO - 1, ';');
            file_in.ignore(100, ';');

            file_in.get(temp_evolution, MAX_SIZE_NAMES - 1, ';');
            file_in.ignore(100, ';');


            file_in >> temp_evo_candy;
            file_in.ignore(100, ';');

            file_in.get(temp_evo_info, MAX_SIZE_INFO - 1, '\n');
            file_in.ignore(100, '\n');
        } 
        else if (temp_info_type == 1)
        { 
            file_in.get(temp_list_of_pokemon, MAX_SIZE_INFO - 1, ';');
            file_in.ignore(100, ';');

            file_in >> temp_num_of_unique_pokemon;
            file_in.ignore(100, '\n');
        }
        else if (temp_info_type == 2)
        {
            file_in.get(temp_term_info, MAX_SIZE_INFO - 1, '\n');
            file_in.ignore(100, '\n');
        }

    }
    else return true;   //end of items, leave recursion

    //create new node and add data to it
    entry_node * temp = new entry_node;
    temp -> entry_data.set_entry_data(temp_keyword, temp_info_type, temp_background, temp_evolution, temp_evo_candy, temp_evo_info, temp_list_of_pokemon, temp_num_of_unique_pokemon, temp_term_info);

    int hash_index = hash_function(temp -> entry_data.keyword);

    cout  << endl<< hash_index << endl;

    //list management
    if (!hash_table[hash_index])
    {
        hash_table[hash_index] = temp;
    } 
    
    else if (hash_table[hash_index])
    {
        entry_node * temp2 = hash_table[hash_index];
        hash_table[hash_index] = temp;
        hash_table[hash_index] -> next_entry = temp2; 
    }
    
    ++entry_count;

    cout << entry_count << endl;
    display_a_node(hash_table[hash_index]);

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
