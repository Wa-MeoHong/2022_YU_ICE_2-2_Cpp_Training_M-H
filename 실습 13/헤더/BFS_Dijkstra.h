#ifndef BFS_DIJKSTRA_H
#define BFS_DIJKSTRA_H

#include "Graph.h"
#include <fstream>

using namespace std;

typedef Graph::Vertex Vertex;					// Ŭ���� Vertex (Node)
typedef Graph::Edge Edge;						// Ŭ���� Edge (����)
typedef std::list<Graph::Vertex> VrtxList;		// Vertex List
typedef std::list<Graph::Edge> EdgeList;		// Edge List (�̾��� ��带 ǥ��)
typedef std::list<Graph::Vertex>::iterator VrtxItor;		// iterator 1
typedef std::list<Graph::Edge>::iterator EdgeItor;			// iterator 2

typedef enum BFS_PROCESS_STATTUS { NOT_SELECTED, SELECTED} BFSstat;

class BreadthFirstSearch
{
protected:
	Graph& graph;
	bool done;				// flag of search done ( �̹� �湮�� ������� Ȯ��)
protected:
	void initialize();
	bool isValidvID(int vid) { return graph.isValidvID(vid); }
	int NumVertices() { return graph.NumVertices(); }
	void _bfsTraversal(ostream& ostr, Vertex& s, Vertex& target, VrtxList& path);
	void visit(Vertex& v);
	bool isVisited(Vertex& v);
public:
	// constructor 
	BreadthFirstSearch(Graph& g) : graph(g), done(false)
	{
		g.initDistMtrx();
	}

	// getter 
	Graph& getGraph() { return graph; }
	double** DistMtrx() { return graph.DistMtrx(); }
	// member function 
	void bfsShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path);
	void DijkstraShortestPath(ostream& ostr, Vertex& start, Vertex& target, VrtxList& path);


};
#endif // !BPS_DIJKSTRA_H
