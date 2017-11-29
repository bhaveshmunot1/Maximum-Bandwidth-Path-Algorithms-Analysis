#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include "Heap.cpp"
#include "union_find.cpp"

using namespace std;

struct path
{
	vector<int> order;
	int distance;
};

struct mstPath
{
	vector<pair<int, pair<int, int>>> edges;
	int weight;
};

struct max_bw_path
{
	vector<int> order;
	int bandwidth;
};

typedef struct max_bw_path MBPPath;
typedef struct path Path;
typedef struct mstPath MSTPath;

struct mstGraph
{
	MSTPath path;
	unordered_map<int, vector<pair<int, int>>> mst;
};

typedef struct mstGraph MSTGraph;


class Graph
{
private:
	int nodes;
	int edges;
	unordered_map<int, vector<pair<int, int>>> graph;
	void GetInput(int nodes, int edges);
	enum COLORS {WHITE, GRAY, BLACK};
	bool DFS(unordered_map<int, vector<pair<int, int>>> g, int destination, vector<int> &answer, vector<int> current, int color[], int &bandwidth, int curBW);
public:
	Graph();
	virtual ~Graph();
	Graph(int nodes, int edges, vector<pair<int, pair<int, int>>> x);
	Graph(int _nodes, int _edges);
	void PrintGraph(ofstream &);
	/*
        Path BellmanFordShortestPath();
        MSTPath KruskalMinimumSpanningTree();
        Path DijkstraShortestPathHeap(int source, int destination);
        Path DijkstraShortestPathNaive(int source, int destination);
	*/
	MBPPath  MaximumBandwidthPathHeap(int source, int destination);
	MBPPath  MaximumBandwidthPathNaive(int source, int destination);
	MSTGraph KruskalMaximumSpanningTree();
	MBPPath  KruskalMaxBandwidthPath(int source, int destination, unordered_map<int, vector<pair<int, int>>> &kruskalsMaximumSpanningTree);
};

#endif // GRAPH_H
