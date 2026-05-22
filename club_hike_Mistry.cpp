/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
24 April 2026
Filename: club_hike_Mistry.cpp

This file implements the ClubHike base class. It defines
the constructors, destructor, copy constructor, assignment
operator, and overloaded operators declared in
club_hike_Mistry.h. The class manages a dynamically
allocated trail_name (char *), so the implementations of
the destructor, copy constructor, and assignment operator
all perform deep copies and matched delete[] calls to
prevent memory leaks. Comparison operators compare hikes
by distance_miles; equality operators compare by trail_name
and location. Stream extraction (>>) throws InvalidHikeData
on malformed input. Stream insertion (<<) writes a
human-readable summary of the hike.
*/

#include "club_hike_Mistry.h"
#include <cstring>

using namespace std;

//Default constructor
//Initializes a ClubHike with a one-byte allocated empty
//C-string for trail_name (so trail_name is always a valid
//C-string, never null), and distance_miles set to 0.0.
//The location string default constructs to " ".
//Input: none
//Output: a default-initialized ClubHike object
ClubHike::ClubHike() : distance_miles(0.0)
{
    trail_name = new char[1];
    trail_name[0] = '\0';
}


//Parameterized constructor
//Creates a ClubHike with caller-provided trail name,
//location, and distance. Allocates new memory for
//trail_name and deep-copies the C-string from the caller
//so the object owns its own copy of the string. Throws
//InvalidHikeData if a_trail_name is null.
//Input:  a_trail_name - C-string trail name (cant be null)
//        a_location   - location of the hike
//        a_distance   - length of the hike in miles
//Output: a fully initialized ClubHike object
ClubHike::ClubHike(const char * a_trail_name,
                   const string & a_location,
                   float a_distance)
    : location(a_location), distance_miles(a_distance)
{
    if (!a_trail_name)
        throw InvalidHikeData{};

    trail_name = new char[strlen(a_trail_name) + 1];
    strcpy(trail_name, a_trail_name);
}


//Copy constructor
//Creates a new ClubHike that is a deep copy of source.
//Allocates fresh memory for trail_name so this object
//does not share dynamic memory with source. The location
//string and distance_miles are copied via initializer
//list using their natural copy semantics.
//Input: source - the ClubHike being copied
//Output: a new ClubHike with independent dynamic memory
ClubHike::ClubHike(const ClubHike & source)
    : location(source.location), distance_miles(source.distance_miles)
{
    trail_name = new char[strlen(source.trail_name) + 1];
    strcpy(trail_name, source.trail_name);
}


//Destructor
//Releases the dynamic memory allocated for trail_name.
//Uses delete[] to match the new char[] allocation
//performed by the constructors. The location string and
//distance_miles do not require manual cleanup.
//Input: none
//Output: none — releases this object's dynamic memory
ClubHike::~ClubHike()
{
    delete [] trail_name;
}


//Assignment operator
//Deep copies the data from rhs into this ClubHike. Performs
//a self-assignment check, releases the existing trail_name
//memory, allocates fresh memory, and copies all data members
//independently so the two objects share no dynamic memory.
//Returns *this by reference so chained assignment works
//(a = b = c).
//Input: rhs - the ClubHike being assigned from
//Output: reference to *this, so chained assignment works
ClubHike & ClubHike::operator=(const ClubHike & rhs)
{
    if (this != &rhs)
    {
        delete [] trail_name;
        trail_name = new char[strlen(rhs.trail_name) + 1];
        strcpy(trail_name, rhs.trail_name);
        location = rhs.location;
        distance_miles = rhs.distance_miles;
    }
    return *this;
}


//Relational operators
//All four compare hikes by distance_miles. They do not
//throw — comparing floats is always valid given the class
//invariant that distance_miles is properly initialized.
//Input:  rhs - the ClubHike on the right-hand side
//Output: true if the comparison holds, false otherwise

bool ClubHike::operator<(const ClubHike & rhs) const
{
    return distance_miles < rhs.distance_miles;
}

bool ClubHike::operator<=(const ClubHike & rhs) const
{
    return distance_miles <= rhs.distance_miles;
}

bool ClubHike::operator>(const ClubHike & rhs) const
{
    return distance_miles > rhs.distance_miles;
}

bool ClubHike::operator>=(const ClubHike & rhs) const
{
    return distance_miles >= rhs.distance_miles;
}


//Equality operators
//Two hikes are equal if they share the same trail_name
//(compared via strcmp) and the same location. Distance is 
//intentionally not part of the equality check, because the 
//same trail recorded on different outings may have different distances.
//Input: rhs - the ClubHike on the right-hand side
//Output: true if equal (==) or unequal (!=); false otherwise

bool ClubHike::operator==(const ClubHike & rhs) const
{
    return strcmp(trail_name, rhs.trail_name) == 0
        && location == rhs.location;
}

bool ClubHike::operator!=(const ClubHike & rhs) const
{
    return !(*this == rhs);
}


//Compound assignment operator (+=)
//Adds the distance of rhs into this ClubHike's
//distance_miles. The trail_name and location of *this
//are preserved, only the mileage accumulates. Throws
//IncompatibleHikes if the two hikes are at different
//locations, since combining miles across different
//locations does not produce meaningful data.
//Input: rhs - the ClubHike whose distance is added in
//Output: reference to *this, for chained use
ClubHike & ClubHike::operator+=(const ClubHike & rhs)
{
    if (location != rhs.location)
        throw IncompatibleHikes{};

    distance_miles += rhs.distance_miles;
    return *this;
}


//Binary addition operator (+)
//Produces a new ClubHike whose distance is the sum of
//*this and rhs. The new hike inherits the left operand's
//trail_name and location. Implemented in terms of +=
//so the same compatibility check applies. Throws
//IncompatibleHikes (via +=) if the two hikes are at
//different locations.
//Input: rhs - the ClubHike being added
//Output: a new ClubHike, returned by value
ClubHike ClubHike::operator+(const ClubHike & rhs) const
{
    ClubHike result(*this);
    result += rhs;
    return result;
}


//Stream insertion operator (<<)
//Writes a one-line summary of h to out.
//Format: "trail_name" at "location" "distance miles"
//Implemented as a friend function so the first operand
//can be an ostream rather than a ClubHike. Does not
//append a newline — the caller is responsible for line
//breaks.
//Input:  out - the output stream being written to
//        h   - the ClubHike being displayed
//Output: reference to out, for chained insertion
ostream & operator<<(ostream & out, const ClubHike & h)
{
    out << "\"" << h.trail_name << "\" at " << h.location
        << " (" << h.distance_miles << " miles)";
    return out;
}


//Stream extraction operator (>>)
//Reads trail name, location, and distance from in into h.
//Reads each of trail_name and location as a full line
//via getline. Reads distance as a float. All values are first
//stored in local variables and validated together. After validation
//passes does the function modify h, so a thrown exception
//never leaves h in a partially-modified state.
//Throws InvalidHikeData if the trail name or location is
//empty, the distance is negative, or the input stream
//fails. Implemented as a friend function so the first
//operand can be an istream rather than a ClubHike.
//Input: in - the input stream being read from
//       h  - the ClubHike being populated
//Output: reference to in, for chained extraction
istream & operator>>(istream & in, ClubHike & h)
{
    string buffer_trail;
    string buffer_location;
    float buffer_distance;

    getline(in, buffer_trail);
    getline(in, buffer_location);
    in >> buffer_distance;
    in.ignore();

    if (!in || buffer_trail.empty() || buffer_location.empty()
        || buffer_distance < 0)
        throw InvalidHikeData{};

    delete [] h.trail_name;
    h.trail_name = new char[buffer_trail.length() + 1];
    strcpy(h.trail_name, buffer_trail.c_str());
    h.location = buffer_location;
    h.distance_miles = buffer_distance;

    return in;
}

