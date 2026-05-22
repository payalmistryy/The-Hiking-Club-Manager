/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
21 April 2026
Filename: club_hike_Mistry.h

This file declares the ClubHike class which represents
the base class in the hiking club's core hierarchy.
A hike represents a single trail outing and holds 
the data common to every type of hike the club tracks
(trail name, location, distance (miles). The three
derived classes include DayHike, BackpackingTrip, 
and Peak. The rule of three applies here and 
implemented in this file. 
*/

#ifndef CLUB_HIKE_MISTRY_H
#define CLUB_HIKE_MISTRY_H


#include <string>
#include <iostream>
#include "exceptions_Mistry.h"

using std::string;


//ClubHike class (base class)
//This class holds data common to every
//hike (trail name, location, and distance) while
//declaring overloaded operators used by the DLL template. 
class ClubHike
{
    public: 
        //Constructors, destructor, rule of 3
        ClubHike();                                 //Default constructor - initialize a Hike 
        ClubHike(const char * a_trail_name,         //Parameterized constructor - creating a Hike with params(trail name, location, distance)
            const string & a_location,
            float a_distance);
        ClubHike(const ClubHike & source);              //Copy constructor - creates a new Hike as a deep copy of source
        ~ClubHike();                                //Destructor - frees dynamic memory. 
        
        //Assignment operator
        ClubHike & operator=(const ClubHike & rhs);
        //Relational operators
        bool operator<(const ClubHike & rhs) const;
        bool operator<=(const ClubHike & rhs) const;
        bool operator>(const ClubHike & rhs) const;
        bool operator>=(const ClubHike & rhs) const;
        //Equality operators
        bool operator==(const ClubHike & rhs) const;
        bool operator!=(const ClubHike & rhs) const;

        ClubHike & operator+=(const ClubHike & rhs);        //Adds the distance of rhs into this Hike
        ClubHike operator+(const ClubHike & rhs) const;     //Produces a new Hike whose distance is the sum of *this and rhs
        //Stream insertion operator (<<)
        friend std::ostream & operator<<(std::ostream & out, const ClubHike & h);
        //Stream extraction operator (>>)
        friend std::istream & operator>>(std::istream & in, ClubHike & h);

    protected:
        string location;        //where the hike takes place
        float distance_miles;   //total length of hike in miles

    private:
        char * trail_name;      //dynamically allocated for name of trail

};






#endif