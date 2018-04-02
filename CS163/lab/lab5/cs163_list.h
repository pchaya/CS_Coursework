//list.h
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>


//For practice we will be using a data structure of integers
//This is set up for a doubly linked list
struct node
{
    int data;
    node * previous;
    node * next;
};

//These functions have already been implemented
void build(node * & head);  //supplied
void display(node * head);  //supplied
void destroy(node * &head); //supplied

/* *****************YOUR TURN! ******************************** */
/* These are the functions you will be implementing for this lab */
int insert_after(node * & head);
int insert_before(node * & head);
int display_last_two(node * head);
int remove_last_two(node * & head);

//challenge:
bool same_length(node * head1, node * head2);
