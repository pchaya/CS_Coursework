#include "cs163_queue.h"

using namespace std;

int main()
{
    queue my_journal;
    journal_entry to_add, an_entry;
    char title[100];
    char notes[300];
    
    //Let's add some items ot the journal first
    do
    {
       cout <<"Please enter a title: ";
       cin.get(title, 100); cin.ignore(100,'\n');
       cout <<"Please enter the notes: ";
       cin.get(notes, 300); cin.ignore(100,'\n');
       to_add.create_entry(title, notes);
       
       //now enqueue it onto the queue
        if (!my_journal.enqueue(to_add))
            cout << "Failed to add the journal item." << endl;
       
    } while (again());
    
    //Let's display what we have  (this function was provided for you)
    cout <<"\n\nThis is the contents of the stack: ";
    my_journal.display_all();

    
//Now dequeue
    do
    {
          
       if( my_journal.dequeue()) 
       {
          
          cout <<"\n\nAfter removing this is what we have: ";
          my_journal.display_all(); 
       }
       else  cout <<"\nNothing could be removed, the stack is empty! " <<endl;
    } while (again());
    
    return 0;
}
