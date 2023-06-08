
#include "CitySearch.h"


void CitySearch::loadCities(const std::string &fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    std::string line;
    std::string cityName;
    Coordinates coordinates(0.0, 0.0);

    while (std::getline(inputFile, line)) {
        cityName = line;
        if (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            if (!(iss >> coordinates.x)) {
                throw std::runtime_error("Error reading x-coordinate for city: " + cityName);
            }
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '-');
            if (!(iss >> coordinates.y)) {
                throw std::runtime_error("Error reading y-coordinate for city: " + cityName);
            }

            cities.insert({cityName, coordinates});
        }
    }

    inputFile.close();
}


[[nodiscard]] std::multimap<std::string, Coordinates>
CitySearch::findCities(const std::string &selectedCity, double radius, int norm) const {
    auto range = cities.equal_range(selectedCity);
    if (range.first == range.second) {
        throw std::runtime_error(
                "ERROR: \"" + selectedCity + "\" isn't found in the city list. Please try again.");
    }

    std::multimap<std::string, Coordinates> searchResult;

    // Define lambda functions for different norms
    using DistanceFunction = std::function<double(const Coordinates &, const Coordinates &)>;
    std::map<int, DistanceFunction> distanceFuncs{
            {0, [](const Coordinates &c1, const Coordinates &c2) {
                return std::sqrt(std::pow(c1.x - c2.x, 2) + std::pow(c1.y - c2.y, 2));
            }},
            {1, [](const Coordinates &c1, const Coordinates &c2) {
                return std::max(std::abs(c1.x - c2.x), std::abs(c1.y - c2.y));
            }},
            {2, [](const Coordinates &c1, const Coordinates &c2) {
                return std::abs(c1.x - c2.x) + std::abs(c1.y - c2.y);
            }},
    };

    // Find the distance function for the given norm
    auto distanceFunc = distanceFuncs.find(norm);
    if (distanceFunc == distanceFuncs.end()) {
        throw std::runtime_error("Invalid norm type.");
    }

    const Coordinates &selectedCoords = range.first->second;
    for (const auto &city: cities) {
        const std::string &cityName = city.first;
        const Coordinates &coords = city.second;
        double distance = distanceFunc->second(coords, selectedCoords);
        if (distance <= radius) {
            searchResult.insert({cityName, coords});
        }
    }

    return searchResult;
}


[[nodiscard]] long CitySearch::countCitiesNorth(const std::multimap<std::string, Coordinates>& cities) {
    // Count the number of cities that are to the north of the selected city
    double selectedY = range.first->second.y;
    return std::count_if(cities.begin(), cities.end(), [&](const auto &city) {
        return city.second.y < selectedY;
    });
}