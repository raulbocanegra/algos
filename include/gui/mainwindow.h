#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// ---------------------------------------------------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}

namespace introduction { namespace algorithms { namespace graphs
{
    class Edge;
}}}

// ---------------------------------------------------------------------------------------------------------------------
// Class MainWindow
// ---------------------------------------------------------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setData(const std::vector<introduction::algorithms::graphs::Edge> &edges);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
