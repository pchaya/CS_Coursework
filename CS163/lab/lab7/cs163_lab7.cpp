#include "cs163_bst.h"
using namespace std;

int main()
{
    table BST;	
    BST.build();
    BST.display();

    /*  PLACE YOUR FUNCTION CALL HERE */

    cout << BST.count() << " items in tree." << endl;;

    cout << "Sum of items in tree: " << BST.sum() << endl;

    cout << "Height of tree: " << BST.height() << endl;
    BST.display();

    return 0;
}
