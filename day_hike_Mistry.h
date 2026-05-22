/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
21 April 2026
Filename: day_hike_Mistry.h

This file contains the DayHike class, which is one
of the threee derived classes in the hiking club's core
hierarchy. A DayHike represents a trail outing that starts 
and ends on the same day, with an elevation gain component
and difficulty rating. DayHike inherits publicly from Hike,
collecting its trial name, location, distance in miles along
with all of Hike's overload operators. The difficulty is rated 
by "mild", "intermediate", "expert".
*/

#ifndef DAY_HIKE_MISTRY_H
#define DAY_HIKE_MISTRY_H

#include <string>
#include <iostream>
#include "club_hike_Mistry.h"

using std::string;

//Class: DayHike (derived)
//This class's purpose is to represent single-day hikes. 
//Inherits the trail_name, location, distance_miles from
//Hike and adds its own elevation gain + difficulty rating.
class DayHike : public ClubHike
{
    public:
        DayHike();                           //Default constructor - initializes a Dayhike w/default values
        DayHike(const char * a_trail_name,   //Parameterized constructor - creates a DayHike w/given trail data, 
                                            //elevation gain, difficulty        
        const string & a_location,
        float a_distance, int a_elevation, 
        const string & a_difficulty);       
        ~DayHike();                         
        
        //Accessors - read-only access to derived data members
        int get_elevation_gain() const;     //Returns total elevation gain in feet
        string get_difficulty() const;      //Returns the difficulty rating

        //Stream insertion operator (<<) - writes
        friend std::ostream & operator<<(std::ostream & out,
                                        const DayHike & h);

        //Stream extraction operator (>>) - reads
        friend std::istream & operator>>(std::istream & in,
                                        DayHike & h);
        
    private:
            int elevation_gain_ft;  //total elevation gained on a hike (in feet)
            string difficulty;      //difficulty ratining - mild, intermediate, expert
};




#endif