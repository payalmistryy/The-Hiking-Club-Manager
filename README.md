# Hiking Club Manager

A C++ application developed for CS 302 (Programming Methodologies and Software Implementation) at Portland State University.

## Overview

A menu-driven system that manages a hiking club's trail outings across three distinct hike types. The application stores each collection in a **custom templated doubly linked list** and supports adding, searching, removing, combining, and saving hikes. It demonstrates advanced object-oriented design, generic programming with templates, fully recursive data structure operations, and disciplined manual memory management.

## Features

- Three distinct hike types organized in a single inheritance hierarchy: Day Hikes, Peak Hikes, and Backpacking Trips
- Generic storage with a hand-built templated doubly linked list that holds any hike type
- Combine and extend hikes through overloaded operators (`+`, `+=`) with location-compatibility checks
- Custom exception types for invalid data, incompatible hikes, empty lists, and missing items
- Random data generation so each run populates collections with varied sample data
- Two-level menu interface for managing each collection independently

## Technical Highlights

- Single inheritance hierarchy with an abstract-style base class (`ClubHike`) and three derived classes (`DayHike`, `Peak`, `BackpackingTrip`)
- Templated `DLL<T>` and `Node<T>` classes — all repetitive list operations (insert, remove, display, retrieve, remove_all) implemented with **exclusively recursive** private helper methods
- Comprehensive operator overloading: relational (`<`, `<=`, `>`, `>=`), equality (`==`, `!=`), compound assignment (`+=`), arithmetic (`+`), and stream (`<<`, `>>`)
- Resolved name-hiding by re-exposing the base class operator (`using ClubHike::operator+=`) so a derived class can overload `+=` for its own purpose without losing inherited behavior
- Dynamic memory managed safely with the **Rule of Three** (destructor, copy constructor, assignment operator) in every class that owns raw pointers
- Mix of raw memory management (`char *`) and modern C++ (STL `string`, `list`)
- Custom exception classes used for error signaling where operators cannot return status flags
- Template implementation split into a `.tpp` file included inside the header guard, following correct template instantiation practice
- Compiled warning-free with the `-Wall` flag

## Tech Stack

- **Language:** C++ (C++17)
- **Concepts:** Object-Oriented Programming, Inheritance, Polymorphism, Templates / Generic Programming, Operator Overloading, Recursion, Exception Handling, Dynamic Memory Management
- **Data Structures:** Templated Doubly Linked List, STL `list`

## How to Run

```bash
g++ -Wall -o hiking_club *.cpp
./hiking_club
```

## Author

Payal Mistry — Computer Science, Portland State University
