/* DepthFirstSearch.cpp */
#include <list>
#include <algorithm>
#include "Graph.h"
#include "DepthFirstSearch.h"

using namespace std;

// consructor 
DepthFirstSearch::DepthFirstSearch(Graph& g) : graph(g)
{
	int num_nodes = g.NumVertices();

	// Vertex�� ���� �迭
	pVrtxStatus = new VrtxStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;

	// EdgeStatus ������ �迭 �Ҵ� ( �� ��帶�� ������ ������ �迭)
	ppEdgeStatus = new EdgeStatus * [num_nodes];
	for (int i = 0; i < num_nodes; i++)
		ppEdgeStatus[i] = new EdgeStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;
}


// member function
void DepthFirstSearch::initialize()
{
	int num_nodes = graph.NumVertices();

	VrtxList verts;
	graph.vertices(verts);		// vertex�� ����Ʈ�� �޾ƿ� (vertex�� ������)
	Vertex vrtx_1, vrtx_2;

	done = false;				// �ʱ� DFS�� ���´� Done ���� �ʾ���

	// �ʱ�ȭ
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;
}

void DepthFirstSearch::_dfsTravelsal(Vertex& v, Vertex& target, VrtxList& path)
{
	// base vertex�� visited�� ǥ��
	visit(v);
	if (v == target)		// if v == target, reculsive function escape
	{
		done = true;
		return;
	}

	EdgeList incidentEdges;			// v�� ������ ������ ����Ʈ
	incidentEdges.clear();
	graph.incidentEdges(v, incidentEdges);	// v�� ������ ������ ����Ʈ���� ������

	EdgeItor pe = incidentEdges.begin();
	while (!isDone() && pe != incidentEdges.end())
	{
		Edge e = *pe++;			// pe�� ����Ű�� Edge�� ������ ��, pe ����
		EdgeStatus eStat = EdgeStat(e);
		if (eStat == EDGE_UN_VISITED)	// ���� ������ ������ ���°� �湮�� ���� ���� �����̶��
		{
			visit(e);				// ������ �����ٰ� ǥ��
			Vertex w = e.opposite(v);		// �� ������ ���� �����ԵǴ� �ݴ� ���
			if (!isVisited(w))
			{
				path.push_back(w);		// �� �߰��� �ݴ��带 path(���)�� push
				SetEdgeStat(e, DISCOVERY);		// e�� DISCOVERY(�߰��� ����)�� ǥ��
				if (!isDone())
				{
					_dfsTravelsal(w, target, path);		// w��忡 ���� target������θ� ã�� dfs�� �����
					// ��Ͱ� ���������� �������� �������� ���ߴٸ�
					if (!isDone()) {
						// ���� �������� ���� ���(���)�� pop�Ѵ�
						Vertex Last_pushed = path.back();
						path.pop_back();		// ����
					}
				} // end if !isDone()
			} // end if !isVisited(w)
			else
			{
				SetEdgeStat(e, BACK);
			}
		} // end if (eStat == UNVISITED)
	}// end while 
}

void DepthFirstSearch::findPath(Vertex& s, Vertex& t, VrtxList& path)
{
	initialize();	// �ʱ� �̴ϼȶ�����
	path.clear();	// path�� �����

	path.push_back(s);		// ó�� ���۳�带 push
	_dfsTravelsal(s, t, path);	// DFS ����
}

// utilities
void DepthFirstSearch::visit(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))		// ���� vID�� ��ȿ�ϴٸ�
		pVrtxStatus[vID] = VISITED;		// �� Vertex�� �湮�� ���¶�� ǥ��
}
void DepthFirstSearch::visit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	
	// �������� �̾��� �� ��带 �޾ƿ� id�� ������
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// ���� �� ��尡 ��� ��ȿ�ϴٸ� �� ������ �湮���·� ǥ��
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = EDGE_VISITED;
}
void DepthFirstSearch::unvisit(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))		// ���� vID�� ��ȿ�ϴٸ�
		pVrtxStatus[vID] = UN_VISITED;		// �� Vertex�� �湮���� ���� ���¶�� ǥ��
}
void DepthFirstSearch::unvisit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();

	// �������� �̾��� �� ��带 �޾ƿ� id�� ������
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// ���� �� ��尡 ��� ��ȿ�ϴٸ� �� ������ �湮���·� ǥ��
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = EDGE_UN_VISITED;
}
bool DepthFirstSearch::isVisited(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))				// ���� vID�� ��ȿ�ϴٸ�
		return (pVrtxStatus[vID] == VISITED);	// �� Vertex�� �湮�� ���¶�� ��ȯ
	return false;
}
bool DepthFirstSearch::isVisited(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	EdgeStatus eStat;

	// �������� �̾��� �� ��带 �޾ƿ� id�� ������
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// ���� �� ��尡 ��� ��ȿ�ϴٸ� ������ �湮�ߴ���(�߰��ߴ���/ �ڷΰ�����)���θ� Ȯ��
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		if ((eStat == EDGE_VISITED) || (eStat == DISCOVERY) || (eStat == BACK))
			return true;
		else
			return false;
	}
	return false;
}

void DepthFirstSearch::SetEdgeStat(Edge& e, EdgeStatus es)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();

	// �������� �̾��� �� ��带 �޾ƿ� id�� ������
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// ���� �� ��尡 ��� ��ȿ�ϴٸ� ������ ���¸� es�� ����
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = es;
}
EdgeStatus DepthFirstSearch::EdgeStat(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	EdgeStatus eStat;

	// �������� �̾��� �� ��带 �޾ƿ� id�� ������
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// ���� �� ��尡 ��� ��ȿ�ϴٸ� ������ ������¸� ��ȯ
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		return eStat;
	}
	else
	{
		cout << "Edge (" << e << ") was noy found from AdjacencyList" << endl;
		return EDGE_NOT_FOUND;
	}
}
