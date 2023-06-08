task04-roeebenezra

Task 4 - STL Containers

## City Search

This program allows you to search for cities within a given radius of a selected city and count the number of cities to
the north of the selected city. The city data is loaded from a file.

### Data Structures

The program utilizes the following data structures:

#### Coordinates

The Coordinates struct represents the x and y coordinates of a city. It has the following members:

float x: Represents the x-coordinate of the city.
float y: Represents the y-coordinate of the city.

#### CitySearch

The CitySearch class encapsulates the functionality of the city search. It has the following member functions:

### Multimap

A std::multimap is a container in C++ Standard Template Library (STL) that allows multiple elements with the same key.
It is similar to a map, but it can store multiple values associated with a single key.

In the context of this program, the std::multimap<std::string, Coordinates> data structure is used to store the city
data. The city names are used as keys, and the corresponding coordinates are stored as values.

Using a multimap allows multiple cities to have the same name while preserving the ability to associate each city with
its coordinates. This is important because there may be different cities with the same name in different locations.

When searching for cities within a given radius of a selected city, the resulting cities and their coordinates are
stored in a new multimap and returned as the search result.

