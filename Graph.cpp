
#include "Graph.h"

Graph::Graph()
{
	cout << "Enter number of nodes and edges respectively: " ;
	cin >> nodes >> edges;
	GetInput(nodes, edges);
}

Graph::Graph(int _nodes, int _edges)
{
	GetInput(_nodes, _edges);
}

void Graph::GetInput(int nodes, int edges)
{
	// cout << "Enter <from> <to> <weight> for each edge" << endl;
	for (int i=0; i<edges; i++)
	{
		int from, to, weight;
		cin >> from >> to >> weight;
		if (from<1 || from>nodes ||
			to<1 || to>nodes)
		{
			cerr << "Invalid entry! " << endl;
			i--;
		}
		else
		{
			graph[from].push_back(make_pair(to, weight));
			// graph[to].push_back(make_pair(from, weight));
		}
	}
}

Graph::Graph(int _nodes, int _edges, vector<pair<int, pair<int, int>>> x)
{
	// cout << n
	nodes = _nodes;
	edges = _edges;
	for (int i=0; i<edges; i++)
	{
		int from = x[i].second.first, to = x[i].second.second, weight = x[i].first;

		if (from<1 || from>nodes ||
			to<1 || to>nodes)
		{
			cerr << "Invalid entry! " << endl;
			i--;
		}
		else
		{
			graph[from].push_back(make_pair(to, weight));
			graph[to].push_back(make_pair(from, weight));
		}
	}
}

void Graph::PrintGraph(ofstream &eout)
{
	#if 0
	cout << nodes << " " << edges << endl;
	for (int i=1; i<=nodes; i++)
	{
		cout << i << ": ";
		int n = graph[i].size();
		if (n>0)
		{
		//	eout << i << " " << graph[i][0].first << " " << graph[i][0].second << endl;
			cout << "<" << graph[i][0].first << ", " << graph[i][0].second << ">";
		}
		for (int j=1; j<n; j++)
		{
		//	eout << i << " " << graph[i][j].first << " " << graph[i][j].second << endl;
			cout << ", <" << graph[i][j].first << ", " << graph[i][j].second << ">";
		}
		cout << endl;
	}
	#else
	eout << nodes << " " << edges << endl;
	// cout << nodes << " " << edges << endl;
	for (int i=1; i<=nodes; i++)
	{
		// cout << i << ": ";
		int n = graph[i].size();
		if (n>0)
		{
			eout << i << " " << graph[i][0].first << " " << graph[i][0].second << endl;
		//	cout << "<" << graph[i][0].first << ", " << graph[i][0].second << ">";
		}
		for (int j=1; j<n; j++)
		{
			eout << i << " " << graph[i][j].first << " " << graph[i][j].second << endl;
		//	cout << ", <" << graph[i][j].first << ", " << graph[i][j].second << ">";
		}
		//cout << endl;
	}
	eout.close();
	#endif
}


MBPPath Graph::MaximumBandwidthPathNaive(int source, int destination)
{
	// cout << "In" << endl;
	int parent[nodes+1];
	int bandwidth[nodes+1];
	int status[nodes+1];

	enum status_of_node {INTREE, FRINGE, UNTOUCHED};

	for (int i=1; i<=nodes; i++)
		parent[i] = -1, bandwidth[i] = -1, status[i] = UNTOUCHED;

	parent[source] = 0;
	bandwidth[source] = 9999999;
	status[source] = FRINGE;

	// cout << "While start" << endl;
	while (status[destination] != INTREE )
	{
		int current = -1, bw = -1;
		for (int i=1; i<=nodes; i++)
		{
			// cout << " dist[i] = " << distance[i] << " " ;
			if (status[i] == FRINGE  && bw < bandwidth[i])
			{
				current = i;
				bw = bandwidth[current];
			}
		}
		// cout << current << " " << bandwidth[current] << endl;
		// cout << "For start, current = " << current << endl;
		vector<pair<int, int>> &curr_source = graph[current];
		for (int i=0; i<curr_source.size(); i++)
		{
            //cout << "  " << graph[current][i].first << " " << bandwidth[graph[current][i].first] << endl;
			if ((status[curr_source[i].first] != INTREE) &&
			    (bandwidth[curr_source[i].first] < min(bandwidth[current], curr_source[i].second)))
            {
                parent[curr_source[i].first] = current;
                bandwidth[curr_source[i].first] = min(bandwidth[current], curr_source[i].second);
                status[curr_source[i].first] = FRINGE;
                //cout << "  " << curr_source[i].first << " changed to " << bandwidth[curr_source[i].first] << endl;
            }
		}

		status[current] = INTREE;
	}
	// cout << "While end" << endl;
	stack<int> s;
	int node = destination;
	while (parent[node] != 0)
	{
		s.push(node);
		node = parent[node];
	}
	s.push(source);

	static MBPPath answer;
	answer.bandwidth = bandwidth[destination];
	while(!s.empty())
	{
		answer.order.push_back(s.top());
		s.pop();
	}
	return answer;
}

MBPPath Graph::MaximumBandwidthPathHeap(int source, int destination)
{
	// cout << "In" << endl;
	static MBPPath answer;
	MaxHeap h;
	int parent[nodes+1];
	int status[nodes+1];
	int bandwidth[nodes+1];
	enum status_of_node {INTREE, FRINGE, UNTOUCHED};

	for (int i=1; i<=nodes; i++)
		parent[i] = -1, bandwidth[i]=-1, status[i] = UNTOUCHED;


	parent[source] = 0;
	status[source] = FRINGE;
	bandwidth[source] = 99999999;
	h.insert(source, bandwidth);

	// cout << "While start" << endl;
	while (status[destination] != INTREE && !h.empty())
	{
		// h.Print(bandwidth);
		// cout << "In while" << endl; cin >> i;
		int current_max = h.top();
		int current = current_max;
		int bw = bandwidth[current_max];
		
		// cout << current << " " << bw << endl;
		h.delet(bandwidth);
		
		// cout << "For start, current = " << current << endl;
		vector<pair<int, int>> &curr_source = graph[current];
		for (int i=0; i<curr_source.size(); i++)
		{
			// cout << "  " << curr_source[i].first << " " << distance[curr_source[i].first] << endl;
			if ((status[curr_source[i].first] != INTREE) && 
				(bandwidth[curr_source[i].first] < min(bw, curr_source[i].second)))
			{
				parent[curr_source[i].first] = current;
				bandwidth[curr_source[i].first] = min(bw, curr_source[i].second);
				h.update(curr_source[i].first, bandwidth);
				status[curr_source[i].first] = FRINGE;
				//cout << "  " << curr_source[i].first << " changed to " << bandwidth[curr_source[i].first] << endl;
			}
		}
		if (current == destination)
			answer.bandwidth = bw;
		status[current] = INTREE;
	}
	if (status[destination] != INTREE)
		cerr << " ERRRRRORRRRR " << endl;
	// cout << "While end" << endl;
	stack<int> s;
	int node = destination;
	while (parent[node] != 0)
	{
		s.push(node);
		node = parent[node];
	}
	s.push(source);
	while(!s.empty())
	{
		answer.order.push_back(s.top());
		s.pop();
	}

	return answer;
}

MSTGraph Graph::KruskalMaximumSpanningTree()
{
	// cout << "in" << endl;
	//cout << "pushing to heap" << endl;
	MaxHeapForEdges h;
	MSTGraph answer;
	answer.path.weight = 0;

	for (int i=1; i<=nodes; i++)
	{
		for (int j=0; j<graph[i].size(); j++)
		{
			if (i<graph[i][j].first)
			{
				// cout << "Inserting " << endl;
				h.insert(make_pair(graph[i][j].second, make_pair(i, graph[i][j].first)));
			}
		}
	}

	//cout << "pushed to heap" << endl;
	UnionFind uf(nodes);
	int edges = 0, i = 0;
	while (edges < (nodes-1))
	{
		// cout << "In while" << endl;
		pair<int, pair<int, int>> current = h.top();
		h.delet();
		// cout << current.second.first << " " <<  current.second.second << endl;
		if (!uf.will_form_cycle(current.second.first, current.second.second))
		{
			uf.Union(current.second.first, current.second.second);
			answer.path.edges.push_back(current);
			// cout << current.first << endl;
			answer.path.weight += current.first;
			edges++;
		}
		else
		{
			// cout << "Ignored" << endl;
		}
		i++;
	}

	MSTPath &kmst = answer.path;
	for (int i=0; i<kmst.edges.size(); i++)
	{
		answer.mst[kmst.edges[i].second.first].push_back(make_pair(kmst.edges[i].second.second, kmst.edges[i].first));
		answer.mst[kmst.edges[i].second.second].push_back(make_pair(kmst.edges[i].second.first, kmst.edges[i].first));
	}

	return answer;
}


MBPPath Graph::KruskalMaxBandwidthPath(int source, int destination, unordered_map<int, vector<pair<int, int>>> &mst)
{
	MBPPath answer;
	answer.bandwidth = 0;
	
	// for (int i=0; i<kruskalsMaximumSpanningTree.edges.size(); i++)
		// cout << kruskalsMaximumSpanningTree.edges[i].second.first << " " << kruskalsMaximumSpanningTree.edges[i].second.second << endl;
	// cout << kruskalsMaximumSpanningTree.weight << endl;
	
	//cout << "tree genrated" << endl;
	/*
	for (int i=1; i<=nodes; i++)
	{
		cout << i << ": ";
		int n = mst[i].size();
		if (n>0)
		{
			cout << "<" << mst[i][0].first << ", " << mst[i][0].second << ">";
		}
		for (int j=1; j<n; j++)
		{
			cout << ", <" << mst[i][j].first << ", " << mst[i][j].second << ">";
		}
		cout << endl;
	}
	*/

	int bandwidth[nodes+1] = {0};
	bandwidth[source] = 99999999;
	int parent[nodes+1] = {0};
	parent[source] = -1;
	queue<int> q;
	q.push(source);
	while (!q.empty())
	{
		int current = q.front();
		//cout << current << endl;
		if (current == destination)
			break;
		q.pop();
		for (int i=0; i<mst[current].size(); i++)
		{
			if (parent[mst[current][i].first] == 0)
			{
				parent[mst[current][i].first] = current;
				bandwidth[mst[current][i].first] = min(bandwidth[current], mst[current][i].second);
				q.push(mst[current][i].first);	
			}
		}
	}
	//cout << "path genrated" << endl;
	answer.bandwidth = bandwidth[destination];
	stack<int> s;
	int node = destination;
	while (parent[node] != -1)
	{
		//cout << node << endl;
		s.push(node);
		node = parent[node];
	}
	s.push(source);
	while(!s.empty())
	{
		//cout << s.top() << endl;
		answer.order.push_back(s.top());
		s.pop();
	}
	return answer;
}


Graph::~Graph()
{
    //dtor
}
