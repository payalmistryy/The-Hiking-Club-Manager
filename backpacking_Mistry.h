/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
21 April 2026
Filename: backpacking_Mistry.h

This file contains the BackpackingTrip class, one of the
three derived classes in the hiking club's core hierarchy.
A BackpackingTrip represents a multi-day hike where the
hiker camps overnight at a specific campsite. BackpackingTrip
inherits publicly from ClubHike, collecting its trail name, 
location, distance in miles along with all of Hike's 
overloaded operators. BackpackingTrip adds two data members 
of its own: the name of the campsite (stored as a char *) 
and the number of nights the trip lasts. Because this class 
manages its own dynamic memory for campsite_name, it 
implements the full rule of three: destructor, copy 
constructor, and assignment operator.
*/

#ifndef BACKPACKING_MISTRY_H
#define BACKPACKING_MISTRY_H

#include <string>
#include <iostream>
#include "club_hike_Mistry.h"

using std::string;

//Class: BackpackingTrip (derived)
//This class's purpose is to represent multi-day hikes with
//overnight camping. Inherits trail_name, location, distance_miles
//from Hike and adds its own campsite name (char *) and nights.
//Implements the full rule of three because it manages its own
//dynamic memory for campsite_name
class BackpackingTrip : public ClubHike
{
    public:
        BackpackingTrip();                          //Default constructor - initializes a BackpackingTrip w/default values
        BackpackingTrip(const char * a_trail_name,  //Parameterized constructor - creates a BackpackingTrip w/given trail data,
                                                    //campsite name, number of nights
        const string & a_location,
        float a_distance, const char * a_campsite_name,
        int a_num_nights);
        BackpackingTrip(const BackpackingTrip & source);    //Copy constructor - deep copies campsite_name
        ~BackpackingTrip();                                 //Destructor - releases campsite_name

        //Assignment operator - deep copies rhs into *this
        BackpackingTrip & operator=(const BackpackingTrip & rhs);
        
        //Accessors - read-only access to derived data members
        int get_num_nights() const;     //Returns the number of nights the trip lasts
        string get_campsite() const;    //Returns the campsite name as a safe string copy

        //Stream insertion operator (<<) - writes
        friend std::ostream & operator<<(std::ostream & out,
                                        const BackpackingTrip & b);

        //Stream extraction operator (>>) - reads
        friend std::istream & operator>>(std::istream & in,
                                        BackpackingTrip & b);

    private:
            char * campsite_name;   //dynamically allocated for name of campsite
            int num_nights;         //number of nights the trip lasts
};

#endif
