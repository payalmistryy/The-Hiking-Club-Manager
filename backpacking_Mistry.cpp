/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
26 April 2026
Filename: backpacking_Mistry.cpp

This file implements the BackpackingTrip class. Because
BackpackingTrip manages its own dynamic memory for
campsite_name (a char *), it implements the full rule of
three: copy constructor, destructor, and assignment
operator. The copy constructor and assignment operator
chain to ClubHike's versions to handle the inherited
trail_name, then deep-copy the BackpackingTrip specific
campsite_name. The accessors return num_nights as an int
and campsite as a string copy for safety. Stream
extraction throws InvalidHikeData on malformed input.
*/

#include "backpacking_Mistry.h"
#include <cstring>

using namespace std;

//Default constructor
//Initializes a BackpackingTrip with a one-byte allocated
//empty C-string for campsite_name and num_nights set to
//zero. The base class default constructor runs implicitly
//to initialize ClubHike's inherited members.
//Input:  none
//Output: a default-initialized BackpackingTrip object
BackpackingTrip::BackpackingTrip() : num_nights(0)
{
    campsite_name = new char[1];
    campsite_name[0] = '\0';
}


//Parameterized constructor
//Creates a BackpackingTrip with caller-provided trail data,
//campsite name, and number of nights. Forwards the base
//class data to ClubHike's constructor via the initializer
//list, deep-copies a_campsite_name into fresh memory, and
//sets num_nights. Throws InvalidHikeData if a_campsite_name
//is null or num_nights is negative.
//Input:  a_trail_name     - C-string trail name
//        a_location       - location of the hike
//        a_distance       - length in miles
//        a_campsite_name  - C-string campsite name
//        a_num_nights     - number of overnight stays
//Output: a fully initialized BackpackingTrip object
BackpackingTrip::BackpackingTrip(const char * a_trail_name,
                                 const string & a_location,
                                 float a_distance,
                                 const char * a_campsite_name,
                                 int a_num_nights)
    : ClubHike(a_trail_name, a_location, a_distance),
      num_nights(a_num_nights)
{
    if (!a_campsite_name || a_num_nights < 0)
        throw InvalidHikeData{};

    campsite_name = new char[strlen(a_campsite_name) + 1];
    strcpy(campsite_name, a_campsite_name);
}


//Copy constructor
//Creates a new BackpackingTrip as a deep copy of source.
//Forwards source to the base class copy constructor via
//the initializer list, then deep-copies campsite_name and copies num_nights.
//Input: source - the BackpackingTrip being copied
//Output: a new BackpackingTrip with independent dynamic memory
BackpackingTrip::BackpackingTrip(const BackpackingTrip & source)
    : ClubHike(source), num_nights(source.num_nights)
{
    campsite_name = new char[strlen(source.campsite_name) + 1];
    strcpy(campsite_name, source.campsite_name);
}


//Destructor
//Releases the dynamic memory allocated for campsite_name.
//Uses delete[] to match the new char[] allocations.
//The base class destructor runs automatically after this
//returns, releasing the inherited trail_name.
//Input: none
//Output: none
BackpackingTrip::~BackpackingTrip()
{
    delete [] campsite_name;
}


//Assignment operator
//Deep-copies rhs into this BackpackingTrip. Performs a
//self-assignment check, calls the base class operator=
//to handle inherited members, then releases the existing
//campsite_name memory and allocates fresh memory for the
//deep copy. Returns *this by reference for chained
//assignment.
//Input: rhs - the BackpackingTrip being assigned from
//Output: reference to *this
BackpackingTrip & BackpackingTrip::operator=(const BackpackingTrip & rhs)
{
    if (this != &rhs)
    {
        ClubHike::operator=(rhs);

        delete [] campsite_name;
        campsite_name = new char[strlen(rhs.campsite_name) + 1];
        strcpy(campsite_name, rhs.campsite_name);
        num_nights = rhs.num_nights;
    }
    return *this;
}


//Accessor for num_nights
//Returns the number of overnight stays on this trip.
//Input:  none
//Output: the number of nights as an int
int BackpackingTrip::get_num_nights() const
{
    return num_nights;
}


//Accessor for campsite
//Returns the campsite name as a string copy. Converts
//from the internal char * to a string for safer client
//use (the client can't accidentally modify our memory).
//Input: none
//Output: a string copy of the campsite name
string BackpackingTrip::get_campsite() const
{
    return string(campsite_name);
}


//Stream insertion operator (<<)
//Writes a one-line summary of b to out, including base
//class data and BackpackingTrip specific data (campsite, nights). 
//Implemented as a friend.
//Input:  out - the output stream
//        b   - the BackpackingTrip being displayed
//Output: reference to out, for chained insertion
ostream & operator<<(ostream & out, const BackpackingTrip & b)
{
    out << static_cast<const ClubHike &>(b)
        << " [campsite: " << b.campsite_name
        << ", " << b.num_nights << " nights]";
    return out;
}


//Stream extraction operator (>>)
//Reads base-class data via ClubHike's >>, then reads
//campsite name and number of nights into local buffers
//and validates them. Throws InvalidHikeData on bad input.
//Only commits to b after all validation passes.
//Input:  in - the input stream
//        b  - the BackpackingTrip being populated
//Output: reference to in, for chained extraction
istream & operator>>(istream & in, BackpackingTrip & b)
{
    in >> static_cast<ClubHike &>(b);

    string buffer_campsite;
    int buffer_nights;

    getline(in, buffer_campsite);
    in >> buffer_nights;
    in.ignore();

    if (!in || buffer_campsite.empty() || buffer_nights < 0)
        throw InvalidHikeData{};

    delete [] b.campsite_name;
    b.campsite_name = new char[buffer_campsite.length() + 1];
    strcpy(b.campsite_name, buffer_campsite.c_str());
    b.num_nights = buffer_nights;

    return in;
}


