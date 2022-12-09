/*
  파일명 : "실습13_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Dijkstra를 구성하여 자동완성 기능을 확인해본다.
  프로그램 작성자 : 신대홍(2022년 12월 6일)
  최종 Update : Version 1.0.0, 2022년 12월 6일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/12/06		v1.0.0		  최초작성
	신대홍		 2022/12/08		v1.1.0		  한국 지리 그래프 자료 추가
	신대홍		 2022/12/09		v1.2.0		  DFS, BFS 알고리즘 추가

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
	
	// 파일 열기 실패시 탈출
	if (fin.fail())
	{
		cout << "Fail to open input file !! ";
		exit(-1);
	}

	// 파일 읽기 후, 값을 집어넣음
	fin >> gName >> num_vrtx;
	g->initGraph(gName, num_vrtx);
	cout << "Initializing graph (" << gName << ") from input data file (" << fin_name << ") . . ." << endl;
	while (!fin.eof())
	{
		// 파일이 끝날 때까지 무한반복
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

	// 삽입된 Vertex들을 모두 출력
	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst);		// Vertex들을 모두 들고옴

	// 출력
	int count = 0;
	cout << "\nInserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor)
	{
		cout << *vItor << ", ";
	}
	cout << endl << endl;

	// 삽입된 edge의 리스트를 모두 출력
	cout << "Inserted edges: " << endl;
	EdgeList egLst;
	simpleGraph.edges(egLst);			// 리스트를 들고옴
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		cout << *p << ", ";
		// 5개 출력할 때마다 줄바꿈
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
		// .. 입력시 종료
		cout << "Input start and end of path to search shortest path (.. to quit) : ";
		cin >> start_nm;
		if (start_nm == "..")
			break;
		cin >> end_nm;

		// Vertex의 Edge정보 등을 얻어옴
		pStart = simpleGraph.getVertex(start_nm);
		pEnd = simpleGraph.getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex Name !!" << endl;
			exit(-1);
		}

		// 최단거리를 찾음
		cout << "\nDijkstra Shortest Path Finding from" << pStart->Name()
			<< " to " << pEnd->Name() << "...." << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " → ";
		}
		cout << endl;

		//반대방향으로도 계산
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
				cout << " → ";
		}
		cout << endl;
	}

	return 0;
}