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
	
	// get the top, bottom, right and leftmost nodes
	auto yMinMaxPair = std::minmax_element(
		nodes.begin(), 
		nodes.end(), 
		[](const Node& a, const Node& b) 
	{ 
		auto aPos = a.getPosition();
		auto bPos = b.getPosition();
		return aPos.second < bPos.second; 
	});
	auto xMinMaxPair = std::minmax_element(
		nodes.begin(),
		nodes.end(),
		[](const Node& a, const Node& b)
	{
		auto aPos = a.getPosition();
		auto bPos = b.getPosition();
		return aPos.first < bPos.first;
	});

	auto xMin = xMinMaxPair.first->getPosition().first;
	auto xMax = xMinMaxPair.second->getPosition().first;
	auto yMin = yMinMaxPair.first->getPosition().second;
	auto yMax = yMinMaxPair.second->getPosition().second;
	auto xAxisScale = (widget_geometry.width() - 2 * constants::diameter) / (xMax - xMin);
	auto yAxisScale = (widget_geometry.height() - 3 * constants::diameter) / (yMax - yMin);
	std::for_each(
		nodes.begin(),
		nodes.end(),		
		[&](Node& n)
	{
		auto nodePos = n.getPosition();		
		nodePos.first = (nodePos.first - xMin) * xAxisScale;		
		nodePos.second = ((nodePos.second + yMax) * yAxisScale) + 3 * constants::radius;
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
		painter.drawText(startPos.first, startPos.second - constants::radius,
			QString::fromStdString(std::to_string(e.start())));
		painter.drawText(endPos.first, endPos.second - constants::radius,
			QString::fromStdString(std::to_string(e.end())));
	});
	
	painter.restore();
	_graph.calcForces();	
}
