/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
26 April 2026
Filename: main_Mistry.cpp

Driver program for the Hiking Club. Provides a two-level
menu interface: a main menu that selects which derived
type to work with (DayHike, Peak, BackpackingTrip), and
a type-specific submenu for each that lets the user
manage a templated DLL of that type. Random data
generation uses srand/rand so populated collections
vary on each run. All loops are controlled by sentinel
boolean variables.
*/

#include "club_hike_Mistry.h"
#include "day_hike_Mistry.h"
#include "peak_Mistry.h"
#include "backpacking_Mistry.h"
#include "dll_Mistry.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;


//Pools of sample values used by the random data generator.
//Oregon trails are local to my home state; Big Sur trails
//are along the Central Coast of California where I have
//done some of my favorite hikes.
const string OREGON_TRAILS[]  = {"Eagle Creek", "Dog Mountain",
                                 "Cape Lookout", "Tom McCall Preserve",
                                 "Salmon Butte"};
const string BIG_SUR_TRAILS[] = {"Buzzard's Roost", "Pfeiffer Falls",
                                 "Mount Manuel", "Ewoldsen Trail",
                                 "Tanbark Trail", "McWay Falls Overlook",
                                 "Salmon Creek Falls"};
const string DIFFICULTIES[]   = {"mild", "intermediate", "expert"};
const string CAMPSITES[]      = {"Sykes Camp", "Barlow Camp",
                                 "Pine Valley Camp", "Redwood Camp",
                                 "Terrace Creek Camp"};
const string SUMMITS[]        = {"Cone Peak", "Junipero Serra Peak",
                                 "Bear Mountain", "Pinyon Peak",
                                 "Manuel Peak", "Pico Blanco"};


//Reads an integer menu choice from stdin and clears the
//newline so the next getline call starts clean.
//Input:  none
//Output: the integer the user typed
int read_choice()
{
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}


//Reads a single line of text from stdin into the result.
//Input:  prompt - text shown to the user before reading
//Output: the line typed (without the trailing newline)
string read_line(const string & prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}


//Generates one random DayHike using Oregon trails so any
//two generated hikes can be combined using + or +=.
//Input:  none
//Output: a randomly initialized DayHike
DayHike random_day_hike()
{
    const string & trail      = OREGON_TRAILS[rand() % 5];
    float distance            = (rand() % 200) / 10.0f + 1.0f;
    int elevation             = rand() % 4000 + 200;
    const string & difficulty = DIFFICULTIES[rand() % 3];
    return DayHike(trail.c_str(), "Oregon",
                   distance, elevation, difficulty);
}


//Generates one random Peak with a non-empty summit list.
//Uses Big Sur trails along California's Central Coast.
//Input:  none
//Output: a randomly initialized Peak
Peak random_peak()
{
    const string & trail = BIG_SUR_TRAILS[rand() % 7];
    float distance       = (rand() % 300) / 10.0f + 5.0f;
    int summit_elev      = rand() % 8000 + 6000;

    list<string> summit_list;
    int summit_count = rand() % 3 + 1;
    for (int j = 0; j < summit_count; ++j)
        summit_list.push_back(SUMMITS[rand() % 6]);

    return Peak(trail.c_str(), "California",
                distance, summit_elev, summit_list);
}


//Generates one random BackpackingTrip in Big Sur.
//Input:  none
//Output: a randomly initialized BackpackingTrip
BackpackingTrip random_backpacking_trip()
{
    const string & trail    = BIG_SUR_TRAILS[rand() % 7];
    float distance          = (rand() % 800) / 10.0f + 20.0f;
    const string & campsite = CAMPSITES[rand() % 5];
    int nights              = rand() % 9 + 1;
    return BackpackingTrip(trail.c_str(), "California",
                           distance, campsite.c_str(),
                           nights);
}


//Day Hikes submenu
//
//Submenu for the DayHike collection. Maintains a single DLL
//of DayHikes for the duration of this submenu and lets the
//user perform task-oriented operations on the collection.
//Loop is controlled by a sentinel boolean. Returns true if
//the user chose Quit so the main loop can also exit.
//Input:  none
//Output: true if user chose Quit, false if Back to main
bool day_hike_menu()
{
    DLL<DayHike> hikes;
    bool in_submenu = true;
    bool user_quit  = false;

    while (in_submenu)
    {
        cout << "\n--- Day Hikes ---\n";
        cout << "  1. Add hikes (random batch of 4)\n";
        cout << "  2. Add a hike (manual entry)\n";
        cout << "  3. View all hikes\n";
        cout << "  4. Search for a hike\n";
        cout << "  5. Remove a hike\n";
        cout << "  6. Extend a hike's mileage\n";
        cout << "  7. Combine two hikes into a summary (+)\n";
        cout << "  8. View accessors of a sample hike\n";
        cout << "  9. Save hike collection\n";
        cout << " 10. Clear all hikes\n";
        cout << " 11. Back to main menu\n";
        cout << " 12. Quit\n";
        cout << "Choice: ";

        int choice = read_choice();

        try
        {
            if (choice == 11)
                in_submenu = false;
            else if (choice == 12)
            {
                in_submenu = false;
                user_quit  = true;
            }
            else if (choice == 1)
            {
                for (int i = 0; i < 4; ++i)
                    hikes.insert(random_day_hike());
                cout << "Added 4 random hikes to the collection.\n";
            }
            else if (choice == 2)
            {
                cout << "Enter a hike. Trail name, location,\n"
                     << "and difficulty go on their own lines.\n"
                     << "Distance and elevation gain are numbers.\n";
                DayHike fresh;
                cin >> fresh;
                hikes.insert(fresh);
                cout << "Added: " << fresh << "\n";
            }
            else if (choice == 3)
                hikes.display();
            else if (choice == 4)
            {
                string trail = read_line("Trail name: ");
                string loc   = read_line("Location: ");
                DayHike lookup(trail.c_str(), loc, 0.0f, 0, "");
                DayHike found = hikes.retrieve(lookup);
                cout << "Found: " << found << "\n";
            }
            else if (choice == 5)
            {
                string trail = read_line("Trail name to remove: ");
                string loc   = read_line("Location: ");
                DayHike target(trail.c_str(), loc, 0.0f, 0, "");
                hikes.remove(target);
                cout << "Removed.\n";
            }
            else if (choice == 6)
            {
                DayHike a = random_day_hike();
                DayHike b = random_day_hike();
                cout << "Hike a: " << a << "\nHike b: " << b << "\n";
                a += b;
                cout << "After combining b into a:\n  " << a << "\n";
            }
            else if (choice == 7)
            {
                DayHike a = random_day_hike();
                DayHike b = random_day_hike();
                cout << "Hike a: " << a << "\nHike b: " << b << "\n";
                ClubHike summary = a + b;
                cout << "Combined summary (base-class data only):\n  "
                     << summary << "\n";
            }
            else if (choice == 8)
            {
                DayHike sample = random_day_hike();
                cout << "Sample hike: " << sample << "\n";
                cout << "  get_elevation_gain(): " << sample.get_elevation_gain() << " ft\n";
                cout << "  get_difficulty():     " << sample.get_difficulty() << "\n";
            }
            else if (choice == 9)
            {
                DLL<DayHike> backup(hikes);
                cout << "Backup copy contents:\n";
                backup.display();

                DLL<DayHike> reassigned;
                reassigned = hikes;
                cout << "Reassigned copy contents:\n";
                reassigned.display();
            }
            else if (choice == 10)
            {
                hikes.remove_all();
                cout << "All hikes cleared. Collection empty? "
                     << (hikes.is_empty() ? "yes" : "no") << "\n";
            }
            else
                cout << "Invalid choice.\n";
        }
        catch (const InvalidHikeData &)
        {
            cout << "  [Could not complete that action: the hike data was invalid.]\n";
        }
        catch (const IncompatibleHikes &)
        {
            cout << "  [Could not complete that action: the two hikes are at different locations.]\n";
        }
        catch (const EmptyList &)
        {
            cout << "  [No hikes in the collection yet.]\n";
        }
        catch (const ItemNotFound &)
        {
            cout << "  [That hike was not found in the collection.]\n";
        }
    }

    return user_quit;
}


//Peak Hikes submenu
//
//Submenu for the Peak collection. Same shape as the Day
//Hikes submenu, plus task-oriented options for adding
//summits and checking summit membership. Loop is
//controlled by a sentinel boolean.
//Input:  none
//Output: true if user chose Quit, false if Back to main
bool peak_menu()
{
    DLL<Peak> peaks;
    bool in_submenu = true;
    bool user_quit  = false;

    while (in_submenu)
    {
        cout << "\n--- Peak Hikes ---\n";
        cout << "  1. Add peaks (random batch of 4)\n";
        cout << "  2. Add a peak (manual entry)\n";
        cout << "  3. View all peaks\n";
        cout << "  4. Search for a peak\n";
        cout << "  5. Remove a peak\n";
        cout << "  6. Add a summit to a sample peak hike\n";
        cout << "  7. Check whether a peak hike includes a summit\n";
        cout << "  8. Save peak collection (test deep copy)\n";
        cout << "  9. Clear all peaks\n";
        cout << " 10. Back to main menu\n";
        cout << " 11. Quit\n";
        cout << "Choice: ";

        int choice = read_choice();

        try
        {
            if (choice == 10)
                in_submenu = false;
            else if (choice == 11)
            {
                in_submenu = false;
                user_quit  = true;
            }
            else if (choice == 1)
            {
                for (int i = 0; i < 4; ++i)
                    peaks.insert(random_peak());
                cout << "Added 4 random peak hikes.\n";
            }
            else if (choice == 2)
            {
                cout << "Enter a peak hike. Trail name, location,\n"
                     << "distance, summit elevation, and a comma-\n"
                     << "separated list of summits, each on a line.\n";
                Peak fresh;
                cin >> fresh;
                peaks.insert(fresh);
                cout << "Added: " << fresh << "\n";
            }
            else if (choice == 3)
                peaks.display();
            else if (choice == 4)
            {
                string trail = read_line("Trail name: ");
                string loc   = read_line("Location: ");
                list<string> empty_list;
                Peak lookup(trail.c_str(), loc, 0.0f, 0, empty_list);
                Peak found = peaks.retrieve(lookup);
                cout << "Found: " << found << "\n";
            }
            else if (choice == 5)
            {
                string trail = read_line("Trail name to remove: ");
                string loc   = read_line("Location: ");
                list<string> empty_list;
                Peak target(trail.c_str(), loc, 0.0f, 0, empty_list);
                peaks.remove(target);
                cout << "Removed.\n";
            }
            else if (choice == 6)
            {
                Peak p = random_peak();
                cout << "Sample peak hike: " << p << "\n";
                string summit = read_line("Summit to add: ");
                p += summit;
                cout << "After adding the summit:\n  " << p << "\n";
            }
            else if (choice == 7)
            {
                Peak p = random_peak();
                p += "Manuel Peak";
                cout << "Sample peak hike: " << p << "\n";
                string query = read_line("Summit to check: ");
                cout << "  has_summit(\"" << query << "\")? "
                     << (p.has_summit(query) ? "yes" : "no") << "\n";
                cout << "  get_summit_count(): " << p.get_summit_count() << "\n";
            }
            else if (choice == 8)
            {
                DLL<Peak> backup(peaks);
                cout << "Backup copy contents:\n";
                backup.display();

                DLL<Peak> reassigned;
                reassigned = peaks;
                cout << "Reassigned copy contents:\n";
                reassigned.display();
            }
            else if (choice == 9)
            {
                peaks.remove_all();
                cout << "All peaks cleared. Collection empty? "
                     << (peaks.is_empty() ? "yes" : "no") << "\n";
            }
            else
                cout << "Invalid choice.\n";
        }
        catch (const InvalidHikeData &)
        {
            cout << "  [Could not complete that action: the peak data was invalid.]\n";
        }
        catch (const EmptyList &)
        {
            cout << "  [No peaks in the collection yet.]\n";
        }
        catch (const ItemNotFound &)
        {
            cout << "  [That peak hike was not found in the collection.]\n";
        }
    }

    return user_quit;
}


//Backpacking Trips submenu
//
//Submenu for the BackpackingTrip collection. Task-oriented
//options including combining two trips by mileage. Loop is
//controlled by a sentinel boolean.
//Input: none
//Output: true if user chose Quit, false if Back to main
bool backpacking_menu()
{
    DLL<BackpackingTrip> trips;
    bool in_submenu = true;
    bool user_quit  = false;

    while (in_submenu)
    {
        cout << "\n--- Backpacking Trips ---\n";
        cout << "  1. Add trips (random batch of 4)\n";
        cout << "  2. Add a trip (manual entry)\n";
        cout << "  3. View all trips\n";
        cout << "  4. Search for a trip\n";
        cout << "  5. Remove a trip\n";
        cout << "  6. Extend a trip's mileage\n";
        cout << "  7. View accessors of a sample trip\n";
        cout << "  8. Save trip collection \n";
        cout << "  9. Clear all trips\n";
        cout << " 10. Back to main menu\n";
        cout << " 11. Quit\n";
        cout << "Choice: ";

        int choice = read_choice();

        try
        {
            if (choice == 10)
                in_submenu = false;
            else if (choice == 11)
            {
                in_submenu = false;
                user_quit  = true;
            }
            else if (choice == 1)
            {
                for (int i = 0; i < 4; ++i)
                    trips.insert(random_backpacking_trip());
                cout << "Added 4 random backpacking trips.\n";
            }
            else if (choice == 2)
            {
                cout << "Enter a trip. Trail name, location,\n"
                     << "campsite name, distance, and number\n"
                     << "of nights, each on its own line.\n";
                BackpackingTrip fresh;
                cin >> fresh;
                trips.insert(fresh);
                cout << "Added: " << fresh << "\n";
            }
            else if (choice == 3)
                trips.display();
            else if (choice == 4)
            {
                string trail = read_line("Trail name: ");
                string loc   = read_line("Location: ");
                BackpackingTrip lookup(trail.c_str(), loc, 0.0f, "", 0);
                BackpackingTrip found = trips.retrieve(lookup);
                cout << "Found: " << found << "\n";
            }
            else if (choice == 5)
            {
                string trail = read_line("Trail name to remove: ");
                string loc   = read_line("Location: ");
                BackpackingTrip target(trail.c_str(), loc, 0.0f, "", 0);
                trips.remove(target);
                cout << "Removed.\n";
            }
            else if (choice == 6)
            {
                BackpackingTrip a = random_backpacking_trip();
                BackpackingTrip b = random_backpacking_trip();
                cout << "Trip a: " << a << "\nTrip b: " << b << "\n";
                a += b;
                cout << "After combining b into a:\n  " << a << "\n";
            }
            else if (choice == 7)
            {
                BackpackingTrip sample = random_backpacking_trip();
                cout << "Sample trip: " << sample << "\n";
                cout << "  get_num_nights(): " << sample.get_num_nights() << "\n";
                cout << "  get_campsite():   " << sample.get_campsite() << "\n";
            }
            else if (choice == 8)
            {
                DLL<BackpackingTrip> backup(trips);
                cout << "Backup copy contents:\n";
                backup.display();

                DLL<BackpackingTrip> reassigned;
                reassigned = trips;
                cout << "Reassigned copy contents:\n";
                reassigned.display();
            }
            else if (choice == 9)
            {
                trips.remove_all();
                cout << "All trips cleared. Collection empty? "
                     << (trips.is_empty() ? "yes" : "no") << "\n";
            }
            else
                cout << "Invalid choice.\n";
        }
        catch (const InvalidHikeData &)
        {
            cout << "  [Could not complete that action: the trip data was invalid.]\n";
        }
        catch (const IncompatibleHikes &)
        {
            cout << "  [Could not complete that action: the two trips are at different locations.]\n";
        }
        catch (const EmptyList &)
        {
            cout << "  [No trips in the collection yet.]\n";
        }
        catch (const ItemNotFound &)
        {
            cout << "  [That trip was not found in the collection.]\n";
        }
    }

    return user_quit;
}


//Main loop - Program starts
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "  CS 302 Program 2 - Hiking Club\n";
    cout << "------------------------------------------------\n";

    bool keep_going = true;

    while (keep_going)
    {
        cout << "\n--- Main Menu ---\n";
        cout << "  1. Day Hikes\n";
        cout << "  2. Peak Hikes\n";
        cout << "  3. Backpacking Trips\n";
        cout << "  0. Quit\n";
        cout << "Choice: ";

        int choice = read_choice();

        if (choice == 0)
            keep_going = false;
        else if (choice == 1)
        {
            if (day_hike_menu()) keep_going = false;
        }
        else if (choice == 2)
        {
            if (peak_menu()) keep_going = false;
        }
        else if (choice == 3)
        {
            if (backpacking_menu()) keep_going = false;
        }
        else
            cout << "Invalid choice.\n";
    }

    cout << "\nGoodbye!\n";
    return 0;
}