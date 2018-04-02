#include "cs163_entry.h"

//The stack is based on the journal class from Lab #2
//which has been completed for this lab.
//
//The data structure is a LLL of arrays of journal entries

//Remember, whenever you have a pointer you can
//point to one item or the first of many items
struct node
{
       journal_entry * entries; //a dynamically allocated array of journal entries
       node * next;
};

//Now let's create a stack. Stacks should be able to keep a collection of
//data and push (add at the beginning), pop (remove at the beginning), 
//display all, and peek (retrieve the information at the beginning).

//Create arrays of const size MAX
const int MAX = 5;

class stack
{
      public:
             //These functions have ALREADY been written for you
             stack(void);     
             ~stack(void);     
             int display_all(void) const; 
            
 
             //Peek: You need to get back through the argument list the
             //journal on the top of the stack but don't change the stack
             int peek(journal_entry & ) const; //MODIFY THIS PROTOTYPE BEFORE YOU BEGIN!

             int push(const journal_entry &);  //MODIFY THIS PROTOTYPE BEFORE YOU BEGIN!
                                         //to push the argument onto the stack
             int pop (void); 

  
      private:
              node * head;
              int top_index;   //The index for the next place to push
			       //It is set to zero by the constructor
			       //When it is MAX, the array is full
              
};
             
