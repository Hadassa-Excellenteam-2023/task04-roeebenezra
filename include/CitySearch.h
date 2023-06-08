#pragma once

#include "Coordinates.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>


class CitySearch {
private:
    std::multimap<std::string, Coordinates> m_cities;

public:
    explicit CitySearch(const std::string &fileName) {
        loadCities(fileName);
    }

    // load cities from file
    void loadCities(const std::string &fileName);

    // find cities in the given radius
    [[nodiscard]] std::multimap<std::string, Coordinates>
    findCities(const std::string &selectedCity, double radius, int norm) const;

    // count cities to the north of the selected city
    [[nodiscard]] static long countCitiesNorth(const std::multimap<std::string, Coordinates>&) ;
};
