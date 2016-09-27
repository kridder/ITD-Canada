#include <iostream>
using std::cout;
using std::endl;

#include <queue>
using std::queue;

#include "Graph.h"
#include "GraphNode.h"
#include "GraphArc.h"

Graph::Graph()
{
	m_count = 0;
} // end default constructor

Graph::~Graph()
{
	for each(GraphNode * node in m_nodes)
	{
		delete node;
	}
} // end destructor

const deque<GraphNode *> & Graph::getNodes()
{
	return m_nodes;
}

void Graph::addNode(GraphNode & node, size_t index) // defualt size_t index = -1;
{
	// if no index is specified, add to the back of the deque
	if (index == -1)
	{
		m_nodes.push_back(&node);
		++m_count;
	}
	// otherwise insert at specified index
	else if (index >= 0 && index <= m_count)
	{
		m_nodes.insert(m_nodes.begin() + index, &node);
		++m_count;
	}
} // end function addNode

void Graph::removeNode(size_t index)
{
	// check if index is in range
	if (index < 0 || index >= m_count)
	{
		return;
	}

	// remove any arcs from any other nodes pointing to this node
	for each(GraphNode * node in m_nodes)
	{
		node->removeArc(m_nodes[index]); // this will check all arcs, but only remove those that point to the argument node
	} // end for each

	// delete node and remove from node deque
	delete m_nodes[index];
	m_nodes[index] = 0;
	m_nodes.erase(m_nodes.begin() + index);
	--m_count;
} // end function removeNode

int Graph::getCount()
{
	return m_count;
}

void Graph::addArc(size_t fromIndex, size_t toIndex, int weight, bool twoWayArc) // default bool twoWayArc = false
{
	// check if indices are in range
	if (fromIndex < 0 || fromIndex >= m_count || toIndex < 0 || toIndex >= m_count)
	{
		return;
	}

	// add arc(s)
	m_nodes[fromIndex]->addArc(m_nodes[toIndex], weight);
	if (twoWayArc)
	{
		m_nodes[toIndex]->addArc(m_nodes[fromIndex], weight);
	}
} // end function addArc

void Graph::removeArc(size_t fromIndex, size_t toIndex, bool twoWayArc) // default bool twoWayArc = false
{
	// check if indices are in range
	if (fromIndex < 0 || fromIndex >= m_count || toIndex < 0 || toIndex >= m_count)
	{
		return;
	}

	// remove arc(s)
	m_nodes[fromIndex]->removeArc(m_nodes[toIndex]);
	if (twoWayArc)
	{
		m_nodes[toIndex]->removeArc(m_nodes[fromIndex]);
	}
} // end function removeArc

GraphArc * Graph::getArc(size_t fromIndex, size_t toIndex)
{
	// check if indices are in range
	if (fromIndex < 0 || fromIndex >= m_count || toIndex < 0 || toIndex >= m_count)
	{
		return 0;
	}

	// return Arc
	return m_nodes[fromIndex]->getArc(m_nodes[toIndex]);
} // end function getArc

void Graph::depthTraverse(GraphNode & node)
{
	depthTraverseRecursive(node);

	// unmark all nodes for possible next traversal
	unmarkAllNodes();
} // end function depthTraverse

void Graph::depthTraverseRecursive(GraphNode & node)
{
	// print node data in pre-order
	cout << node.getData() << endl;
	node.setMarked(true);
	for each (GraphArc * arc in node.getArcs())
	{
		if (!arc->getNode()->getMarked())
		{
			// recursively call this function for child node
			depthTraverseRecursive(*arc->getNode());
		} // end for each
	}
} // end function depthTraverseRecursive

void Graph::levelTraverse(GraphNode & node)
{
	queue<GraphNode *> nodeQueue;
	nodeQueue.push(&node);
	node.setMarked(true);
	while (!nodeQueue.empty())
	{
		for each (GraphArc * arc in nodeQueue.front()->getArcs())
		{
			if (!arc->getNode()->getMarked())
			{
				nodeQueue.push(arc->getNode());
				arc->getNode()->setMarked(true);
			}
		} // end for each

		// print front of queue and pop it
		cout << nodeQueue.front()->getData() << endl;
		nodeQueue.pop();
	} // end while

	// unmark all nodes for possible next traversal
	unmarkAllNodes();
} // end function levelTraverse

void Graph::unmarkAllNodes()
{
	for each(GraphNode * node in m_nodes)
	{
		node->setMarked(false);
	}
} // end function unmarkAllNodes