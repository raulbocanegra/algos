#include "gui/mainwindow.h"
#include <QApplication>
#include "algorithms/graph.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace introduction::algorithms;

std::vector<graphs::Edge> readFile(const std::string filename)
{
    std::ifstream file(filename);
    unsigned num_nodes = 0;
    file >> num_nodes;

    // read edges
    std::vector<graphs::Edge> edges;
    edges.reserve(num_nodes);
    std::string line;
    for (int edges_read = 0; edges_read < num_nodes; ++edges_read)
    {
        std::getline(file, line);
        unsigned start = 0;
        unsigned end = 0;
        file >> start >> end;
        edges.emplace_back(graphs::Edge{start, end});
        std::cout << start << " " << end << " ";
        line.clear();
    }
    return edges;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto edges = readFile("C:\\Users\\Raul\\OneDrive\\Programming\\C++\\CS106L\\1.- GraphViz\\01_GraphViz\\res\\2line");
    MainWindow w;
    w.setData(edges);
    w.show();

    return a.exec();
}
