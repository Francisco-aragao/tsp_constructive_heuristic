#include "city.hpp"
#include <algorithm> 
#include <ctime>

using namespace std;

int main () {

    std::clock_t start = std::clock();
    std::vector<City> cities;
    int numCities;
    string DISTANCE_TYPE;

    string info;
    
    //cities info starts after this line
    while (info != "NODE_COORD_SECTION") {
        cin >> info;        
        //cout << info << endl;

        if (info == "DIMENSION:") {
            cin >> info;
            numCities = stoi(info);
        } else if (info == "DIMENSION") {
            cin >> info; // reading ':'
            cin >> info;
            numCities = stoi(info);
        }

        if (info == "EDGE_WEIGHT_TYPE:") {
            cin >> info;
            DISTANCE_TYPE = info;
        } else if (info == "EDGE_WEIGHT_TYPE") {
            cin >> info; // reading ':'
            cin >> info;
            DISTANCE_TYPE = info;
        }
    }

    City initialCity(0, 0, 0, numCities);
    cities.push_back(initialCity);

    int id;
    float x, y;
    for (int i = 0; i < numCities; i++) {
        
        cin >> id;
        cin >> x;
        cin >> y;

        City newCity(id, x, y, numCities);
        cities.push_back(newCity);

        for (auto city : cities) {

            if (city.getId() == 0)
                continue;

            if (city == newCity)
                continue;

            if (city.returnDistanceTo(id) != -1) {
                continue;
            }

            double distance = city.calculateDistanceTo(newCity, DISTANCE_TYPE);
            city.setDistances(id, distance);
            newCity.setDistances(city.getId(), distance);

            //cout << "Distance between " << city.getId() << " and " << newCity.getId() << ": " << city.returnDistanceTo(newCity.getId()) << endl;

            // update vector cities
            cities[city.getId()] = city;
            cities[id] = newCity;
        }
    }
    
    //cout << "Num cities: " << numCities << endl;
    
    double minDistance = 5000000;
    int idCenterCity = 0;

    for (auto city : cities) {

        if (city.getId() == 0)
            continue;

        double sum = 0;

        //cout << "City info " << city.getId() << endl;
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



    //int initialCityId = idCenterCity;

    // initial city is the first city
    int initialCityId = 1;

    // construct the path starting from the center city and going to the closest city, until all cities are visited

    vector<int> path;
    path.push_back(initialCityId);

    int currentCityId = initialCityId;
    double pathCost = 0;

    while ((int) path.size() < numCities) {

        double minDistance = 5000000;
        int nextCityId = 0;

        for (auto city : cities) {

            if (city.getId() == 0)
                continue;

            if (city.getId() == currentCityId)
                continue;

            // if city is already in the path, skip it
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
    // add path to the initial city
    path.push_back(initialCityId);
    pathCost += cities[currentCityId].returnDistanceTo(initialCityId);

    cout << "Center city " << idCenterCity << endl;
    cout << "Path: ";
    for (auto cityId : path) {
        cout << cityId << " ";
    }

    cout << endl;

    cout << "Path cost: " << pathCost << endl;

    std::clock_t end = std::clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;


    return 0;   
}