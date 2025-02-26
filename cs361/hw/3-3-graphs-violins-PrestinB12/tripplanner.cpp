#include <iostream>
#include <fstream>

#include "itinerary.h"

using namespace std;


void read(std::istream &in, Itinerary& itinerary)
{
    string city1, city2, road;
    double distance;

    // Read in the roads data
    while (in.good())
    {
        string line;
        getline(in, line);
        if (in.good() && line.length() > 0)
        {
            istringstream in(line);
            in >> road >> city1;
            while (in >> distance)
            {
                in >> city2;
                Leg newRoad {city1, city2,road, distance};
                itinerary.addRoad(newRoad);
                city1 = city2;
            }
        }
    }
}


int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cerr << "Usage: " << argv[0]
         << " fileName startingCity endingCity" << endl;
    return 1;
  }

  string startingCityName = argv[2];
  string destinationCityName = argv[3];

  if (startingCityName == destinationCityName)
    cout << "You are already at " << startingCityName << endl;
  else
  {
    Itinerary itinerary;

    // Read in the roads data
    ifstream roadsIn(argv[1]);
    read(roadsIn, itinerary);
    
    vector<Leg> path = itinerary.travelPlan(startingCityName, destinationCityName);

    if (path.size() > 0)
    {
      for (Leg leg : path)
      {
        cout << leg << endl;
      }
      cout << "Trip length: " << itinerary.getLastTripLength() << endl;
    }
    else
      cout << "You can't get from " << startingCityName
           << " to " << destinationCityName << endl;
  }
  return 0;
}
