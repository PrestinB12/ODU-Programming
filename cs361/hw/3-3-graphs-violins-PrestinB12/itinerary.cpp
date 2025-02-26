#include "itinerary.h"
#include "graph.h"
#include "graphUtils.h"
#include <boost/graph/adjacency_list.hpp>   //adding in boosts
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace boost;

Itinerary::Itinerary()
{
    //something, right? LOL
}

void Itinerary::addRoad(const Leg &roadSegment)
{

    Vertex vertexOne, vertexTwo;
    auto it = verticesByName.find(roadSegment.fromCity);
    if (it == verticesByName.end())
    {
        vertexOne = add_vertex({roadSegment.fromCity}, g);
        verticesByName[roadSegment.fromCity] = vertexOne;
    }
    else
    {
        vertexOne = it->second;
    }

    it = verticesByName.find(roadSegment.toCity);
    if (it == verticesByName.end())
    {
        vertexTwo = add_vertex({roadSegment.toCity}, g);
        verticesByName[roadSegment.toCity] = vertexTwo;
    }
    else
    {
        vertexTwo = it->second;
    }

    Edge edgeOne;
    bool insertedOne;
    boost::tie(edgeOne, insertedOne) = boost::add_edge(vertexOne, vertexTwo, g);
    if (insertedOne)
    {
        g[edgeOne].length = roadSegment.distance;
        g[edgeOne].roadName = roadSegment.road;
    }

    Edge edgeTwo;
    bool insertedTwo;
    boost::tie(edgeTwo, insertedTwo) = boost::add_edge(vertexTwo, vertexOne, g);
    if (insertedTwo)
    {
        g[edgeTwo].length = roadSegment.distance;
        g[edgeTwo].roadName = roadSegment.road;
    }
}

std::vector<Leg> Itinerary::travelPlan(std::string startingCity, std::string endingCity)
{
    std::vector<Leg> pathToCity;

    auto startIt = verticesByName.find(startingCity);
    auto endIt = verticesByName.find(endingCity);

    if (startIt == verticesByName.end() || endIt == verticesByName.end())
    {
        std::cerr << "One of the cities is not found in the map." << std::endl;
        return pathToCity; 
    }
    Vertex start = startIt->second;
    Vertex end = endIt->second;

    std::vector<Vertex> predecessors(num_vertices(g));
    std::vector<double> distances(num_vertices(g), std::numeric_limits<double>::max());
    boost::property_map<Graph, double EdgeData::*>::type weightmap = get(&EdgeData::length, g);
    boost::dijkstra_shortest_paths(g, start,
                                   boost::predecessor_map(&predecessors[0])
                                       .distance_map(&distances[0])
                                       .weight_map(weightmap));

    for (Vertex v = end; v != start; v = predecessors[v])
    {
        Vertex u = predecessors[v];
        Edge e;
        bool found;
        boost::tie(e, found) = edge(u, v, g);
        if (!found)
        {
            return std::vector<Leg>(); 
        }

        
        /*
        if(v == u)
        {
            continue;
        }
        */
        Leg leg;
        leg.fromCity = g[u].city;
        leg.toCity = g[v].city;
        leg.road = g[e].roadName;
        leg.distance = g[e].length;
        pathToCity.push_back(leg);

        /*
        if(leg.distance < 1)
        {
            std::cerr << "Found it";
        }
        */
    }
    std::reverse(pathToCity.begin(), pathToCity.end()); 
    tripLength = distances[end];
    std::vector<Leg> prunedPath;
    for (int i = 0; i < pathToCity.size(); ++i)
    {
        if (i == pathToCity.size()-1)
        {
            prunedPath.push_back(pathToCity[i]);
        }
        
        else if (pathToCity[i].road == pathToCity[i+1].road)
        {
            Leg combo;
            combo.fromCity = pathToCity[i].fromCity;
            combo.toCity = pathToCity[i+1].toCity;
            combo.road = pathToCity[i].road;
            combo.distance = pathToCity[i].distance + pathToCity[i+1].distance;
            ++i;
            prunedPath.push_back(combo);
        }
        else
        {
            prunedPath.push_back(pathToCity[i]);
        }
    }
    return prunedPath;
    //return pathToCity;
}

double Itinerary::getLastTripLength() const
{
    return tripLength;
}