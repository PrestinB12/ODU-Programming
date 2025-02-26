#include "graph.h"
#include "graphUtils.h"
#include <algorithm>
#include <list>
#include <queue>
#include <vector>

using namespace std;
using namespace boost;


vector<Vertex> topologicalSort (const Graph& g)
{
	// Step 1: get the indegrees of all vertices. Place vertices with
	// indegree 0 into a queue.
	unsigned nVertices = std::distance(vertices(g).first, vertices(g).second);
	vector<int> inDegree(nVertices);
	vector<Vertex> sorted;

	queue<Vertex, list<Vertex> > q;
	auto allVertices = vertices(g);
	for (auto v = allVertices.first; v != allVertices.second; ++v)
	{
		inDegree[*v] = in_degree(*v, g);
		if (inDegree[*v] == 0)
			q.push(*v);
	}

	// Step 2. Take vertices from the q, one at a time, and add to sorted.
	// As we do, pretend that we have deleted these vertices from the graph,
	// decreasing the indegree of all adjacent nodes. If any nodes attain an
	// indegree of 0 because of this, add them to the queue.
	while (!q.empty())
	{
		Vertex v = q.front();
		q.pop();

		sorted.push_back(v);

		auto outEdges = out_edges(v,g);
		for (auto e = outEdges.first; e != outEdges.second; ++e)
		{
			Vertex adjacent = target(*e, g);
			inDegree[adjacent] = inDegree[adjacent] - 1;
			if (inDegree[adjacent] == 0)
				q.push (adjacent);
		}
	}

	// Step 3:  Did we finish the entire graph?
	if (sorted.size() != nVertices)
	{
		sorted.clear();
	}
	return sorted;
}

vector<Vertex> findShortestPath (
		const Graph& g,
		Vertex start,
		Vertex finish)
{
	unsigned nVertices = std::distance(vertices(g).first, vertices(g).second);
	vector<Vertex> cameFrom (nVertices);
	vector<Vertex> path;

	vector<unsigned> dist (nVertices, nVertices);
	dist[start] = 0;

	queue<Vertex, list<Vertex> > q;
	q.push (start);

	// From each vertex in queue, update distances of adjacent vertices
	while (!q.empty() && (dist[finish] == nVertices))
	{
		Vertex v = q.front();
		unsigned d = dist[v];
		q.pop();
		auto outGoing = out_edges(v, g);
		for (auto e = outGoing.first; e != outGoing.second; ++e)
		{
			Vertex w = target(*e, g);
			if (dist[w] > d + 1)
			{
				dist[w] = d + 1;
				q.push (w);
				cameFrom[w] = v;
			}
		}
	}
	// Extract path
	if (dist[finish] != nVertices)
	{
		Vertex v = finish;
		while (!(v == start))
		{
			path.push_back(v);
			v = cameFrom[v];
		}
		path.push_back(start);
	}
	reverse (path.begin(), path.end());

	return path;
}
