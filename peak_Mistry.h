/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
21 April 2026
Filename: peak_Mistry.h

This file contains the Peak class, one of the three
derived classes in the hiking club's hierarchy.
A peak essentially represents a summit-focused hike
where the hiker is tracking a list of peaks thay have 
reached. Peak inherits publicly from ClubHike, aquireing
trail name, locatiion, and distance (miles) + the 
overloaded operators. 
*/

#ifndef PEAK_MISTRY_H
#define PEAK_MISTRY_H

#include <string>
#include <iostream>
#include <list>
#include "club_hike_Mistry.h"

using std::string;
using std::list;

//Class: Peak (derived)
//This class's purpose is to represent summit-focused
//hikes. Inherits trail_name, location, distance_miles from
//ClubHike and adds its own summit elevation + list of peaks reached.
class Peak : public ClubHike
{
    public:
        Peak();                              //Default constructor - initializes a Peak w/default values
        Peak(const char * a_trail_name,      //Parameterized constructor - creates a Peak w/given trail data,
                                             //summit elevation, list of peaks summitted
        const string & a_location,
        float a_distance, int a_summit_elevation,
        const list<string> & a_peaks);
        ~Peak();

        //Brings in the base class's operator+= so it isn't
        //hidden by the new Peak specific overload 
        using ClubHike::operator+=;

        //Adds a summit to peaks_summitted
        Peak & operator+=(const string & summit_name);

        //Accessors - read-only access to derived data members
        int get_summit_elevation() const;               //Returns elevation of primary summit (in feet)
        int get_summit_count() const;                   //Returns the number of summits reached
        bool has_summit(const string & summit_name) const;  //Checks if summit_name is in the list

        //Stream insertion operator (<<) - writes
        friend std::ostream & operator<<(std::ostream & out,
                                        const Peak & p);

        //Stream extraction operator (>>) - reads
        friend std::istream & operator>>(std::istream & in,
                                        Peak & p);

    private:
            int summit_elevation_ft;        //elevation of primary summit (in feet)
            list<string> peaks_summitted;   //STL list of named summits reached on this outing
};

#endif