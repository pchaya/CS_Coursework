#include "cs163_list.h"

/* These are the functions you will be implementing */
/* USE RECURSION! */
int insert_after(node * & head)
{
    if (!head)
        return 0;
    if (head -> data == 2)
    {
        node * temp = head -> next;
        head -> next = new node;
        head -> next -> data = 1; 
        head -> next -> next = temp;
        
        return (1 + insert_after(head -> next -> next));
    }

    return (0 + insert_after(head -> next));

}

int insert_before(node * & head)
{
    if (!head)
        return 0;
    
    int count = 0;
    
    //traverse to end
    return (++count + insert_before(head -> next)); 
    
    if (head -> data == 2)
    {
        ++count;
        /*node * temp = head -> previous;
        head -> previous = new node;
        head -> previous -> data = 1;
        temp -> next = head -> previous;
        temp -> next -> next = head;
    */
        
        return (count + insert_before(head -> previous)); 
    }
}

int display_last_two(node * head)
{
    return 0;
}
int remove_last_two(node * & head)
{
    return 0;
}


//challenge:
bool same_length(node * head1, node * head2)
{
    return 0;
}

