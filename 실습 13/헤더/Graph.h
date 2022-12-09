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
	class Vertex;					// Ŭ���� Vertex (Node)
	class Edge;						// Ŭ���� Edge (����)
	typedef std::list<Graph::Vertex> VrtxList;		// Vertex List
	typedef std::list<Graph::Edge> EdgeList;		// Edge List (�̾��� ��带 ǥ��)
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
			// ����Ʈ�� �������
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		// �ݴ��� Vertex ��ȯ
		Vertex opposite(Vertex v)
		{
			// 1�� vertex��� 2���� ��ȯ
			if (v == *pVrtx_1)
				return *pVrtx_2;
			// 2�� vertex��� 1���� ��ȯ
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			// �ƹ��͵� �ƴϸ� NULL ��ȯ
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
				return &pVrtxArray[i]; // vertex�� �̹� �����Ѵٸ�
		}
		return NULL;	// ������ NULL ��ȯ
	}

	// member function
	void initGraph(string nm, int num_nodes)		// constructor�� ���� ���� �Լ�
	{
		name = nm;
		pVrtxArray = new Graph::Vertex[num_nodes];		// ��� �� ��ŭ �����Ҵ�
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_nodes];			// ��� �� ��ŭ �����Ҵ�
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
	void initDistMtrx()				// �Ÿ� ǥ �ʱ�ȭ
	{
		int curVID, vID;

		for (int i = 0; i < num_vertices; i++)
		{
			// vID�� ��� ���ͼ�
			curVID = pVrtxArray[i].Id();
			EdgeItor pe = pAdjLstArray[curVID].begin();		// Iterator�� ����
			while (pe != pAdjLstArray[curVID].end())		// current Vertex ID �� Edge����Ʈ�� ��� ������ ����
			{
				// ppDistMtrx�� ���� �־��ش�.
				vID = (*(*pe).pvrtx_2()).Id();
				ppDistMtrx[curVID][vID] = (*pe).Distance();	// �Ÿ� ��Ŀ� ��� �־���
				pe++;
			}
			// �ڱ��ڽ��� �Ÿ��� 0�̴�.
			ppDistMtrx[curVID][curVID] = 0.0;
		}
	}
	void vertices(VrtxList& vrtxLst)
	{
		vrtxLst.clear();
		for (int i = 0; i < NumVertices(); i++)
			vrtxLst.push_back(pVrtxArray[i]);		// ����Ʈ�� �������
	}
	void edges(EdgeList& edges)
	{
		EdgeItor eItor;
		Graph::Edge e;

		edges.clear();
		for (int i = 0; i < NumVertices(); i++)
		{
			// ���� �������� ���� Iterator�� �̿��Ѵ�.
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;				// ���� ������
				edges.push_back(e);		// ����Ʈ�� Push��
				eItor++;
			}
		}
	}
	Vertex* insertVertex(Vertex& newV)
	{
		int vID;
		string vName;
		vName = newV.Name();

		// �̹� ���� �̸��̶�� �ٷ� �������� (�ߺ���� X)
		for (int i = 0; i < this->num_vertices; i++)
		{
			if (pVrtxArray[i].Name() == vName)
				return &pVrtxArray[i];
		}

		// ���� ������� �ʴٸ� ���Ӱ� �߰��Ѵ�
		vID = this->num_vertices;
		newV.SetID(vID);
		if (pVrtxArray[vID] == NULL)
		{
			pVrtxArray[vID] = newV;
			this->num_vertices++;
		}
		return &pVrtxArray[vID];		// ���� Vertex ��ȯ
	}
	void insertEdge(Edge& e)
	{
		Vertex vrtx_1, vrtx_2;
		int vrtx_1_ID, vrtx_2_ID;

		vrtx_1 = *e.pvrtx_1(); vrtx_2 = *e.pvrtx_2();
		vrtx_1_ID = vrtx_1.Id(); vrtx_2_ID = vrtx_2.Id();
		
		// if pVrtxArray�� ������� �ʴٸ� ���� ����ش�. 
		if (pVrtxArray[vrtx_1_ID] == NULL)
			pVrtxArray[vrtx_1_ID] = vrtx_1;
		if (pVrtxArray[vrtx_2_ID] == NULL)
			pVrtxArray[vrtx_2_ID] = vrtx_2;

		// edge�� �߰���
		e.SetpVrtx_1(&pVrtxArray[vrtx_1_ID]);
		e.SetpVrtx_2(&pVrtxArray[vrtx_2_ID]);

		pAdjLstArray[vrtx_1_ID].push_back(e);
	}
	void incidentEdges(Vertex v, EdgeList& edgeLst)
	{
		Graph::Edge e;
		EdgeItor eItor;
		int vID = v.Id();

		// edgeList�� ���� ������
		eItor = pAdjLstArray[vID].begin();
		while (eItor != pAdjLstArray[vID].end())
		{
			// �� Vertex�� ����� Edge�� �̾��� �͵��� ��� ����Ʈ�� ����ش�.
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
	void fprintGraph(ostream& ostr)		// ���
	{
		EdgeItor eItor;
		Graph::Edge e;
		int numOutgoingEdges;

		// print format : �̸� with Vertex���� has following adjacency List :
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

		// �Ÿ���� ��� �κ�
		ostr << "\nDistance Matrix of Graph (" << NAME() << "):" << endl;
		ostr << "	|";
		for (int i = 0; i <num_vertices; i++)
		{
			ostr << setw(5) << pVrtxArray[i].Name();
		}
		ostr << endl;

		// ǥ�� ���м� ���
		ostr << "--------+";
		for (int i = 0; i < num_vertices; i++)
			ostr << "-----";
		ostr << endl;

		// �ϳ��� Vertex�� ���� �ٸ� ��� Vertex���� �Ÿ��� ���
		for (int i = 0; i < num_vertices; i++)
		{
			ostr << setw(7) << pVrtxArray[i].Name() << " |";
			for (int j = 0; j < num_vertices; j++)
			{
				dist = ppDistMtrx[i][j];
				if (dist == PLUS_INF)
					ostr << setw(5) << "+oo";		// �� ���Ѵ� ��ȣ
				else
					ostr << setw(5) << dist;		// �ƴϸ� �ٷ� ���
			}
			ostr << endl;
		}
	}
private:
	string name;
	Vertex* pVrtxArray;			// �׷����� Vertex �迭
	EdgeList* pAdjLstArray;		// �� ����� ������ ������ List �迭
	int num_vertices;			// Verties�� ��
	double** ppDistMtrx;		// ���� �Ÿ� ǥ
};



#endif // !GRAPH_H
