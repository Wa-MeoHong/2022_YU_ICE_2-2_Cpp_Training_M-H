/*
  ���ϸ� : "�ǽ�13_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Dijkstra�� �����Ͽ� �ڵ��ϼ� ����� Ȯ���غ���.
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 12�� 6��)
  ���� Update : Version 1.0.0, 2022�� 12�� 6��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/12/06		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/12/08		v1.1.0		  �ѱ� ���� �׷��� �ڷ� �߰�
	�Ŵ�ȫ		 2022/12/09		v1.2.0		  DFS, BFS �˰��� �߰�

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_Dijkstra.h"

#define INPUT1 "USA_7_cities.txt"
#define INPUT2 "Korea_11.txt"
using namespace std;

void fgetGraph(Graph* g, string fin_name)
{
	ifstream fin(fin_name);
	int num_vrtx;
	string gName, v1, v2;
	double dist;
	Vertex vrtx1, vrtx2, * pVrtx1, * pVrtx2;
	Edge e1, e2;
	int num_edge = 0; 
	
	// ���� ���� ���н� Ż��
	if (fin.fail())
	{
		cout << "Fail to open input file !! ";
		exit(-1);
	}

	// ���� �б� ��, ���� �������
	fin >> gName >> num_vrtx;
	g->initGraph(gName, num_vrtx);
	cout << "Initializing graph (" << gName << ") from input data file (" << fin_name << ") . . ." << endl;
	while (!fin.eof())
	{
		// ������ ���� ������ ���ѹݺ�
		fin >> v1 >> v2 >> dist;
		//cout << "insert edge (" << v1 << " -> " << v2 << " : " << dist << ")" << endl;
		vrtx1 = Vertex(v1, -1); vrtx2 = Vertex(v2, -1);
		pVrtx1 = g->insertVertex(vrtx1);
		pVrtx2 = g->insertVertex(vrtx2);
		e1 = Edge(*pVrtx1, *pVrtx2, dist);
		e2 = Edge(*pVrtx2, *pVrtx1, dist);
		g->insertEdge(e1); g->insertEdge(e2);
		num_edge++;
	}
}

int main(void)
{
	Graph simpleGraph;

	fgetGraph(&simpleGraph, INPUT2);

	// ���Ե� Vertex���� ��� ���
	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst);		// Vertex���� ��� ����

	// ���
	int count = 0;
	cout << "\nInserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor)
	{
		cout << *vItor << ", ";
	}
	cout << endl << endl;

	// ���Ե� edge�� ����Ʈ�� ��� ���
	cout << "Inserted edges: " << endl;
	EdgeList egLst;
	simpleGraph.edges(egLst);			// ����Ʈ�� ����
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		cout << *p << ", ";
		// 5�� ����� ������ �ٹٲ�
		if (count % 5 == 0)
			cout << endl;
	}
	cout << endl << endl;

	cout << "Print out Graph based on Adjacency List . ." << endl;
	simpleGraph.fprintGraph(cout);

	//======================================================================================

	VrtxList path;
	BreadthFirstSearch bfsGraph(simpleGraph);

	cout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl;

	simpleGraph.initDistMtrx();
	simpleGraph.fprintDistMtrx(cout);

	path.clear();
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	while (1)
	{
		// .. �Է½� ����
		cout << "Input start and end of path to search shortest path (.. to quit) : ";
		cin >> start_nm;
		if (start_nm == "..")
			break;
		cin >> end_nm;

		// Vertex�� Edge���� ���� ����
		pStart = simpleGraph.getVertex(start_nm);
		pEnd = simpleGraph.getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex Name !!" << endl;
			exit(-1);
		}

		// �ִܰŸ��� ã��
		cout << "\nDijkstra Shortest Path Finding from" << pStart->Name()
			<< " to " << pEnd->Name() << "...." << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " �� ";
		}
		cout << endl;

		//�ݴ�������ε� ���
		pEnd = simpleGraph.getVertex(start_nm);
		pStart = simpleGraph.getVertex(end_nm);
		cout << "\nDijkstra Shortest Path Finding from " << pStart->Name()
			<< " to " << pEnd->Name() << "...." << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " �� ";
		}
		cout << endl;
	}

	return 0;
}