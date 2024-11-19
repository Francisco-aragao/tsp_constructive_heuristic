#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include "city.hpp"

using namespace std;

class Utils {
    private:
        vector<int> path;
    public:        
        vector<int> getPath() {return path;};
        double findPath(int initialCityId, vector<City> cities, int numCities);
        int findCenterCity(vector<City> cities, int numCities);
        vector<City> receiveCoordinatesParameters(ifstream& inputFile, int numCities, string DISTANCE_TYPE);
        vector<string> findPathInfo(ifstream& inputFile);

};

#endif
