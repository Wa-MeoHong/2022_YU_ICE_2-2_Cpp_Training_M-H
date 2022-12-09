#ifndef DFS_H
#define DFS_H

#include <iostream>
#include "Graph.h"

using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;		// Vertex List
typedef std::list<Graph::Edge> EdgeList;		// Edge List (�̾��� ��带 ǥ��)
typedef std::list<Graph::Vertex>::iterator VrtxItor;		// iterator 1
typedef std::list<Graph::Edge>::iterator EdgeItor;			// iterator 2

class DepthFirstSearch
{
protected:
	Graph& graph;
	Vertex start;
	bool done;

protected:
	void initialize();
	void _dfsTravelsal(Vertex& v, Vertex& target, VrtxList& path);
	virtual void traverseDiscovery(const Edge& e, const Vertex& from) {}
	virtual void traverssBack(const Edge& e, const Vertex& from) {}
	virtual void finishVisit(const Vertex& v) {}
	virtual bool isDone() const { return done; }

	// make utility
	void visit(Vertex& v);			// visit overloading 1
	void visit(Edge& e);			// visit overloading 2
	void unvisit(Vertex& v);		// unvisit overloading 1
	void unvisit(Edge& e);			// unvisit overloading 2
	bool isVisited(Vertex& v);		// isVisited overloading 1
	bool isVisited(Edge& e);		// isVisited overloading 2
	
	// setter 
	void SetEdgeStat(Edge& e, EdgeStatus es);	

	// getter
	EdgeStatus EdgeStat(Edge& e);

public:
	// constructor
	DepthFirstSearch(Graph& g);
	
	// getter
	Graph& getGraph() { return graph; }
	
	// member function 
	void findPath(Vertex& s, Vertex& t, VrtxList& path);
	void showConnectivity();

private:
	VrtxStatus* pVrtxStatus;		// �������� ���� ������ �迭
	EdgeStatus** ppEdgeStatus;		// �������� ������¿� ���� ������ �迭
};


#endif // !DFS_H

