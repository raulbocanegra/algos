#include "algorithms/graph.h"

using namespace introduction::algorithms::graphs;

Graph::Graph(const std::vector<Node> &nodes, const std::vector<Edge> &edges)
    : _nodes(nodes)
    , _edges(edges)
{}

void Graph::setEdges(const std::vector<Edge>& edges)
{
    _edges = edges;
}
