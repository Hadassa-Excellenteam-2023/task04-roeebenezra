#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

struct City {
    std::string name;
    double x;
    double y;

    City(std::string cityName, double xPos, double yPos)
            : name(std::move(cityName)), x(xPos), y(yPos) {}

    friend std::ostream &operator<<(std::ostream &os, const City &city);
};

std::ostream &operator<<(std::ostream &os, const City &city) {
    os << city.name << ", " << city.x << " - " << city.y;
    return os;
}


std::vector<City> loadCities(const std::string& fileName) {
    std::vector<City> cities;
    std::ifstream file(fileName);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cityName;
        double xPos, yPos;

        if (!(std::getline(iss, cityName, ',')) || !(iss >> xPos) || !(iss.ignore(1)) || !(iss >> yPos)) {
            std::cout << "Failed to parse line: " << line << std::endl;
            continue;  // Skip this line and continue with the next one
        }

        cities.emplace_back(cityName, xPos, yPos);
    }

    std::cout << cities.size() << std::endl;

    file.close();
    return cities;
}


double calculateDistance(const City &city1, const City &city2, int norm) {
    if (norm == 0) {
        double distanceX = city1.x - city2.x;
        double distanceY = city1.y - city2.y;
        return std::sqrt(distanceX * distanceX + distanceY * distanceY);
    } else if (norm == 1) {
        return std::abs(city1.x - city2.x) + std::abs(city1.y - city2.y);
    }
    // Add more cases for other norms if needed

    return 0.0;
}

std::vector<City> findCities(const std::vector<City> &cities, const City &startCity, double radius, int norm) {
    std::vector<City> result;
    for (const auto &city: cities) {
        double distance = calculateDistance(startCity, city, norm);
        if (distance <= radius) {
            result.push_back(city);
        }
    }
    return result;
}

int main() {
    std::string fileName = "data.txt"; // Replace with the actual file name
    std::vector<City> cities = loadCities(fileName);

    // Example usage
    City startCity("StartCity", 30.0, 80.0);
    double searchRadius = 20.0;
    int norm = 0;

    std::vector<City> foundCities = findCities(cities, startCity, searchRadius, norm);

    // Print the found cities
    for (const auto &city: foundCities) {
        std::cout << "City: " << city.name << ", X: " << city.x << ", Y: " << city.y << std::endl;
    }


    return 0;
}
