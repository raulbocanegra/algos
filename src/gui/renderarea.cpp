#include "gui/renderarea.h"
#include "ui_renderarea.h"
#include <QPainter>

using namespace algorithms::graphs;

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea)
{
    ui->setupUi(this);
}

RenderArea::~RenderArea()
{
    delete ui;
}

void RenderArea::setEdges(const std::vector<Edge>& edges)
{
    _graph.setEdges(edges);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::SolidPattern);
    painter.save();
    painter.drawLine(this->geometry().bottomLeft(), this->geometry().topRight());
    painter.restore();
}
