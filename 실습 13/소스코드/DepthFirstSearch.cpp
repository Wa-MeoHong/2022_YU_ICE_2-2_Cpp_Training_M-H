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

	// Vertex의 상태 배열
	pVrtxStatus = new VrtxStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;

	// EdgeStatus 이차원 배열 할당 ( 각 노드마다 인접한 간선의 배열)
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
	graph.vertices(verts);		// vertex의 리스트를 받아옴 (vertex의 정보들)
	Vertex vrtx_1, vrtx_2;

	done = false;				// 초기 DFS의 상태는 Done 되지 않았음

	// 초기화
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;
}

void DepthFirstSearch::_dfsTravelsal(Vertex& v, Vertex& target, VrtxList& path)
{
	// base vertex를 visited로 표시
	visit(v);
	if (v == target)		// if v == target, reculsive function escape
	{
		done = true;
		return;
	}

	EdgeList incidentEdges;			// v에 인접한 간선의 리스트
	incidentEdges.clear();
	graph.incidentEdges(v, incidentEdges);	// v에 인접한 간선의 리스트들을 가져옴

	EdgeItor pe = incidentEdges.begin();
	while (!isDone() && pe != incidentEdges.end())
	{
		Edge e = *pe++;			// pe가 가리키는 Edge를 가져온 후, pe 증가
		EdgeStatus eStat = EdgeStat(e);
		if (eStat == EDGE_UN_VISITED)	// 만약 인접한 간선의 상태가 방문한 적이 없는 간선이라면
		{
			visit(e);				// 간선을 만났다고 표시
			Vertex w = e.opposite(v);		// 이 간선을 따라 만나게되는 반대 노드
			if (!isVisited(w))
			{
				path.push_back(w);		// 그 발견한 반대노드를 path(경로)에 push
				SetEdgeStat(e, DISCOVERY);		// e를 DISCOVERY(발견한 상태)로 표시
				if (!isDone())
				{
					_dfsTravelsal(w, target, path);		// w노드에 대해 target까지경로를 찾는 dfs를 재귀함
					// 재귀가 끝났음에도 목적지에 도달하지 못했다면
					if (!isDone()) {
						// 가장 마지막에 넣은 경로(노드)를 pop한다
						Vertex Last_pushed = path.back();
						path.pop_back();		// 꺼냄
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
	initialize();	// 초기 이니셜라이즈
	path.clear();	// path를 비워줌

	path.push_back(s);		// 처음 시작노드를 push
	_dfsTravelsal(s, t, path);	// DFS 시작
}

// utilities
void DepthFirstSearch::visit(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))		// 만약 vID가 유효하다면
		pVrtxStatus[vID] = VISITED;		// 이 Vertex는 방문한 상태라고 표시
}
void DepthFirstSearch::visit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	
	// 간선으로 이어진 두 노드를 받아와 id를 가져옴
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// 만약 두 노드가 모두 유효하다면 이 간선은 방문상태로 표시
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = EDGE_VISITED;
}
void DepthFirstSearch::unvisit(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))		// 만약 vID가 유효하다면
		pVrtxStatus[vID] = UN_VISITED;		// 이 Vertex는 방문하지 않은 상태라고 표시
}
void DepthFirstSearch::unvisit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();

	// 간선으로 이어진 두 노드를 받아와 id를 가져옴
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// 만약 두 노드가 모두 유효하다면 이 간선은 방문상태로 표시
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = EDGE_UN_VISITED;
}
bool DepthFirstSearch::isVisited(Vertex& v)
{
	Vertex* pVtx = NULL;
	int numNodes = graph.NumVertices();
	int vID = v.Id();

	if (getGraph().isValidvID(vID))				// 만약 vID가 유효하다면
		return (pVrtxStatus[vID] == VISITED);	// 이 Vertex는 방문한 상태라고 반환
	return false;
}
bool DepthFirstSearch::isVisited(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	EdgeStatus eStat;

	// 간선으로 이어진 두 노드를 받아와 id를 가져옴
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// 만약 두 노드가 모두 유효하다면 간선이 방문했는지(발견했는지/ 뒤로가는지)여부를 확인
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

	// 간선으로 이어진 두 노드를 받아와 id를 가져옴
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// 만약 두 노드가 모두 유효하다면 간선의 상태를 es로 변경
	if (graph.isValidvID(vID_1) && graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = es;
}
EdgeStatus DepthFirstSearch::EdgeStat(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = graph.NumVertices();
	EdgeStatus eStat;

	// 간선으로 이어진 두 노드를 받아와 id를 가져옴
	vrtx_1 = *e.pvrtx_1();	vrtx_2 = *e.pvrtx_2();
	vID_1 = vrtx_1.Id();	vID_2 = vrtx_2.Id();

	// 만약 두 노드가 모두 유효하다면 간선의 현재상태를 반환
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
