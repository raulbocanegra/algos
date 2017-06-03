#include "algorithms/graph.h"
#include <iostream>

using namespace algorithms::graphs;

// ---------------------------------------------------------------------------------------------------------------------
// Class Node
// ---------------------------------------------------------------------------------------------------------------------
Node::Node(double x_pos, double y_pos)
    : _x(x_pos)
    , _y(y_pos)
{}

void Node::print(std::ostream &out) const
{
    out << "N(" << _x << ", " << _y << ")" << std::endl;
}

NodeCoord algorithms::graphs::Node::getPosition() const
{
	return {_x, _y};
}

std::ostream& algorithms::graphs::operator <<(std::ostream & out, const Node & node)
{
    node.print(out);
    return out;
}

// ---------------------------------------------------------------------------------------------------------------------
// Class Edge
// ---------------------------------------------------------------------------------------------------------------------
Edge::Edge(size_t start, size_t end)
    : _start(start)
    , _end(end)
{}

std::size_t algorithms::graphs::Edge::getStart() const
{
	return _start;
}

std::size_t algorithms::graphs::Edge::getEnd() const
{
	return _end;
}

void Edge::print(std::ostream& out) const
{
    out << "E(" << _start << ", " << _end << ")" << std::endl;
}

std::ostream& algorithms::graphs::operator <<(std::ostream & out, const Edge &edge)
{
    edge.print(out);
    return out;
}

// ---------------------------------------------------------------------------------------------------------------------
// Class Graph
// ---------------------------------------------------------------------------------------------------------------------
Graph::Graph(const std::vector<Edge> &edges)
    : _edges(edges)
{}

void Graph::setEdges(const std::vector<Edge>& edges)
{
    _edges = edges;
}
