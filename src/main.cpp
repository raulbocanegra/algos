#include "gui/mainwindow.h"
#include <QApplication>
#include "algorithms/graph.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace algorithms;

graphs::Graph readGraph(const std::string& filename)
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
	
    return graphs::Graph(num_nodes, edges);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto graph = readGraph("C:\\Users\\Raul\\OneDrive\\Programming\\C++\\algos\\res\\10grid");
    MainWindow w;	
    w.setData(graph);
    w.show();

    return a.exec();
}
