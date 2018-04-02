#include "cs163_bst.h"
using namespace std;


// ***These are sample wrapper functions
table::~table()
{
     remove_all(root); //call the recursive removal_all private function
}

// This is a wrapper function that will call the recursive count function
int table::count()
{
    //Notice how the returned value from the recursive function is used
    return count(root);
}

// Now it is your turn to write the count function recursively
int table::count (node * root)
{
    if (!root)
        return 0;

    return 1 + count (root -> left) + count(root -> right);
}


// Start with the wrapper function that calls the recursive function
int table::sum()
{
    //Call the recursive function here:

    return sum(root);
}

// Now it is your turn to write the sum function recursively
int table::sum (node * root)
{
    if (!root)
        return 0;
    int count = root -> data;
    return count + sum(root -> left) + sum (root -> right);
}


int table::height()   //simply call the private version of the functions
{
    //Call the recursive function here:

    return height(root);
}

//Now write this function recursively
int table::height (node * root)       
{
    if (!root)
        return 0;
    return max(height(root -> right), height(root -> left)) +1;
}


int table::remove_all()
{
    //Call the recursive function here:
    return 0;
}

// Now it is your turn to write the remove_all function recursively
int table::remove_all(node * & root)
{

    return 0;
}  


int table::copy(const table & to_copy)
{
    //Call the recursive function here:

    return 0;
}

// Now it is your turn to write the copy function recursively
int table::copy(node * & dest_root, node * source_root) 
{


    return 0;
}  

