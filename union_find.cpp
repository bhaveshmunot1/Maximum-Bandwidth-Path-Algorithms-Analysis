#include <iostream>
using namespace std;
#define MAX 100000
#include <queue>

class UnionFind
{
	int rank[MAX];
	int set[MAX];
	int n;
public:
	void Print()
	{
		return;

		cout << "sets[] = ";
		for (int i=1; i<=n; i++)
		{
			cout << set[i] << " ";
		}
		cout << endl;
		cout << "rank[] = ";
		for (int i=1; i<=n; i++)
		{
			cout << rank[i] << " ";
		}
		cout << endl;
		cout << "indx[] = ";
		for (int i=1; i<=n; i++)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	UnionFind(int _n)
	{
		n = _n;
		for (int i=1; i<=n; i++)
		{
			set[i] = i;
			rank[i] = 0;
		}
		Print();
	}

	void Union(int a, int b)
	{
		// cout << "Union: " << a << " " << b << endl;
		a = Find(a);
		b = Find(b);
		if (rank[a] == rank[b])
		{
			set[b] = a;
			rank[a]++;
		}
		else if(rank[a] < rank[b])
		{
			set[a] = b;
		}
		else if(rank[b] < rank[a])
		{
			set[b] = a;
			//cout << b << a<< endl;
		}
		Print();
	}

	int Find(int a)
	{
		// cout << "Find : " << a << endl;
		queue<int> q;
		while (set[a] != a)
		{
			q.push(a);
			a = set[a];
		}

		while (!q.empty())
		{
			set[q.front()] = a;
			q.pop();
		}
		Print();
		return a;
	}

	bool will_form_cycle(int a, int b)
	{
		return Find(a) == Find(b);
	}
};