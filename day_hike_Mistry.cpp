/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
25 April 2026
Filename: day_hike_Mistry.cpp

This file implements the DayHike class. It defines the
default constructor, parameterized constructor, destructor,
two accessors (get_elevation_gain and get_difficulty), and
the friend stream operators (<< and >>). DayHike does not
manage its own dynamic memory, the base class ClubHike
handles trail_name. so no rule-of-three functions are
implemented in this file. The copy constructor and 
assignment operator chain to the base correctly.
The parameterized constructor uses the initializer list
to forward base class data to ClubHike's constructor.
Stream extraction throws InvalidHikeData on invalid
input.
*/

#include "day_hike_Mistry.h"

using namespace std;

//Default constructor
//Initializes a DayHike with zero elevation gain and an
//empty difficulty string. The base class default
//constructor runs implicitly to initialize ClubHike's
//inherited members (empty trail_name, empty location,
//distance 0.0).
//Input: none
//Output: a default initialized DayHike object
DayHike::DayHike() : elevation_gain_ft(0)
{
}


//Parameterized constructor
//Creates a DayHike with caller-provided trail data, plus
//elevation gain and difficulty rating. Forwards the base
//class data to ClubHike's parameterized constructor via
//the initializer list, then initializes the DayHike-
//specific members.
//Input:  a_trail_name - C-string trail name
//        a_location   - location of the hike
//        a_distance   - length in miles
//        a_elevation  - total elevation gain in feet
//        a_difficulty - difficulty rating string
//Output: a fully initialized DayHike object
DayHike::DayHike(const char * a_trail_name,
                 const string & a_location,
                 float a_distance,
                 int a_elevation,
                 const string & a_difficulty)
    : ClubHike(a_trail_name, a_location, a_distance),
      elevation_gain_ft(a_elevation),
      difficulty(a_difficulty)
{
}


//Destructor
//No cleanup required. The base class
//destructor runs automatically after this function
//returns, releasing the inherited trail_name memory.
//Input: none
//Output: none
DayHike::~DayHike()
{
}


//Accessor for elevation_gain_ft
//Returns the total elevation gain of this hike in feet.
//Input:  none
//Output: the elevation gain as an int
int DayHike::get_elevation_gain() const
{
    return elevation_gain_ft;
}


//Accessor for difficulty
//Returns the difficulty rating as a string copy. Returns
//by value (rather than by const reference) so the caller's
//string remains valid even if the DayHike is destroyed.
//Input: none
//Output: a copy of the difficulty rating string
string DayHike::get_difficulty() const
{
    return difficulty;
}


//Stream insertion operator (<<)
//Writes a one line summary of h to out, including base
//class data (trail name, location, distance) and DayHike
//specific data (elevation gain, difficulty). Does not
//append a newline. Implemented as a friend so it can
//access h's private and inherited members directly.
//Input:  out - the output stream
//        h   - the DayHike being displayed
//Output: reference to out, for chained insertion
ostream & operator<<(ostream & out, const DayHike & h)
{
    out << static_cast<const ClubHike &>(h)
        << " [elevation gain: " << h.elevation_gain_ft
        << " ft, difficulty: " << h.difficulty << "]";
    return out;
}


//Stream extraction operator (>>)
//Reads base class data via ClubHike's >>, then reads
//elevation gain and difficulty into local buffers and
//validates them. Throws InvalidHikeData if elevation is
//negative or difficulty is empty. Only commits to h after
//all validation passes, so a thrown exception leaves h
//unmodified by this function.
//Input:  in - the input stream
//        h  - the DayHike being populated
//Output: reference to in, for chained extraction
istream & operator>>(istream & in, DayHike & h)
{
    in >> static_cast<ClubHike &>(h);

    int buffer_elevation;
    string buffer_difficulty;

    in >> buffer_elevation;
    in.ignore();
    getline(in, buffer_difficulty);

    if (!in || buffer_elevation < 0 || buffer_difficulty.empty())
        throw InvalidHikeData{};

    h.elevation_gain_ft = buffer_elevation;
    h.difficulty = buffer_difficulty;

    return in;
}
