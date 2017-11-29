#include <iostream>
using namespace std;
#define MAX_NODES_IN_GRAPH 50000

class MaxHeap // Max heap
{
	int a[MAX_NODES_IN_GRAPH];
	int n;
	int m[MAX_NODES_IN_GRAPH];

	void topToBottom(int index, int dist[])
	{
		if (index>=size() || index<0)
		{
			//cerr << " topToBottom : Out of bound" << endl;
			return;
		}

		//cout << "top to bottom index "<< index << endl;
		int left = 2*index+1, right = 2*index+2;
		if (left>=size())
			return;

		int cmpIndex = left;
		if (right < size())
		{
			if (dist[a[right]] > dist[a[left]])
				cmpIndex = right;
		}//
		//cout << "cmpIndex = " << cmpIndex << " val " << dist[a[cmpIndex]]<< endl;
		if (dist[a[index]] < dist[a[cmpIndex]])
		{//
			//cout << "swapping" << endl;
			int temp = a[index];
			a[index] = a[cmpIndex];
			a[cmpIndex] = temp;
			int t = m[a[index]];
			m[a[index]] = m[a[cmpIndex]];
			m[a[cmpIndex]] = t;
			topToBottom(cmpIndex, dist);
		}
	}

	void bottomToTop(int index, int dist[])
	{
		if (index>=size() || index<0)
		{
			//cerr << " bottomToTop : Out of bound" << endl;
			return;
		}
		//cout << "bottom to top : index " << index << endl;
		int parent = (index-1) / 2;
		//cout << " parent = " << parent << " val " << dist[a[parent]]<< endl; 
		if (dist[a[parent]]< dist[a[index]])
		{
			//cout << "swapping" << endl;
			int temp = a[index];
			a[index] = a[parent];
			a[parent] = temp;

			int t = m[a[index]];
			m[a[index]] = m[a[parent]];
			m[a[parent]] = t;
			bottomToTop(parent, dist);
		}
	}

public:

	MaxHeap()
	{
		// cout << "created heap" << endl;
		n = 0;
		for (int i=0; i<MAX_NODES_IN_GRAPH; i++)
		{
			a[i] = 0;
			m[i] = -1;
		}
	}

	inline int size() { return n; }

	void insert(int x, int dist[])
	{
		a[size()] = x;
		m[x] = size();
		n++;
		bottomToTop(n-1, dist);
	}

	void delet(int index, int dist[])
	{
		if (index >= size() || index < 0)
		{
			// cout << index << " " << size() << endl;
			// cout << "delet: Out of bound " << endl;			
			// cerr << "delet: Out of bound " << endl;
			return;
		}
		m[a[size()-1]] = index;
		m[a[index]] = -1;
		a[index] = a[size()-1];
		n--;
		topToBottom(index, dist);
		bottomToTop(index, dist);
	}

	void delet(int dist[])
	{
		// cout << "deleting top" << endl;
		if (!empty())
			delet(0, dist);
		else
			cerr << " HEAP EMPTY " << endl;
	}

	void update(int x, int dist[])
	{
		// cout << "Heap: " << x << endl;;
		if (m[x] != -1)
		{
			delet(m[x], dist);
		}
		insert(x, dist);
	}

	inline bool empty() { return size() == 0; }

	inline int top()
	{
		if (!empty())
			return a[0];
		else
			cerr << " HEAP EMPTY " << endl;
		return 0;
	}

	void Print(int dist[])
	{

		for (int i=0; i<n; i++)
		{
			//cout << "Heap[" << i << "] = {node = " << a[i] << ", distance = " << \
			dist[a[i]] << ", mappedToIndex = " << m[a[i]] << endl;
		}
	}
};


class MaxHeapForEdges // Max heap
{
	vector<pair<int, pair<int, int>>> a;
	int n;

	void topToBottom(int index)
	{
		if (index>=size() || index<0)
		{
			// cerr << " topToBottom : Out of bound" << endl;
			return;
		}

		//cout << "top to bottom index "<< index << endl;
		int left = 2*index+1, right = 2*index+2;
		if (left>=size())
			return;

		int cmpIndex = left;
		if (right < size())
		{
			if (a[right].first > a[left].first)
				cmpIndex = right;
		}//
		//cout << "cmpIndex = " << cmpIndex << " val " << dist[a[cmpIndex]]<< endl;
		if (a[index].first < a[cmpIndex].first)
		{//
			//cout << "swapping" << endl;
			pair<int, pair<int, int>> temp = a[index];
			a[index] = a[cmpIndex];
			a[cmpIndex] = temp;
			topToBottom(cmpIndex);
		}
	}

	void bottomToTop(int index)
	{
		if (index>=size() || index<0)
		{
			//cerr << " bottomToTop : Out of bound" << endl;
			return;
		}
		//cout << "bottom to top : index " << index << endl;
		int parent = (index-1) / 2;
		//cout << " parent = " << parent << " val " << dist[a[parent]]<< endl; 
		if (a[parent].first < a[index].first)
		{
			//cout << "swapping" << endl;
			pair<int, pair<int, int>> temp = a[index];
			a[index] = a[parent];
			a[parent] = temp;
			bottomToTop(parent);
		}
	}

public:

	MaxHeapForEdges()
	{
		// cout << "created heap" << endl;
		n = 0;
	}

	inline int size() { return n; }

	void insert(pair<int, pair<int, int>> x)
	{
		// cout << "inserting " << x << endl;
		a.push_back(x);
		n++;
		bottomToTop(n-1);
	}

	void delet(int index)
	{
		if (index > size() || index < 0)
		{
			//cout << index << " " << size() << endl;
			//cout << "delet: Out of bound " << endl;			
			//cerr << "delet: Out of bound " << endl;
			return;
		}
		// cout << "deleting Heap[" << index <<"] =" << a[index] << endl;
		a[index] = a[size()-1];
		n--;
		topToBottom(index);
		a.pop_back();
	}

	void delet()
	{
		// cout << "deleting top" << endl;
		if (!empty())
			delet(0);
		else
			cerr << " HEAP EMPTY " << endl;
	}

	inline bool empty() { return size() == 0; }

	inline pair<int, pair<int, int>> top()
	{
		if (!empty())
			return a[0];
		else
			cerr << " HEAP EMPTY " << endl;
		return make_pair(0, make_pair(0,0));
	}

	void Print()
	{

		for (int i=0; i<n; i++)
		{
			//cout << "Heap[" << i << "] = {node = " << a[i] << ", distance = " << \
			dist[a[i]] << ", mappedToIndex = " << m[a[i]] << endl;
		}
	}
};
