#include "city.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


void processFile(const string& filename) {
    std::clock_t start;
    double totalPathCost = 0;
    double totalElapsedTime = 0;

    // Read the file 5 times
    for (int iteration = 0; iteration < 5; ++iteration) {

        string DISTANCE_TYPE;
        string info;
        int numCities;
        vector<City> cities;
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        start = std::clock();
        while (info != "NODE_COORD_SECTION" && inputFile >> info) {
            if (info == "DIMENSION:") {
                inputFile >> info;
                numCities = stoi(info);
            } else if (info == "DIMENSION") {
                inputFile >> info; // reading ':'
                inputFile >> info;
                numCities = stoi(info);
            }

            if (info == "EDGE_WEIGHT_TYPE:") {
                inputFile >> info;
                DISTANCE_TYPE = info;
            } else if (info == "EDGE_WEIGHT_TYPE") {
                inputFile >> info; // reading ':'
                inputFile >> info;
                DISTANCE_TYPE = info;
            }
        }

        City initialCity(0, 0, 0, numCities);
        cities.push_back(initialCity);

        int id;
        float x, y;
        for (int i = 0; i < numCities; i++) {
            inputFile >> id >> x >> y;
            City newCity(id, x, y, numCities);
            cities.push_back(newCity);

            for (auto city : cities) {
                if (city.getId() == 0)
                    continue;

                if (city == newCity)
                    continue;

                if (city.returnDistanceTo(id) != -1)
                    continue;

                double distance = city.calculateDistanceTo(newCity, DISTANCE_TYPE);
                city.setDistances(id, distance);
                newCity.setDistances(city.getId(), distance);

                cities[city.getId()] = city;
                cities[id] = newCity;
            }
        }

        double minDistance = 5000000;
        int idCenterCity = 0;
        for (auto city : cities) {
            if (city.getId() == 0)
                continue;

            double sum = 0;
            for (int i = 1; i <= numCities; i++) {
                if (city.getId() == i)
                    continue;

                sum += city.returnDistanceTo(i);
            }

            if (sum < minDistance) {
                minDistance = sum;
                idCenterCity = city.getId();
            }
        }

        int initialCityId = 1;
        vector<int> path;

        path.push_back(initialCityId);

        int currentCityId = initialCityId;
        
        double pathCost = 0;

        while ((int)path.size() < numCities) {
            double minDistance = 5000000;
            int nextCityId = 0;

            for (auto city : cities) {
                if (city.getId() == 0)
                    continue;

                if (city.getId() == currentCityId)
                    continue;

                if (find(path.begin(), path.end(), city.getId()) != path.end())
                    continue;

                double distance = city.returnDistanceTo(currentCityId);
                if (distance < minDistance) {
                    if (minDistance != 5000000)
                        pathCost -= minDistance;

                    pathCost += distance;
                    minDistance = distance;
                    nextCityId = city.getId();
                }
            }

            path.push_back(nextCityId);
            currentCityId = nextCityId;
        }
        path.push_back(initialCityId);
        pathCost += cities[currentCityId].returnDistanceTo(initialCityId);

        double elapsed = double(std::clock() - start) / CLOCKS_PER_SEC;

        totalPathCost += pathCost;
        totalElapsedTime += elapsed;
    }

    // Calculate and display the average results

    double avgPathCost = totalPathCost / 5;
    double avgElapsedTime = totalElapsedTime / 5;

    cout << "Results for " << filename << ":\n";
    cout << "Average Path Cost: " << avgPathCost << "\n";
    cout << "Average Elapsed Time: " << avgElapsedTime << " seconds\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <folder_path>" << endl;
        return 1;
    }

    string folderPath = argv[1];

    // Process all .tsp files in the folder
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".tsp") {
            processFile(entry.path().string());
        }
    }

    return 0;
}