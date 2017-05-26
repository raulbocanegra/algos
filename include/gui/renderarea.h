#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QBrush>
#include <QPen>

namespace Ui {
class RenderArea;
}

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = 0);
    ~RenderArea();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::RenderArea *ui;
    QPen _pen;
    QBrush _brush;
};

#endif // RENDERAREA_H
