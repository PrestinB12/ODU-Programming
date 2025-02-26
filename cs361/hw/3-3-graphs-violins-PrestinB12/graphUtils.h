#ifndef GRAPHUTILS
#define GRAPHUTILS


#include "graph.h"
#include <algorithm>
#include <array>
#include <queue>
#include <vector>
#include <unordered_map>


/**
 * A topological sort of a directed graph is any listing of the vertices
 * in g such that v1 precedes v2 in the listing only if there exists no
 * path from v2 to v1.
 *
 * @param g the graph to be sorted
 * @return the ordered list of vertices if a sort is possible, or an
 *         empty list if no sort is possible (because the graph contains
 *         a cycle).
 */
std::vector<Vertex> topologicalSort (const Graph& g);

/**
 * Find the shortest path through g from start to finish.
 *
 * @param g the graph
 * @param start the vertex from which we start our path
 * @param finish the ending vertex for our path
 * @return path the output list of vertices, in the order defining the path
 *        from start to finish. This is empty if no such path exists.
 */
std::vector<Vertex> findShortestPath (
   const Graph& g,
   Vertex start,
   Vertex finish);

/**
 * Find a path through graph g from start to finish that has the smallest
 * possible sum of edge weight.
 *
 * @param g the graph
 * @param start the beginning of the path
 * @param finish the end of the path
 * @param weight a map associating an integer weight with each edge in g
 * @return the minimum-total-cost path from start to finish, or an empty
 *         vector if no path from start to finish exists.
 */
template <typename Graph, typename WeightMap>
std::vector<Vertex> findWeightedShortestPath (
		const Graph& g,
		Vertex start,
		Vertex finish,
		const WeightMap& weight)
{
	// Initialize the distance map and the priority queue
	unsigned nVertices = std::distance(vertices(g).first, vertices(g).second);

	std::vector<Vertex> cameFrom (nVertices);

	std::vector<unsigned> dist(nVertices, INT_MAX);
	dist[(int)start] = 0;

	typedef std::pair<int, Vertex> Element;
	std::priority_queue<Element, std::vector<Element>, std::greater<Element> >
	pq;
	pq.push (Element(0, start));

	// Find the shortest path
	while (!pq.empty())
	{
		Element top = pq.top();
		pq.pop();
		Vertex v = top.second;
		if (v == finish) break; // exit when we reach the finish vertex
		int d = dist[v];
		if (top.first == d)
		{
			auto outgoing = out_edges(v, g);
			for (auto e = outgoing.first; e != outgoing.second; ++e)
			{
				Vertex w = target(*e, g);
				unsigned wDist = d + weight.at(*e);
				if (dist[w] > wDist)
				{
				   dist[w] = wDist;
				   pq.push(Element(wDist, w));
				   cameFrom[w] = v;
				}
			}
		}
	}

	// Extract path
	std::vector<Vertex> path;
	Vertex v = finish;
	if (dist[v] != INT_MAX)
	{
		while (!(v == start))
		{
			path.push_back(v);
			v = cameFrom[v];
		}
		path.push_back(start);
	}
	std::reverse(path.begin(), path.end());
	return path;
}



/**
 * Find a minimum spanning tree within g rooted at start.
 *
 * @param g the graph
 * @param weight a map associating an integer weight with each edge in g
 * @return a set of edges comprising a minimum spanning tree.
 */
template <typename Graph, typename WeightMap>
std::unordered_set<Edge, boost::hash<Edge>> findMinSpanTree (
   const Graph& g,
   const WeightMap& weight)
{      // Prim's Algorithm
	// Initialize the distance map and the priority queue
	auto allVertices = vertices(g);
	unsigned nVertices = std::distance(allVertices.first, vertices(g).second);

	std::vector<Edge> cameFrom(nVertices);
    std::vector<unsigned> dist(nVertices, INT_MAX);
	dist[*(allVertices.first)] = 0;

	typedef std::pair<int, Vertex> Element;
	std::priority_queue<Element, std::vector<Element>, std::greater<Element> >
	pq;
	pq.push (Element(0, *(allVertices.first)));

	// Find the shortest path
	while (!pq.empty())
	{
		Element top = pq.top();
		pq.pop();
		Vertex v = top.second;
		int d = dist[v];
		if (top.first == d)
		{
			auto outgoing = out_edges(v, g);
			for (auto e = outgoing.first; e != outgoing.second; ++e)
			{
				Vertex w = target(*e, g);
				if (dist[w] > weight.at(*e))
				{
					unsigned newDist = weight.at(*e);
					dist[w] = newDist;
					pq.push(Element(newDist, w));
					cameFrom[w] = *e;
				}
			}
		}
	}

	// Extract spanning tree
	std::unordered_set<Edge, boost::hash<Edge>> spanTree;
	auto vi = allVertices.first;
	++vi;
	for (; vi != allVertices.second; ++vi)
	{
		spanTree.insert(cameFrom[*vi]);
	}
	return spanTree;
}

#endif
