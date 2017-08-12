#include "algorithms/graph.h"
#include "common/common.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace algorithms;
using namespace algorithms::graphs;

namespace
{
	double attractForce(const NodeCoord& c0, const NodeCoord& c1)
	{		
		return constants::attract * (pow((c1.first - c0.first), 2) + pow((c1.second - c0.second), 2));
	}
		
	double repelForce(const NodeCoord& c0, const NodeCoord& c1)
	{
		return constants::repel / sqrt(pow((c1.first - c0.first), 2) + pow((c1.second - c0.second), 2));
	}
}

NodeForce algorithms::graphs::operator-(const NodeForce & left, const NodeForce & right)
{
	return NodeForce{ left.first - right.first, left.second - right.second };
}

NodeForce algorithms::graphs::operator+(const NodeForce & left, const NodeForce & right)
{
	return NodeForce{ left.first + right.first, left.second + right.second };
}

NodeForce& algorithms::graphs::operator+=(NodeForce & left, const NodeForce & right)
{
	left = left + right;
	return left;
}

NodeForce& algorithms::graphs::operator-=(NodeForce & left, const NodeForce & right)
{
	left = left - right;
	return left;
}

// ---------------------------------------------------------------------------------------------------------------------
// Class Node
// ---------------------------------------------------------------------------------------------------------------------
Node::Node(double x_pos, double y_pos)
    : _x(x_pos)
    , _y(y_pos)
{}

Node::Node(const NodeCoord & coord)
	: _x(coord.first)
	, _y(coord.second)
{}

void Node::print(std::ostream &out) const
{
    out << "N(" << _x << ", " << _y << ")" << std::endl;
}

NodeCoord algorithms::graphs::Node::getPosition() const
{
	return {_x, _y};
}

void algorithms::graphs::Node::setPosition(const NodeCoord & coord)
{
	_x = coord.first;
	_y = coord.second;
}

void algorithms::graphs::Node::move(const NodeForce & force)
{
	_x += force.first;
	_y += force.second;
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

std::size_t algorithms::graphs::Edge::start() const
{
	return _start;
}

std::size_t algorithms::graphs::Edge::end() const
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
Graph::Graph(std::size_t num_nodes, const std::vector<Edge> &edges)
    : _nodes(num_nodes)
	, _edges(edges)
{
	_initPositionNodes();
}

void Graph::swap(Graph & other)
{
	using std::swap;
	swap(_nodes, other._nodes);
	swap(_edges, other._edges);	
}

Graph & algorithms::graphs::Graph::operator=(Graph other)
{
	other.swap(*this);
	return(*this);
}

void algorithms::graphs::swap(Graph & lhs, Graph & rhs)
{
	lhs.swap(rhs);
}

std::vector<Node> algorithms::graphs::Graph::nodes() const
{
	return _nodes;
}

std::vector<Edge> algorithms::graphs::Graph::edges() const
{
	return _edges;
}

void Graph::_initPositionNodes()
{
	// let's put the nodes in a circle.
	auto num_nodes = _nodes.size();
	for (size_t i = 0; i < num_nodes; ++i)
	{
		auto x_pos = cos(2 * constants::pi * i / num_nodes);
		auto y_pos = sin(2 * constants::pi * i / num_nodes);
		_nodes[i].setPosition({ x_pos, y_pos });
	}
}

void algorithms::graphs::Graph::calcForces()
{	
	std::vector<NodeForce> cachedForce(_nodes.size());
	bool stopIterating = false;
	while (!stopIterating)
	{
		std::vector<NodeForce> forces(_nodes.size());
		// Calculate repel forces	
		for (size_t i = 0; i < _nodes.size() - 1; ++i)
		{
			for (size_t j = i + 1; j < _nodes.size(); ++j)
			{
				auto iPos = _nodes[i].getPosition();
				auto jPos = _nodes[j].getPosition();
				auto theta = atan2(jPos.second - iPos.second, jPos.first - iPos.first);
				auto rForce = repelForce(iPos, jPos);
				forces[i].first -= (rForce * cos(theta));
				forces[i].second -= (rForce * sin(theta));
				forces[j].first += (rForce * cos(theta));
				forces[j].second += (rForce * sin(theta));
			}
		}

		// Calculate attractive forces
		for (size_t i = 0; i < _edges.size(); ++i)
		{
			auto node0Pos = _nodes[_edges[i].start()].getPosition();
			auto node1Pos = _nodes[_edges[i].end()].getPosition();
			auto aForce = attractForce(node0Pos, node1Pos);
			auto theta = atan2(node1Pos.second - node0Pos.second, node1Pos.first - node0Pos.first);
			forces[_edges[i].start()] += { (aForce * cos(theta)) , (aForce * sin(theta)) };
			forces[_edges[i].end()] -= { (aForce * cos(theta)), (aForce * sin(theta)) };
		}
		
		// Update positions
		std::transform(_nodes.begin(), _nodes.end(), forces.begin(), _nodes.begin(),
			[](Node& c1, const NodeForce& c2)
		{
			c1.move(c2);
			return c1;
		});
		
		// Calculate the net forces to test if we need to keep iterating.
		std::vector<NodeForce> diffForces(_nodes.size());
		std::transform(
			forces.begin(),
			forces.end(),
			cachedForce.begin(),
			diffForces.begin(),
			[](const NodeForce& c1, const NodeForce& c2)
		{
			return c1 - c2;
		});

		// check if nodes are stable.
		stopIterating = std::all_of(
			diffForces.begin(),
			diffForces.end(),
			[](const NodeForce& nf) 
		{
			return nf.first < constants::threshold && nf.second < constants::threshold;
		});

		cachedForce = forces;
	}
}