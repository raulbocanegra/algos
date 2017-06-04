#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

using namespace algorithms::graphs;

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

void MainWindow::setData(const Graph& graph)
{
    ui->renderArea->setData(graph);
}
