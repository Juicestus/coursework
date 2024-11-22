#include <iostream>
#include <sstream>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using std::string;

int mapping (string loc);
string rev_mapping (int num);

class node {
    private:
        int value = 0;
        node *ptr = nullptr;
    public:
        // constructor for node
        node (int arg_val, node*);
        // getters, gets value, gets ptr
        int getvalue ();
        node *getptr (); 

        // setter
        void setptr (node *ptr);
        void setvalue (int value);
};

class LinkedList {
    private:
        node *headptr;
    public:
        // constructor
        LinkedList ();
        // destructor
        ~LinkedList ();
        // push, add at the head
        LinkedList (const LinkedList& object);
        LinkedList& operator=(const LinkedList &object);
        void push (int value);
        // pop, remove at the head
        int pop ();
        // print linked list
        void printLinkedList ();
        void insertNode(int value, int reference_value);
        int find_closest_less_than(int value);
        bool link_list_empty();
        int obtain_value_head ();
}; // end of declarations for LinkedList


void get_op(const string& line, string* operation);
void get_loc(const string& line, string* location);
void print_inst_1();
void print_inst_2();
void print_inst_3();

#endif