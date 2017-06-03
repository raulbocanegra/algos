#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/algorithms_gui_global.h"
#include "algorithms/graph.h"
// ---------------------------------------------------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}

// ---------------------------------------------------------------------------------------------------------------------
// Class MainWindow
// ---------------------------------------------------------------------------------------------------------------------

class ALGORITHMS_GUI_LIB MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setData(const std::vector<algorithms::graphs::Edge> &edges);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
