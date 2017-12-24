#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>
using namespace std;

#define MAX_NODES 50000
#define UNDEFINED -1
#define HASH_MUL 1000000

class GraphGenerator
{
	bool all_connected;
	int degree_per_vertex;
	int percentage_connection;
	bool simple_graph_only;
	bool directed_only;
	int degree[MAX_NODES];
	unordered_map<int, std::vector<int>> graph;
	int nodes;
	int maxWeight, minWeight;
	int tolerance;
	vector<pair<int, pair<int, int>>> answer;
	unordered_map<long, bool> ed;

public:
	GraphGenerator(int _nodes,
				   int _all_connected=true,
				   int _degree_per_vertex=UNDEFINED,
				   int _percentage_connection=UNDEFINED,
				   int _simple_graph_only=true,
				   int _directed_only=false,
				   int _maxWeight=300,
				   int _minWeight=100
				   )
	{
		srand (time(NULL));
		nodes = _nodes;
		all_connected = _all_connected;
		degree_per_vertex = _degree_per_vertex;
		if (_percentage_connection != UNDEFINED)
		{
			degree_per_vertex = nodes*_percentage_connection/100;
			tolerance = degree_per_vertex/20;
		}
		simple_graph_only = _simple_graph_only;
		directed_only=_directed_only;

		for (int i=1; i<=nodes; i++)
		{
			degree[i] = 0;
		}
		maxWeight = _maxWeight;
		minWeight = _minWeight;
		//cout << "out" << endl;
	}

	void randomShuffle(vector<int> &v)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  		shuffle (v.begin(), v.end(), std::default_random_engine(seed));
	}

	vector<int> shuffledPermutation()
	{
		vector<int> v;
		for (int i=0; i<nodes; i++)
			v.push_back(i+1);
		randomShuffle(v);
		return v;
	}

	int randInt(int start, int end)
	{
		return rand()%(end-start+1) + start;
	}

	int randInt()
	{
		return randInt(1, nodes);
	}

	bool doesEdgeExist(int s, int t)
	{
		return ed.find(HASH_MUL) != ed.end();
		/*// cout << " doesEdgeExist " << endl;
		for (int i=0; i<graph[s].size(); i++)
		{
			if (graph[s][i] == t)
				return true;
		}
		// cout << " returning false " << endl;
		return false;*/
	}

	bool connect(int from, int to, int weight)
	{
		bool ret = false;
		//cout << " connect " << endl;
		do
		{
			if (from == to)
			{
				ret = false;
				break;
			}
			if (from<1 || from>nodes ||
				to<1 || to>nodes)
			{
				ret = false;
				break;
			}

			if (degree[from]>(degree_per_vertex+tolerance) || degree[to]>(degree_per_vertex+tolerance))
			{
				ret = false;
				break;
			}

			if (doesEdgeExist(from, to) == false)
			{
				// cout << " connecting " << endl;
				graph[from].push_back(to);
				ed[from*HASH_MUL+to] = true;
				// graph[to].push_back(from);
				degree[from]++;
				degree[to]++;
				ret = true;
			}
		}while(0);

		if (ret)
		{
			answer.push_back(make_pair(weight, make_pair(from, to)));
			// cout << from << " " << to << " " << weight << endl;
		}
		return ret;
	}

	int addWeight()
	{
		return randInt(minWeight, maxWeight);
	}

	void PrintDegree()
	{
		for(int i=1; i<=nodes; i++)
		{
			cout << degree[i] << " " ;
		}
		cout << endl;
		for(int i=1; i<=nodes; i++)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	vector<pair<int, pair<int, int>>> generate()
	{
		// cout << "in" << endl;
		answer.clear();

		if (all_connected)
		{
			std::vector<int> v = shuffledPermutation();
			for (int i=0; i<v.size()-1; i++)
			{
				int w = addWeight();
				connect(v[i], v[i+1], w);
			}
			int w = addWeight();
			connect(v[0], v[v.size()-1], w);
		}
		// cout << "out" << endl;
		for (int from = 1; from<=nodes; from++)
		{
			int attempts = 0;
			while(degree[from]<degree_per_vertex && attempts<(nodes/20))
			{
				int to = randInt();
				int w = addWeight();
				if (connect(from, to, w))
				{
					attempts = 0;
				}
				else
				{
					attempts++;
				}
			}
		}
		return answer;
	}
};
