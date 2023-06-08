#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "CitySearch.h"


int main() {
    try {
        std::string fileName = "data.txt"; // Replace with the actual file name
        CitySearch citySearch(fileName);

        std::string selectedCity;
        std::cout << "Please enter selected city name (with line break after it), or '0' to exit:\n";
        while (std::getline(std::cin >> std::ws, selectedCity)) {
            if (selectedCity == "0") {
                break; // Exit loop if '0' is entered
            }

            double radius;
            std::cout << "Please enter the wanted radius: ";
            std::cin >> radius;

            int norm;
            std::cout << "Please enter the wanted norm (0 - L2, 1 - Lin, 2 - L1): ";
            std::cin >> norm;

            std::multimap<std::string, Coordinates> searchResult = citySearch.findCities(selectedCity, radius, norm);
            std::cout << "Search result:\n";
            std::cout << searchResult.size() << " city/cities found in the given radius.\n";

            long countNorth = citySearch.countCitiesNorth(searchResult);
            std::cout << countNorth << " cities are to the north of the selected city. City list:\n";

            for (const auto& city : searchResult) {
                std::cout << city.first << '\n';
            }

            std::cout << "Please enter selected city name (with line break after it), or '0' to exit:\n";
        }
        std::cout << "Bye" << std::endl;
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
