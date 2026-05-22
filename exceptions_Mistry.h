/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
21 April 2026
Filename: exceptions_Mistry.h

This file defines the set of exception types thrown 
by the ClubHike class hierarchy. Since operators are not able
to return a success or failure flag through the return 
value, an exception type is thrown when the operator
faces an invalid user input like incompatible hike
types being combined. Each exception is defined as a 
class. 
*/

#ifndef EXCEPTIONS_MISTRY_H
#define EXCEPTIONS_MISTRY_H


//Class InvalidHikeData (exception)
//Handles invalid user input like negative distance,
//empty trail name, any unexpected input.
class InvalidHikeData
{

};


//Class IncompatibleHikes (exception)
//Two hike objects that aren't able to be combined.
class IncompatibleHikes
{

};


//Class EmptyList (exception)
//Retrieval and remove operations were attempted
//on a DLL that includes no nodes.
class EmptyList
{

};


//Class ItemNotFound (exception)
//The item does not exist in the list.
class ItemNotFound
{

};

#endif