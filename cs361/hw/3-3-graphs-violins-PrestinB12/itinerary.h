#ifndef ITINERARY_H
#define ITINERARY_H

#include <iostream>
#include <map>
#include <vector>

#include "leg.h"
#include "graph.h"

/**
 * @brief A collection of road segments that cna be used to plan a trip from
 *        one city to another.
 * 
 */
class Itinerary {
public:

    /**
     * @brief Construct a new Itinerary object with no road segments.
     * 
     */
    Itinerary();

    /**
     * @brief Add a road segment connecting two cities.
     * 
     * Note that a segment that connects city1 to city2 also connects
     * city2 to city1.
     * 
     * @param roadSegment indicates the cities being connected, the name of
     *                    the road, and the distance between the cities along
     *                    that road.
     */
    void addRoad(const Leg& roadSegment);

    /**
     * @brief Find the shortest path between two cities along he road segments
     *        previously added.
     * 
     * @param startingCity city from which a trip is to start
     * @param endingCity city at which a trip is supposed to end.
     * @return std::vector<Leg> list of legs making up the shortest possible
     *                          trip. Note that if road R connects city A to
     *                          city B and city B to city C, if that road is
     *                          used to travel from A to C, this is considered
     *                          a single leg in the plan, not two separate legs.
     */
    std::vector<Leg> travelPlan(std::string startingCity, 
                                std::string endingCity);

    /**
     * @brief Get the length of the trip returned by the last call to
     *        travelPlan.
     * 
     * @return double length of the last generated trip
     */
    double getLastTripLength() const;
    
private:
    /**
     * @brief records information about all of the trip segments
     */
    Graph g;

    /**
     * @brief maps city names onto graph vertices.
     */
    std::map<std::string, Vertex> verticesByName;

    /**
     * @brief length of the last generated trip
     */
    double tripLength;
};

#endif
