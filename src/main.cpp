#include "gui/mainwindow.h"
#include <QApplication>
#include "algorithms/graph.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace algorithms;

std::vector<graphs::Edge> readGraphFile(const std::string filename)
{
    std::ifstream file(filename);
    
	// read num nodes
	unsigned num_nodes = 0;
    file >> num_nodes;
    	
    std::vector<graphs::Edge> edges;
    edges.reserve(num_nodes);
    
	// read edges
	unsigned start = 0;
	unsigned end = 0;
    while(file >> start >> end)
    {   
		edges.emplace_back(start, end);        
    }
    return edges;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto edges = readGraphFile("C:\\Users\\Raul\\OneDrive\\Programming\\C++\\CS106L\\1.- GraphViz\\01_GraphViz\\res\\3grid");
    MainWindow w;	
    w.setData(edges);
    w.show();

    return a.exec();
}
