
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

	// Vertex �ʱ�ȭ
	VrtxList vrtxLst;
	this->graph.vertices(vrtxLst);
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].SetVrtxStat(UN_VISITED);		// �湮���� ���� ����

	// ���� �ʱ�ȭ 
	EdgeList edges;
	this->graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->SetEdgeStat(EDGE_UN_VISITED);		// ���� edge�� ������ ���� ����
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
	int* pPrev;			// ���� ����� �ٷ� ������ �湮�� ����� �ε��� ��ȣ, �̰��� ���� �������� ���ư���
	int vID = 0;

	Vertex* pVrtxArray, * pVrtx;
	Vertex vrtx, v;
	Edge e;
	int start_vID, target_vID;
	VrtxList vrtxs;
	VrtxItor vItor;
	EdgeList edges;
	EdgeItor eItor;

	if (s == target)		// ���� ���۳�尡 Ÿ���̶�� 
	{
		done = true;		// BFS�� ������ �� 
		path.push_back(s);	// ��ο� PUSH�ϰ� ����
		return;
	}

	// ���� ���� �� �ʱ�ȭ, Vertex�� �ҷ���
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
	
	//ó�� ��带 �湮�ߴٰ� ǥ��
	visit(s);
	vItor = vrtxs.begin();
	pPrev[start_vID] = start_vID;
	num_visited = 0;
	// level 0 ( ó�� ���� ����� ����)
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
				graph.incidentEdges(*vItor, edges);		// vItor�� ����Ű�� vertex�� ���� �������� ����Ʈ�� �޾ƿ�
				eItor = edges.begin();

				while (eItor != edges.end())
				{
					pVrtx = eItor->pvrtx_2();
					if (pVrtx->VrtxStat() != VISITED)
					{
						nodeLevel[pVrtx->Id()] = level + 1;		// VItor�� �ݴ���� vItor�� Level + 1�̴�.
						pVrtx->SetVrtxStat(VISITED);
						eItor->SetEdgeStat(DISCOVERY);
						pPrev[pVrtx->Id()] = vItor->Id();		// pPrev�� ��������� ���̵� ����
					}
					else
						eItor->SetEdgeStat(CROSS);			// �̹� ���� ���� ����� ������ CROSS EDGE�� ǥ��(���� �ʴ´�)
				}	// end of while 
				++eItor;
			}// end of if()
			++vItor;
		}
		if (num_visited >= num_nodes)		// Ż�� ����
			break;
		level++;		// ������ �����ϰ�, ���� ���� Ž��
	} // end of while (num_visited < num_nodes)
	
	// ��� ��带 Ž���� ��, path�� push�Ѵ�.
	vID = target_vID;
	while (vID != start_vID)
	{
		pVrtx = &pVrtxArray[vID];		// Vertex Array���� Vertex�� �����ͼ� 
		path.push_front(*pVrtx);		// path�� ����
		vID = pPrev[vID];				// vID�� vID�� ���� ����� ���̵�� ����
	}
	path.push_front(pVrtxArray[vID]);		// start_vertex�� push

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
	// ���� ����
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
	
	// �� �Լ� ����
	pLeastCost = new double[num_nodes];				// ������ �������� �Ÿ��� �ּҰŸ���
	pPrev = new int[num_nodes];						// Ž���� ������ ����ϱ� ���� Vertex ID
	pBFS_Process_Stat = new BFSstat[num_nodes];		// BFSŽ���� ��尡 ���õǾ����� �Ǻ��ϴ� �迭

	// initialize L(n) = w(start, n)
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}

	// ���� ��, ���
	pBFS_Process_Stat[start_vID] = SELECTED;
	num_selected = 1;
	path.clear();				// �ִܰŸ��� ã�Ƴ��� ���� ���� path�� �ʱ�ȭ�� ��Ŵ

	// ��¹�
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
	// ��¹� ����

	int round = 0;
	int cost;

	while (num_selected < num_nodes)
	{
		round++;
		ostr << "round [" << setw(2) << round << "]|";
		minID = -1;
		minCost = PLUS_INF;				// �ּҰŸ��� ����

		for (int i = 0; i < num_nodes; i++)
		{	
			// ���� pLeastCost�ȿ� ����Ȱ��� minCost���� �۰�
			// Selected �Ǿ� ���� �ʴٸ�(�ѹ� �湮�ߴ� ��尡 �ƴ϶��)

			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED))
			{
				// �ּҰ� ����
				minID = i;
				minCost = pLeastCost[i];
			}
		}

		// ���� �ּҳ�带 ã�� ���ߴٸ�
		if (minID == -1)
		{
			ostr << "Error in Dijkstra() --found not connected vertex !!" << endl;
			break;
		}
		// �ּҳ�带 ã�Ҵٸ�
		else
		{
			// �ѷ��� Vertex�� ���� ����� ���� ��� Vertex�� �����Ѵ�.
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;	

			// ���� �� ���õ� vertex�� ���� ã���ִ� ���������� Vertex��� 
			if (minID == target_vID)
			{
				ostr << endl << "reached to the target node ("
					<< pVrtxArray[minID].Name() << ") at Least Cost = " << minCost << endl;
				vID = minID;

				// the others node push
				do
				{
					// ���������� ��忡�� �������� ���ư���,
					// ������ ������ ��ȯ�޾� path�� PUSH�Ѵ�.
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

