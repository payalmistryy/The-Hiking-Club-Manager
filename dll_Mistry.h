/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
26 April 2026
Filename: dll_Mistry.h

This file declares a templated doubly linked list (DLL)
and the templated Node it holds. The DLL stores a chain
of nodes containing objects of type T, maintains both
head and tail pointers, and implements all repetitive
operations (insert, remove, display, retrieve, remove_all)
recursively via private helper methods. Because the DLL
manages dynamic memory through raw pointers, it
implements the full rule of three. The implementation
file dll_Mistry.tpp is included at the bottom of this
header because class template implementations must be
visible at each instantiation site.
*/


#ifndef DLL_MISTRY_H
#define DLL_MISTRY_H

#include <iostream>
#include "exceptions_Mistry.h"


//Node class template
//Each Node holds one piece of data of type T and pointers
//to the next and previous nodes in the list.
template <typename T>
class Node
{
    public:
        Node();                                     //Default constructor
        Node(const T & a_data);                     //Parameterized constructor

        T & get_data();                             //Accessor for data (modifiable)
        const T & get_data() const;                 //Accessor for data (read-only)
        Node<T> * & get_next();                     //Accessor for next pointer (modifiable)
        Node<T> * & get_prev();                     //Accessor for prev pointer (modifiable)

    private:
        T data;                 //the payload stored in this node
        Node<T> * next;         //pointer to the next node, or nullptr at tail
        Node<T> * prev;         //pointer to the previous node, or nullptr at head
};


//DLL class template
//Templated doubly linked list with head and tail pointers
//and recursive implementations for all repetitive ops.
//Manages raw pointers to its nodes and implements the rule
//of three for safe copying and destruction.
template <typename T>
class DLL
{
    public:
        DLL();                                      //Default constructor - creates an empty list
        DLL(const DLL<T> & source);                 //Copy constructor - deep copies entire chain
        ~DLL();                                     //Destructor - releases every node

        DLL<T> & operator=(const DLL<T> & rhs);     //Assignment - deep copies, releases existing chain

        //Public wrappers for the five core operations.
        //Each delegates to a private recursive helper.
        void insert(const T & item);                //Adds item to the back of the list
        void remove(const T & item);                //Removes the first node whose data == item
        void display() const;                       //Prints every node's data, one per line
        T retrieve(const T & item) const;           //Returns a copy of the matching item's data
        void remove_all();                          //Removes every node in the list

        bool is_empty() const;                      //True if list contains no nodes

    private:
        Node<T> * head;         //pointer to the first node in the chain
        Node<T> * tail;         //pointer to the last node in the chain

        //Private recursive helpers. Each operates on a node
        //pointer parameter and walks the chain via next.
        void copy_chain(Node<T> * & dest, Node<T> * source, Node<T> * & dest_tail);
        void insert_at_back(Node<T> * & current, Node<T> * prev_node, const T & item);
        bool remove_helper(Node<T> * & current, const T & item);
        void display_helper(Node<T> * current) const;
        const T & retrieve_helper(Node<T> * current, const T & item) const;
        void remove_all_helper(Node<T> * & current);
};


#include "dll_Mistry.tpp"

#endif