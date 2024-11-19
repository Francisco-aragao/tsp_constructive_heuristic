#include <ctime>
#include <string>
#include "utils.hpp"

using namespace std;
namespace fs = std::filesystem;

Utils utils;

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

        cities = utils.receiveParameters(inputFile, numCities, DISTANCE_TYPE);


        int initialCityId = utils.findCenterCity(cities, numCities);

        double pathCost = utils.findPath(initialCityId, cities, numCities);

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