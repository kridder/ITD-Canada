#include "GraphNode.h"
#include "GraphArc.h"

GraphNode::GraphNode()
{
	m_data = "";
	m_marked = false;
} // end default constructor;

GraphNode::GraphNode(string data)
{
	m_data = data;
	m_marked = false;
} // end default constructor;

GraphNode::~GraphNode()
{

	// delete all newed arcs
	for each(GraphArc * arc in m_arcList)
	{
		delete arc;
	}
} // end destructor

void GraphNode::setData(string data)
{
	m_data = data;
} // end function 

string GraphNode::getData()
{
	return m_data;
} // end function 

void GraphNode::setMarked(bool marked)
{
	m_marked = marked;
} // end function 

bool GraphNode::getMarked()
{
	return m_marked;
} // end function 

void GraphNode::addArc(GraphNode * node, int weight)
{
	m_arcList.push_back(new GraphArc(weight, node));
} // end function 

const list<GraphArc *> & GraphNode::getArcs()
{
	return m_arcList;
}

GraphNode * GraphNode::getNode(GraphNode * node)
{
	// if there is an arc pointing to this node
	for each(GraphArc * arc in m_arcList)
	{
		if (arc->getNode() == node)
		{
			return arc->getNode();
		}
	}

	// if no arc pointing to the node was found return a null pointer
	return 0;
} // end function getNode

GraphArc * GraphNode::getArc(GraphNode * toNode)
{
	// if there is an arc pointing to this node
	for each(GraphArc * arc in m_arcList)
	{
		if (arc->getNode() == toNode)
		{
			return arc;
		}
	}

	// if no arc pointing to the node was found return a null pointer
	return 0;
}

void GraphNode::removeArc(GraphNode * toNode)
{

	for (list<GraphArc *>::iterator arc = m_arcList.begin(); arc != m_arcList.end();)
	{
		if ((*arc)->getNode() == toNode)
		{
			delete *arc;
			m_arcList.remove(*arc++);
		}
		else
		{
			++arc;
		}
	}
} // end function removeArc