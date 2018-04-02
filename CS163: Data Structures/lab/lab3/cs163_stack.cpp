#include "cs163_stack.h"


//These are the functions you will be implementing
//for this lab, using a linear linked list of arrays
//as the data structure

//Add a new item to the top of stack
int stack::push(const journal_entry & to_add)
{
    if (!head)
    {
        head = new node;
        head -> next = NULL;
        head -> entries = new journal_entry[MAX];
        head -> entries[top_index].copy_entry(to_add);
        ++top_index;
        return 1;
    }

    else if ((top_index+1) == MAX)
    {
        top_index = 0;

        node * current = head;
        head = new node;
        head -> next = current;
        head -> entries = new journal_entry[MAX];
        head -> entries[top_index].copy_entry(to_add);
        ++top_index;      
    }

    else
    {
        head -> entries[top_index].copy_entry(to_add);
        ++top_index;
    }

    return 1;
}

//Remove the top of stack
int stack::pop (void)
{
    if (!head)
        return 0;

    else if (top_index == 1)
    {
        top_index = MAX;
        delete [] head -> entries;
        delete head;
        head = NULL;
    }

    else
        --top_index; 

    return 1;
}

//Supply the journal at the top of stack back to the client
//Return 0 if there are no items
//top_index is one beyond where the top of stack is...
//with no items, top_index is zero
int stack::peek(journal_entry & found_at_top) const
{
            //Implement the function here
    return 1;
}

