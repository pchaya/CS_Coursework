#include "cs163_table.h"
using namespace std;

/* Implement these three functions for this lab */
table::table(int size)
{
      //Allocate the hash table and initialize each
      //element and data member.
    hash_table_size = size; 
    hash_table = new node * [hash_table_size];
    
    for(int i = 0; i < hash_table_size; ++i)
        hash_table[i] = NULL;
}

//Using a hash function, insert a new value into the 
//head of the chain
int table::insert(char * key_value, const journal_entry & to_add)
{
    if (!key_value)
        return -1;
    int index = hash_function(key_value);

    if (index == -1) return index;

    cout << index << endl;
    node * temp = hash_table[index];
    hash_table[index] = new node;
    hash_table[index] -> next = temp;

    hash_table[index] -> entry.copy_entry(to_add);
   
    return 1;
}

//Using a hash function determine which chain to search
//then return 0 if no match is found
int table::retrieve(char * title_to_find, journal_entry & found) const
{

        //Place your code here
    return 1;
}

int table::hash_function(char * title)
{
    if (!title)
        return -1;
    
    unsigned int sum = 0;
    unsigned int length = strlen(title);

    for (unsigned int i = 0; i <= length; ++i)
        sum += title[i] * 7;

    cout << sum << endl;
    return sum % hash_table_size;

}
