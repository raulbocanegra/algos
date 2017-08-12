#ifndef _ALGORITHMS_GRAPH_HEADER_
#define _ALGORITHMS_GRAPH_HEADER_

#include "algorithms/algorithms_global.h"
#include <vector>

namespace algorithms { namespace graphs
{    
	using NodeCoord = std::pair<double, double>;
	using NodeForce = std::pair<double, double>;
	
	NodeForce operator - (const NodeForce& left, const NodeForce& right);
	NodeForce operator + (const NodeForce& left, const NodeForce& right);
    NodeForce& operator +=(NodeForce& left, const NodeForce& right);
	NodeForce& operator -=(NodeForce& left, const NodeForce& right);

	// -----------------------------------------------------------------------------------------------------------------
    // Class Node
    // -----------------------------------------------------------------------------------------------------------------
    class ALGORITHMS_LIB Node
    {	
	public:
		Node() = default;
        Node(const Node& other) = default;
		explicit Node(double x_pos, double y_pos);
	    explicit Node(const NodeCoord& coord);

        void print(std::ostream& out) const;

		NodeCoord getPosition() const;
		void setPosition(const NodeCoord& coord);
		
		// this method moves the node adding the force applied to it.
		void move(const NodeForce& force);
		
	private:
		double _x;
		double _y;
    };

    // operator << for Node to be with ADL
    std::ostream& operator << (std::ostream& out, const Node& node);

    // -----------------------------------------------------------------------------------------------------------------
    // Class Edge
    // -----------------------------------------------------------------------------------------------------------------
    class ALGORITHMS_LIB Edge
    {
	public:	
        Edge() = default;
        Edge(const Edge& other) = default;
        explicit Edge(std::size_t start, std::size_t end);

		std::size_t start() const;
		std::size_t end() const;

        void print(std::ostream& out) const;
	
	private:
		std::size_t _start;
		std::size_t _end;
    };

    // operator << for Edge to be used with ADL
    std::ostream& operator << (std::ostream& out, const Edge& edge);

    // -----------------------------------------------------------------------------------------------------------------
    // Class Graph
    // -----------------------------------------------------------------------------------------------------------------
    class ALGORITHMS_LIB Graph
    {
    public:
        Graph() = default;
        Graph(const Graph& other) = default;
		~Graph() = default;

        explicit Graph(std::size_t num_nodes, const std::vector<Edge>& edges);
		void swap(Graph& other);
		Graph& operator = (Graph other);

		std::vector<Node> nodes() const;
		std::vector<Edge> edges() const;
		
		void calcForces();

    private:

		void _initPositionNodes();

        std::vector<Node> _nodes;
        std::vector<Edge> _edges;
    };

	void swap(Graph& lhs, Graph& rhs);
}} // namespace instroduction::algorithms::graphs
#endif
