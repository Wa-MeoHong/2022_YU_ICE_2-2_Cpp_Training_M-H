
/* BFS_Dijkstra.cpp */

#include "Graph.h"
#include "BFS_Dijkstra.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>

using namespace std;

void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = Graph().pVrtxArr();
	int num_vertices = Graph().NumVertices();

	// Vertex 초기화
	VrtxList vrtxLst;
	this->graph.vertices(vrtxLst);
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].SetVrtxStat(UN_VISITED);		// 방문하지 못한 상태

	// 간선 초기화 
	EdgeList edges;
	this->graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->SetEdgeStat(EDGE_UN_VISITED);		// 간선 edge를 지나지 않은 상태
}

void BreadthFirstSearch::bfsShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	initialize();
	path.clear();

	graph.initDistMtrx(); //fprintDistMtrx(fout);
	_bfsTraversal(fout, start, target, path);
}

void BreadthFirstSearch::_bfsTraversal(ostream& ostr, Vertex& s, Vertex& target, VrtxList& path)
{
	int* nodeLevel;
	int num_nodes = 0, num_visited = 0;
	int* pPrev;			// 현재 노드의 바로 이전에 방문한 노드의 인덱스 번호, 이것을 통해 역순으로 돌아간다
	int vID = 0;

	Vertex* pVrtxArray, * pVrtx;
	Vertex vrtx, v;
	Edge e;
	int start_vID, target_vID;
	VrtxList vrtxs;
	VrtxItor vItor;
	EdgeList edges;
	EdgeItor eItor;

	if (s == target)		// 만약 시작노드가 타겟이라면 
	{
		done = true;		// BFS를 종료한 후 
		path.push_back(s);	// 경로에 PUSH하고 종료
		return;
	}

	// 변수 설정 및 초기화, Vertex를 불러옴
	pVrtxArray = graph.pVrtxArr();	start_vID = s.Id();
	target_vID = target.Id(); num_nodes = graph.NumVertices();
	pPrev = new int[num_nodes];
	nodeLevel = new int[num_nodes];

	for (int i = 0; i < num_nodes; i++)
	{
		nodeLevel[i] = -1;
		pPrev[i] = -1;
	}

	graph.vertices(vrtxs);
	
	//처음 노드를 방문했다고 표시
	visit(s);
	vItor = vrtxs.begin();
	pPrev[start_vID] = start_vID;
	num_visited = 0;
	// level 0 ( 처음 시작 노드의 레벨)
	int level = 0;
	nodeLevel[start_vID] = 0;

	while (num_visited < num_nodes)
	{
		ostr << "Level (" << setw(2) << level << ") : ";
		vItor = vrtxs.begin();
		while (vItor != vrtxs.end())
		{
			vID = vItor->Id();
			if (isVisited(*vItor) && nodeLevel[vID] == level)
			{
				ostr << *vItor << ", ";
				graph.incidentEdges(*vItor, edges);		// vItor가 가리키는 vertex의 인접 간선들의 리스트를 받아옴
				eItor = edges.begin();

				while (eItor != edges.end())
				{
					pVrtx = eItor->pvrtx_2();
					if (pVrtx->VrtxStat() != VISITED)
					{
						nodeLevel[pVrtx->Id()] = level + 1;		// VItor의 반대노드는 vItor의 Level + 1이다.
						pVrtx->SetVrtxStat(VISITED);
						eItor->SetEdgeStat(DISCOVERY);
						pPrev[pVrtx->Id()] = vItor->Id();		// pPrev에 이전노드의 아이디를 넣음
					}
					else
						eItor->SetEdgeStat(CROSS);			// 이미 만난 노드와 연결된 간선은 CROSS EDGE로 표시(가지 않는다)
				}	// end of while 
				++eItor;
			}// end of if()
			++vItor;
		}
		if (num_visited >= num_nodes)		// 탈출 구문
			break;
		level++;		// 레벨을 증가하고, 다음 레벨 탐색
	} // end of while (num_visited < num_nodes)
	
	// 모든 노드를 탐색한 후, path에 push한다.
	vID = target_vID;
	while (vID != start_vID)
	{
		pVrtx = &pVrtxArray[vID];		// Vertex Array에서 Vertex를 가져와서 
		path.push_front(*pVrtx);		// path에 넣음
		vID = pPrev[vID];				// vID를 vID의 이전 노드의 아이디로 갱신
	}
	path.push_front(pVrtxArray[vID]);		// start_vertex를 push

}

void BreadthFirstSearch::visit(Vertex& v)
{
	int numNodes = graph.NumVertices();
	int vID = v.Id();
	if (isValidvID(vID))
	{
		Vertex* pVrtx = graph.pVrtxArr();
		pVrtx[vID].SetVrtxStat(VISITED);
	}
}

bool BreadthFirstSearch::isVisited(Vertex& v)
{
	int numNodes = graph.NumVertices();
	int vID = v.Id();
	if (isValidvID(vID))
	{
		Vertex* pVrtx = graph.pVrtxArr();
		return (pVrtx[vID] == VISITED);
	}
	return false;
}

void BreadthFirstSearch::DijkstraShortestPath(ostream& ostr, Vertex& start, Vertex& target, VrtxList& path)
{
	// 변수 설정
	double** ppDistMtrx = DistMtrx();
	double* pLeastCost, minCost;
	int num_nodes = NumVertices();
	int num_selected, minID;
	BFSstat* pBFS_Process_Stat;
	int* pPrev;

	Vertex* pVrtxArray = this->graph.pVrtxArr();
	Vertex vrtx, v;
	Edge e;
	int start_vID, target_vID, vID;
	EdgeList* pAdjLstArray = this->graph.pAdjLstArr();
	start_vID = start.Id(); target_vID = target.Id();
	
	// 본 함수 시작
	pLeastCost = new double[num_nodes];				// 지나간 간선간의 거리의 최소거리합
	pPrev = new int[num_nodes];						// 탐색의 순서를 기록하기 위한 Vertex ID
	pBFS_Process_Stat = new BFSstat[num_nodes];		// BFS탐색중 노드가 선택되었는지 판별하는 배열

	// initialize L(n) = w(start, n)
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}

	// 선택 후, 출력
	pBFS_Process_Stat[start_vID] = SELECTED;
	num_selected = 1;
	path.clear();				// 최단거리를 찾아내기 위해 먼저 path를 초기화를 시킴

	// 출력문
	ostr << "Dijkstra::Least Cost from Vertex (" << start.Name() << ") at each round : " << endl;
	ostr << "	  |";
	for (int i = 0; i < num_nodes; i++)
	{
		ostr << setw(5) << pVrtxArray[i].Name();
	}
	ostr << endl;
	ostr << "----------+";
	for (int i = 0; i < num_nodes; i++)
		ostr << setw(5) << "-----";
	ostr << endl;
	// 출력문 종료

	int round = 0;
	int cost;

	while (num_selected < num_nodes)
	{
		round++;
		ostr << "round [" << setw(2) << round << "]|";
		minID = -1;
		minCost = PLUS_INF;				// 최소거리를 구함

		for (int i = 0; i < num_nodes; i++)
		{	
			// 만약 pLeastCost안에 저장된값이 minCost보다 작고
			// Selected 되어 있지 않다면(한번 방문했던 노드가 아니라면)

			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED))
			{
				// 최소값 갱신
				minID = i;
				minCost = pLeastCost[i];
			}
		}

		// 만약 최소노드를 찾지 못했다면
		if (minID == -1)
		{
			ostr << "Error in Dijkstra() --found not connected vertex !!" << endl;
			break;
		}
		// 최소노드를 찾았다면
		else
		{
			// 둘러본 Vertex중 가장 비용이 적게 드는 Vertex를 선택한다.
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;	

			// 만약 그 선택된 vertex가 현재 찾고있는 최종목적지 Vertex라면 
			if (minID == target_vID)
			{
				ostr << endl << "reached to the target node ("
					<< pVrtxArray[minID].Name() << ") at Least Cost = " << minCost << endl;
				vID = minID;

				// the others node push
				do
				{
					// 최종목적지 노드에서 역순으로 돌아가서,
					// 만났던 노드들을 반환받아 path에 PUSH한다.
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];
				} while (vID != start_vID);

				// start node push
				vrtx = pVrtxArray[vID];
				path.push_front(vrtx);
				break;
			}
		}

		// Edge relaxation 
		for (int i = 0; i < num_nodes; i++)
		{
			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > pLeastCost[minID] + ppDistMtrx[minID][i]))
			{
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
			}
		}

		//print out the pLeastCost[] for debug
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				ostr << setw(5) << "+oo";
			else
				ostr << setw(5) << pLeastCost[i];
		}
		ostr << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	} // end of while ()
	
}

