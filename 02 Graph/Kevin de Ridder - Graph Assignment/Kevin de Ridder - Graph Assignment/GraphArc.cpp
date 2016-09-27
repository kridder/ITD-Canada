#include "GraphArc.h"

GraphArc::GraphArc()
{
	m_node = 0;
	arcWeight = 0;
} // end default constructor

GraphArc::GraphArc(int weight, GraphNode * node) // default GraphNode * node = 0
{
	m_node = node;
	arcWeight = weight;
} // end intializer constructor

GraphArc::~GraphArc()
{
	//void
} // end destructor

void GraphArc::setNode(GraphNode & node)
{
	m_node = &node;
} // end function setNode

GraphNode * GraphArc::getNode()
{
	return m_node;
} // end function getNode

void GraphArc::setArcWeight(int weight)
{
	arcWeight = weight;
} // end function setArcWeight

int GraphArc::getArcWeight()
{
	return arcWeight;
} // end function getArcWeight