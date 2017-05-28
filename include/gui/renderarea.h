#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "gui/algorithms_gui_global.h"
#include <QWidget>
#include "algorithms/graph.h"

namespace Ui
{
    class RenderArea;
}

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = 0);
    ~RenderArea();

    void setEdges(const std::vector<introduction::algorithms::graphs::Edge>& edges);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::RenderArea *ui;
    introduction::algorithms::graphs::Graph _graph;

};

#endif // RENDERAREA_H
