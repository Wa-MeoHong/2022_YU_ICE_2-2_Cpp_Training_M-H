#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

#define PLUS_INF INT_MAX/2
enum VrtxStatus { UN_VISITED, VISITED, Not_SELECTED, SELECTed, VRTX_SELECTED, VRTX_NOT_SELECTED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_NOT_SELECTED, EDGE_SELETED,
	EDGE_VISITED, EDGE_NOT_FOUND };

class Graph
{
public:
	class Vertex;					// 클래스 Vertex (Node)
	class Edge;						// 클래스 Edge (간선)
	typedef std::list<Graph::Vertex> VrtxList;		// Vertex List
	typedef std::list<Graph::Edge> EdgeList;		// Edge List (이어진 노드를 표현)
	typedef std::list<Graph::Vertex>::iterator VrtxItor;		// iterator 1
	typedef std::list<Graph::Edge>::iterator EdgeItor;			// iterator 2

public:
	class Vertex
	{
		friend ostream& operator<< (ostream& ostr, Vertex v)
		{
			ostr << v.Name();
			return ostr;
		}

	public:
		// constructor
		Vertex() : name(""), ID(-1) {}
		Vertex(string n, int id) : name(n), ID(id) {}
		Vertex(int id) : ID(id) {}
		// getter
		string Name() { return name; }
		int Id() { return ID; }
		VrtxStatus VrtxStat() { return vrtxStatus; }

		// setter
		void SetName(string n) { name = n; }
		void SetID(int id) { ID = id; }
		void SetVrtxStat(VrtxStatus vs) { vrtxStatus = vs; }

		// operator overloading
		bool operator==(Vertex other) { return ((ID == other.Id()) && (name == other.Name())); }
		bool operator!=(Vertex other) { return ((ID != other.Id()) || (name != other.Name())); }

	private:
		string name;
		int ID;
		VrtxStatus vrtxStatus;
	}; // end of class Vertex
	class Edge // Graph::Edge
	{
		friend ostream& operator<<(ostream& ostr, Edge& e)
		{
			ostr << "Edge(" << setw(2) << *e.pvrtx_1() << ", " << setw(2) << *e.pvrtx_2();
			ostr << ", " << setw(2) << e.Distance() << ")";
			return ostr;
		}
	public:
		// constructor
		Edge() 
			: pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF), edgeStatus(EDGE_UN_VISITED) {}
		Edge(Vertex& v1, Vertex& v2, double d)
			: pVrtx_1(&v1), pVrtx_2(&v2), distance(d), edgeStatus(EDGE_UN_VISITED) {}

		//member function 
		
		void endVertices(VrtxList& vrtxLst)
		{
			// 리스트에 집어넣음
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		// 반대쪽 Vertex 반환
		Vertex opposite(Vertex v)
		{
			// 1번 vertex라면 2번을 반환
			if (v == *pVrtx_1)
				return *pVrtx_2;
			// 2번 vertex라면 1번을 반환
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			// 아무것도 아니면 NULL 반환
			else
				return Vertex(NULL);
		}

		// getter
		Vertex* pvrtx_1() { return pVrtx_1; }
		Vertex* pvrtx_2() { return pVrtx_2; }
		double Distance() { return distance; }
		EdgeStatus EdgeStat() { return edgeStatus; }

		// setter
		void SetpVrtx_1(Vertex* pV) { pVrtx_1 = pV; }
		void SetpVrtx_2(Vertex* pV) { pVrtx_2 = pV; }
		void SetDistance(double d) { distance = d; }
		void SetEdgeStat(EdgeStatus es) { edgeStatus = es; }


		// operator overloading
		bool operator!=(Edge e) { return ((pVrtx_1 != e.pvrtx_1()) || (pVrtx_2 != e.pvrtx_2())); }
		bool operator==(Edge e) { return ((pVrtx_1 == e.pvrtx_1()) && (pVrtx_2 == e.pvrtx_2())); }

	private:
		Vertex* pVrtx_1;
		Vertex* pVrtx_2;
		double distance;
		EdgeStatus edgeStatus;
	}; // end of class Edge

public:
	// constructor
	Graph() :name(""), pVrtxArray(NULL), pAdjLstArray(NULL), num_vertices(0) {}
	Graph(string nm, int num_nodes)
		:name(nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		initGraph(nm, num_nodes);
	}

	// getter 
	string NAME() { return name; }
	Vertex* pVrtxArr() { return pVrtxArray;}
	EdgeList* pAdjLstArr() { return pAdjLstArray; }
	int NumVertices() { return num_vertices; }
	double** DistMtrx() { return ppDistMtrx; }
	Vertex* getVertex(string vName)
	{
		for (int i = 0; i < this->NumVertices(); i++)
		{
			if (pVrtxArray[i].Name() == vName)
				return &pVrtxArray[i]; // vertex가 이미 존재한다면
		}
		return NULL;	// 없으면 NULL 반환
	}

	// member function
	void initGraph(string nm, int num_nodes)		// constructor와 거의 같은 함수
	{
		name = nm;
		pVrtxArray = new Graph::Vertex[num_nodes];		// 노드 수 만큼 동적할당
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_nodes];			// 노드 수 만큼 동적할당
		for (int i = 0; i < num_nodes; i++)
			pAdjLstArray[i].clear();
		this->ppDistMtrx = new double* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new double[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			for (int j = 0; j < num_nodes; j++)
				ppDistMtrx[i][j] = PLUS_INF;

		num_vertices = 0;			 // num_vertices is increased at insertVertex
		
	}
	void initDistMtrx()				// 거리 표 초기화
	{
		int curVID, vID;

		for (int i = 0; i < num_vertices; i++)
		{
			// vID를 모두 들고와서
			curVID = pVrtxArray[i].Id();
			EdgeItor pe = pAdjLstArray[curVID].begin();		// Iterator를 설정
			while (pe != pAdjLstArray[curVID].end())		// current Vertex ID 의 Edge리스트를 모두 꺼내서 넣음
			{
				// ppDistMtrx에 값을 넣어준다.
				vID = (*(*pe).pvrtx_2()).Id();
				ppDistMtrx[curVID][vID] = (*pe).Distance();	// 거리 행렬에 모두 넣어줌
				pe++;
			}
			// 자기자신은 거리가 0이다.
			ppDistMtrx[curVID][curVID] = 0.0;
		}
	}
	void vertices(VrtxList& vrtxLst)
	{
		vrtxLst.clear();
		for (int i = 0; i < NumVertices(); i++)
			vrtxLst.push_back(pVrtxArray[i]);		// 리스트에 집어넣음
	}
	void edges(EdgeList& edges)
	{
		EdgeItor eItor;
		Graph::Edge e;

		edges.clear();
		for (int i = 0; i < NumVertices(); i++)
		{
			// 값을 가져오기 위해 Iterator를 이용한다.
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;				// 값을 가져옴
				edges.push_back(e);		// 리스트에 Push함
				eItor++;
			}
		}
	}
	Vertex* insertVertex(Vertex& newV)
	{
		int vID;
		string vName;
		vName = newV.Name();

		// 이미 넣은 이름이라면 바로 빠져나감 (중복허용 X)
		for (int i = 0; i < this->num_vertices; i++)
		{
			if (pVrtxArray[i].Name() == vName)
				return &pVrtxArray[i];
		}

		// 만약 들어있지 않다면 새롭게 추가한다
		vID = this->num_vertices;
		newV.SetID(vID);
		if (pVrtxArray[vID] == NULL)
		{
			pVrtxArray[vID] = newV;
			this->num_vertices++;
		}
		return &pVrtxArray[vID];		// 넣은 Vertex 반환
	}
	void insertEdge(Edge& e)
	{
		Vertex vrtx_1, vrtx_2;
		int vrtx_1_ID, vrtx_2_ID;

		vrtx_1 = *e.pvrtx_1(); vrtx_2 = *e.pvrtx_2();
		vrtx_1_ID = vrtx_1.Id(); vrtx_2_ID = vrtx_2.Id();
		
		// if pVrtxArray에 담겨있지 않다면 전부 담아준다. 
		if (pVrtxArray[vrtx_1_ID] == NULL)
			pVrtxArray[vrtx_1_ID] = vrtx_1;
		if (pVrtxArray[vrtx_2_ID] == NULL)
			pVrtxArray[vrtx_2_ID] = vrtx_2;

		// edge를 추가함
		e.SetpVrtx_1(&pVrtxArray[vrtx_1_ID]);
		e.SetpVrtx_2(&pVrtxArray[vrtx_2_ID]);

		pAdjLstArray[vrtx_1_ID].push_back(e);
	}
	void incidentEdges(Vertex v, EdgeList& edgeLst)
	{
		Graph::Edge e;
		EdgeItor eItor;
		int vID = v.Id();

		// edgeList의 값을 가져옴
		eItor = pAdjLstArray[vID].begin();
		while (eItor != pAdjLstArray[vID].end())
		{
			// 한 Vertex에 연결된 Edge로 이어진 것들을 모두 리스트에 담아준다.
			e = *eItor;
			edgeLst.push_back(e);
			eItor++;
		}
	}

	bool isValidvID(int vid)
	{
		if ((vid >= 0) && (vid < num_vertices))
			return true;
		// else
		return false;
	}
	void fprintGraph(ostream& ostr)		// 출력
	{
		EdgeItor eItor;
		Graph::Edge e;
		int numOutgoingEdges;

		// print format : 이름 with Vertex개수 has following adjacency List :
		//  vertex ( Vertex ) : edge() edge() ...

		ostr << this->NAME() << " with " << this->NumVertices() << " vertices has following adjacency lists :" << endl;
		for (int i = 0; i < num_vertices; i++)
		{
			ostr << " vertex (" << setw(3) << pVrtxArray[i].Name() << ") :";
			numOutgoingEdges = pAdjLstArray[i].size();
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;
				ostr << e << " ";
				eItor++;
			}
			ostr << endl;
		}
	}
	void fprintDistMtrx(ostream& ostr)
	{
		double dist;

		// 거리행렬 출력 부분
		ostr << "\nDistance Matrix of Graph (" << NAME() << "):" << endl;
		ostr << "	|";
		for (int i = 0; i <num_vertices; i++)
		{
			ostr << setw(5) << pVrtxArray[i].Name();
		}
		ostr << endl;

		// 표의 구분선 출력
		ostr << "--------+";
		for (int i = 0; i < num_vertices; i++)
			ostr << "-----";
		ostr << endl;

		// 하나의 Vertex에 관한 다른 모든 Vertex와의 거리를 출력
		for (int i = 0; i < num_vertices; i++)
		{
			ostr << setw(7) << pVrtxArray[i].Name() << " |";
			for (int j = 0; j < num_vertices; j++)
			{
				dist = ppDistMtrx[i][j];
				if (dist == PLUS_INF)
					ostr << setw(5) << "+oo";		// ∞ 무한대 기호
				else
					ostr << setw(5) << dist;		// 아니면 바로 출력
			}
			ostr << endl;
		}
	}
private:
	string name;
	Vertex* pVrtxArray;			// 그래프의 Vertex 배열
	EdgeList* pAdjLstArray;		// 각 노드의 인접한 간선의 List 배열
	int num_vertices;			// Verties의 수
	double** ppDistMtrx;		// 인접 거리 표
};



#endif // !GRAPH_H
