/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
26 April 2026
Filename: peak_Mistry.cpp

This file implements the Peak class. It defines
constructors, destructor, accessors, the operator+=
overload that adds a summit to the peaks_summitted
list, the has_summit search, and the friend stream
operators. Peak does not manage its own dynamic memory,
ClubHike handles trail_name and std::list manages
its own internal storage. so no rule-of-three
functions are needed here. Stream extraction throws
InvalidHikeData on invalid input.
*/

#include "peak_Mistry.h"

using namespace std;

//Default constructor
//Initializes a Peak with zero summit elevation and an
//empty peaks_summitted list. The base class default
//constructor runs implicitly to initialize ClubHike's
//inherited members. The list default-constructs as empty.
//Input: none
//Output: a default initialized Peak object
Peak::Peak() : summit_elevation_ft(0)
{
}


//Parameterized constructor
//Creates a Peak with provided trail data, summit
//elevation, and starting list of peaks. Forwards the
//base class data to ClubHike's constructor via the
//initializer list, then initializes Peak-specific data.
//Input:  a_trail_name       - C-string trail name
//        a_location         - location of the hike
//        a_distance         - length in miles
//        a_summit_elevation - elevation of the primary summit
//        a_peaks            - list of summits reached
//Output: a fully initialized Peak object
Peak::Peak(const char * a_trail_name,
           const string & a_location,
           float a_distance,
           int a_summit_elevation,
           const list<string> & a_peaks)
    : ClubHike(a_trail_name, a_location, a_distance),
      summit_elevation_ft(a_summit_elevation),
      peaks_summitted(a_peaks)
{
}


//Destructor
//No Peak specific cleanup required. The std::list
//destructor handles its internal storage automatically,
//and the base class destructor releases trail_name.
//Input: none
//Output: none
Peak::~Peak()
{
}


//Compound assignment operator (+=) for adding a summit
//Adds summit_name to the peaks_summitted list. Throws
//InvalidHikeData if summit_name is empty.
//Input: summit_name - the name of the summit to add
//Output: reference to *this, for chained use
Peak & Peak::operator+=(const string & summit_name)
{
    if (summit_name.empty())
        throw InvalidHikeData{};

    peaks_summitted.push_back(summit_name);
    return *this;
}


//Accessor for summit_elevation_ft
//Returns the elevation of the primary summit in feet.
//Input:  none
//Output: the summit elevation as an int
int Peak::get_summit_elevation() const
{
    return summit_elevation_ft;
}


//Accessor for the count of summits reached
//Returns the number of peaks in peaks_summitted. Casts
//list::size() (size_t) to int for client convenience.
//Input: none
//Output: the count as an int
int Peak::get_summit_count() const
{
    return static_cast<int>(peaks_summitted.size());
}


//Searches peaks_summitted for summit_name
//Iterates through the list using a range-based for
//loop. Returns true on the first match found.
//Input: summit_name - the summit to search for
//Output: true if found, false otherwise
bool Peak::has_summit(const string & summit_name) const
{
    for (const string & peak : peaks_summitted)
        if (peak == summit_name)
            return true;
    return false;
}


//Stream insertion operator (<<)
//Writes a one line summary of p to out, including base
//class data and Peak specific data. After the standard
//hike info, lists the summits reached in brackets.
//Implemented as a friend.
//Input:  out - the output stream
//        p   - the Peak being displayed
//Output: reference to out, for chained insertion
ostream & operator<<(ostream & out, const Peak & p)
{
    out << static_cast<const ClubHike &>(p)
        << " [summit elevation: " << p.summit_elevation_ft
        << " ft, " << p.peaks_summitted.size() << " peaks: ";

    bool first = true;
    for (const string & peak : p.peaks_summitted)
    {
        if (!first) out << ", ";
        out << peak;
        first = false;
    }
    out << "]";
    return out;
}


//Stream extraction operator (>>)
//Reads base-class data via ClubHike's >>, then reads
//summit elevation and a comma-separated list of summit
//names from a single line. Throws InvalidHikeData on
//bad input. Validates before committing to p.
//Input:  in - the input stream
//        p  - the Peak being populated
//Output: reference to in, for chained extraction
istream & operator>>(istream & in, Peak & p)
{
    in >> static_cast<ClubHike &>(p);

    int buffer_elevation;
    string buffer_peaks_line;

    in >> buffer_elevation;
    in.ignore();
    getline(in, buffer_peaks_line);

    if (!in || buffer_elevation < 0)
        throw InvalidHikeData{};

    list<string> buffer_peaks;
    string current;
    for (char c : buffer_peaks_line)
    {
        if (c == ',')
        {
            if (!current.empty())
            {
                buffer_peaks.push_back(current);
                current.clear();
            }
        }
        else if (c != ' ' || !current.empty())
        {
            current.push_back(c);
        }
    }
    if (!current.empty())
        buffer_peaks.push_back(current);

    p.summit_elevation_ft = buffer_elevation;
    p.peaks_summitted = buffer_peaks;

    return in;
}

