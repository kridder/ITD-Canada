#pragma once

class GraphNode;

class GraphArc
{
public:
	// member functions
	GraphArc();
	GraphArc(int weight, GraphNode * node = 0);
	~GraphArc();
	void setNode(GraphNode & node);
	GraphNode * getNode();
	void setArcWeight(int weight);
	int getArcWeight();

private:
	// data members
	GraphNode * m_node;
	int arcWeight;
};