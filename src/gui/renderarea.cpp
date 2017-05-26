#include "renderarea.h"
#include "ui_renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea),
    _pen(),
    _brush()
{
    ui->setupUi(this);
}

RenderArea::~RenderArea()
{
    delete ui;
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
