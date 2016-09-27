#pragma once

#include <string>
using std::string;

#include <list>
using std::list;

class GraphArc;

class GraphNode
{
public:
	// member functions
	GraphNode();
	GraphNode(string data);
	~GraphNode();
	void setData(string data);
	string getData();
	void setMarked(bool marked);
	bool getMarked();
	void addArc(GraphNode * node, int weight);
	const list<GraphArc *> & getArcs();
	GraphNode * getNode(GraphNode * node);
	GraphArc * getArc(GraphNode * toNode);
	void removeArc(GraphNode * toNode);

private:
	// data members
	string m_data;
	bool m_marked;
	list<GraphArc *> m_arcList;
};