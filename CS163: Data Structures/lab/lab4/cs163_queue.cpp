#include "cs163_queue.h"


//Implement these functions using a Circular Linked List
//Add at the rear
int queue::enqueue(const journal_entry & to_add)
{
    int return_val = 0;

    if (!rear)
    {
        rear = new q_node;
        rear -> entry.copy_entry(to_add);

        rear -> next = rear;
        
        ++return_val;
    }

    else 
    {
        q_node * temp = rear -> next;
        rear -> next = new q_node;
        rear -> next -> entry.copy_entry(to_add);
        
        rear = rear -> next;
        rear -> next = temp;

        return_val = 2;
    }
    
    return return_val;
}


//Remove the node at the front
int queue::dequeue ()
{
    if (!rear)
        return 0;
    else if (rear -> next == rear)
    {
        delete rear;
        rear = NULL;
    }

    else 
    {
        q_node * temp = rear -> next -> next;
        delete rear -> next;
        rear -> next = temp;
    }
    
    return 1;
}

