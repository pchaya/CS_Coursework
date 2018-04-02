#include "cs163_list.h"
using namespace std;

int main()
{
    node * head = NULL;
    build(head);
    display(head);

    cout << "Number of 2s in list: " << insert_after(head) << endl;
    display(head);
    cout << endl << "Number of nodes in list: " << insert_before(head) << endl;

    display(head);
    
    return 0;
}
