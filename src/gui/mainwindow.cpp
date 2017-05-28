#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithms/graph.h"

using namespace introduction::algorithms::graphs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(const std::vector<Edge>& edges)
{
    ui->renderArea->setEdges(edges);
}
