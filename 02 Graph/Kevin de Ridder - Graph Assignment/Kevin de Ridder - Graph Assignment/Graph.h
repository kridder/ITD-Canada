#pragma once

class GraphNode;
class GraphArc;

#include <deque>
using std::deque;

class Graph
{
public:
	Graph();
	~Graph();
	const deque<GraphNode *> & getNodes();
	void addNode(GraphNode & node, size_t index = -1);
	void removeNode(size_t index);
	int getCount();
	void addArc(size_t fromIndex, size_t toIndex, int weight, bool twoWayArc = false);
	void removeArc(size_t fromIndex, size_t toIndex, bool twoWayArc = false);
	GraphArc * getArc(size_t fromIndex, size_t toIndex);
	void depthTraverse(GraphNode & node);
	void depthTraverseRecursive(GraphNode & node);
	void levelTraverse(GraphNode & node);
	void unmarkAllNodes();
private:
	deque<GraphNode *> m_nodes;
	int m_count;
};