#include "gui/renderarea.h"
#include "ui_renderarea.h"
#include "common/common.h"
#include <QPainter>

using namespace algorithms;
using namespace algorithms::graphs;

RenderArea::RenderArea(QWidget *parent) 
	: QWidget(parent)
	, ui(new Ui::RenderArea)	
	, _graph()

{
    ui->setupUi(this);
}

RenderArea::~RenderArea()
{
    delete ui;
}

void RenderArea::setData(const Graph& graph)
{
    _graph = graph;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);    
	painter.setPen(Qt::SolidLine);
    painter.setBrush(Qt::SolidPattern);
    painter.save();
    auto widget_geometry = this->geometry();
	auto nodes = _graph.nodes();
	
	std::for_each(
		nodes.begin(),
		nodes.end(),		
		[&widget_geometry, &painter](Node& n)
	{
		auto nodePos = n.getPosition();
		nodePos.first *= constants::scale;
		nodePos.first += widget_geometry.width() / 2;
		nodePos.second *= constants::scale;
		nodePos.second += widget_geometry.height() / 2;
		painter.drawEllipse(nodePos.first, nodePos.second, constants::diameter, constants::diameter);
		n.setPosition(nodePos);
	});	

	auto edges = _graph.edges();
    std::for_each(		
		edges.begin(),
		edges.end(),
		[&nodes, &painter](const Edge& e)
	{
		auto startPos = nodes[e.start()].getPosition();
		auto endPos = nodes[e.end()].getPosition();
		painter.drawLine(startPos.first + constants::radius, startPos.second + constants::radius, 
			             endPos.first + constants::radius, endPos.second + constants::radius);
	});
	
	painter.restore();
	for (size_t i = 0; i < 100; i++)
	{
		_graph.calcForces();
	}	
}
