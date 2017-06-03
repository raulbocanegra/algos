#ifndef _ALGORITHMS_GRAPH_HEADER_
#define _ALGORITHMS_GRAPH_HEADER_

#include "algorithms/algorithms_global.h"
#include <vector>

namespace algorithms { namespace graphs
{    
	using NodeCoord = std::pair<double, double>;
	// -----------------------------------------------------------------------------------------------------------------
    // Class Node
    // -----------------------------------------------------------------------------------------------------------------
    class ALGORITHMS_LIB Node
    {	
	public:
		Node() = default;
        Node(const Node& other) = default;
        explicit Node(double x_pos, double y_pos);

        void print(std::ostream& out) const;

		NodeCoord getPosition() const;
		
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

		std::size_t getStart() const;
		std::size_t getEnd() const;

        void print(std::ostream& out) const;
	
	private:
		std::size_t _start;
		std::size_t _end;
    };

    // operator << for Edge to be with ADL
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

        explicit Graph(const std::vector<Edge>& edges);

        void setEdges(const std::vector<Edge>& edges);

    private:

        std::vector<Node> _nodes;
        std::vector<Edge> _edges;
    };
}} // namespace instroduction::algorithms::graphs
#endif
