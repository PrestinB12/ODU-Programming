#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

struct VertexData {
  std::string city;
};

struct EdgeData {
  std::string roadName;
  double length;
};

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS, VertexData, EdgeData> Graph;
typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;


#endif
