#ifndef _ALGORITHMS_GRAPH_HEADER_
#define _ALGORITHMS_GRAPH_HEADER_

#include "algorithms/algorithms_global.h"
#include <vector>

namespace introduction { namespace algorithms { namespace graphs
{
    struct ALGORITHMS_LIB_EXPORT Node
    {
        double x;
        double y;
    };

    struct ALGORITHMS_LIB_EXPORT Edge
    {
        std::size_t start;
        std::size_t end;
    };

    class ALGORITHMS_LIB_EXPORT Graph
    {
    public:
        Graph() = default;
        Graph(const Graph& other) = default;
        ~Graph() = default;

        explicit Graph(const std::vector<Node>& nodes, const std::vector<Edge>& edges);

        void setEdges(const std::vector<Edge>& edges);

    private:

        std::vector<Node> _nodes;
        std::vector<Edge> _edges;
    };
}}} // namespace instroduction::algorithms::graphs
#endif
