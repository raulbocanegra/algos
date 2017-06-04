#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "gui/algorithms_gui_global.h"
#include <QWidget>
#include <QPainter>
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

    void setData(const algorithms::graphs::Graph& graph);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::RenderArea *ui;	
    algorithms::graphs::Graph _graph;

};

#endif // RENDERAREA_H
