#include <iostream>
#include <map>
#include <stdexcept>
#include "src\pugixml.hpp"
#include "MST.cpp"

struct Transport {
private:
    struct dataOfRoute {
        std::vector <std::pair <double, double>> coodinates;
        double dist = 0;
        int numberOfStations = 0;
    };
    std::string numberMaxStations, numberMaxDist;

    double maxDist = 0;
    int maxStations = 0;

    std::map <std::string, dataOfRoute> routes;

public:
    void setData(const std::string &number, double x, double y) {
        if (routes[number].numberOfStations != 0) {
            routes[number].coodinates.emplace_back(x, y);
            routes[number].numberOfStations++;
        }
        else {
            routes[number].coodinates.emplace_back(x, y);
            routes[number].numberOfStations = 1;
        }
    }

    void findMaxDist(const std::string &type) {

        for (auto & i : routes) {
            double newDist = MST(i.second.coodinates);
            i.second.dist = newDist;
            if (newDist > maxDist) {
                numberMaxDist = i.first;
                maxDist = newDist;
            }
        }
        std::cout << type << "ный маршрут с самым длинным путём: " << numberMaxDist << "\n";
    }

    void findMaxStation(const std::string &type) {
        for (auto & i : routes) {
            if (i.second.numberOfStations > maxStations) {
                numberMaxStations = i.first;
                maxStations = i.second.numberOfStations;
            }
        }
        std::cout << type << "ный маршрут с самым большим числом остановок: " << numberMaxStations;
        std::cout << " с количеством " << maxStations << "\n";
    }
};

int main() {
    system("chcp 65001");
    pugi::xml_document doc;

    auto result = doc.load_file("../src/data.xml");
    if (result.status != 0) {
        throw std::logic_error("Файла не существует");
    }

    Transport bus;
    Transport tram;
    Transport trolleybus;
    std::map <std::string, int> locations;

    auto data_set = doc.child("dataset");
    for (auto station = data_set.child("transport_station"); station; station = station.next_sibling()) {

        //Сбор данных по остановкам
        std::string location = station.child("location").first_child().value();
        std::string name;
        location += ',';
        for (auto i : location) {
            if (i == ',') {
                if (!name.empty()) {
                    locations[name] += 1;
                }
                name = "";
                continue;
            }
            name += i;
        }

        //Сбор данных по маршрутам
        std::string routes = station.child("routes").first_child().value();
        routes += ',';

        std::string number;
        for (auto i : routes) {
            if (i == ',' || i == '.') {
                std::string coordinates = station.child("coordinates").first_child().value();
                std::string coordinate;
                double x, y;

                for (char j : coordinates) {
                    if (j == ',') {
                        x = std::stod(coordinate);
                        coordinate = "";
                        continue;
                    }
                    coordinate += j;
                }

                y = std::stod(coordinate);
                if ((std::string) station.child("type_of_vehicle").first_child().value() == "Троллейбус") {
                    trolleybus.setData(number, x, y);
                }
                else if ((std::string) station.child("type_of_vehicle").first_child().value() == "Автобус") {
                    bus.setData(number, x, y);
                }
                else if ((std::string) station.child("type_of_vehicle").first_child().value() == "Трамвай") {
                    tram.setData(number, x, y);
                }

                number = "";
                continue;
            }
            number += i;
        }


    }

    std::cout << ">-------------------------------------------------<\n";
    bus.findMaxStation("Автобус");
    tram.findMaxStation("Трамвай");
    trolleybus.findMaxStation("Троллейбус");
    std::cout << ">-------------------------------------------------<\n";
    bus.findMaxDist("Автобус");
    tram.findMaxDist("Трамвай");
    trolleybus.findMaxDist("Троллейбус");
    std::cout << ">-------------------------------------------------<\n";

    int max = 0;
    std::string nameMax;
    for (auto & i : locations) {
        if (i.second > max) {
            max = i.second;
            nameMax = i.first;
        }
    }
    std::cout << "Самое большое количетсво остановок у " << nameMax << " и количетсво " << max << "\n";

    return 0;
}