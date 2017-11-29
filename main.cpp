#include "Graph.h"
#include "Graph_generator.cpp"
#include <ctime>
#include <string>

class MeasureTime
{
	clock_t begin, end;
	double elapsed_secs;
	string operation;
	ofstream &report, &answer, &csv_report;
public:
	MeasureTime(string op, ofstream &_report, ofstream &_answer, ofstream &_csv_report):report(_report), answer(_answer), csv_report(_csv_report)
	{
		answer << "\n\nstart: " << op << endl;
		operation = op;
		begin = clock();
	}

	double getTime()
	{
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//csv_report << elapsed_secs << ", ";
		answer << " Time reqd for " << operation << " = "<< elapsed_secs << endl;
		report << " Time reqd for " << operation << " = "<< elapsed_secs << endl;
		cout << " Time reqd for " << operation << " = "<< elapsed_secs << endl;
		return elapsed_secs;
	}

	~MeasureTime()
	{
		
	}
};

int main()
{

	// Graph G;
	// G.PrintGraph();
	//return 0;
	// int nodes = 10;
	/*cout << "Naive" << endl;

	int source = 435; //%nodes;
	int destination = 67; //5567%nodes;
	Path dijkstraShortestPathNaive = G.DijkstraShortestPathNaive(source, destination);
	for (int i=0; i<dijkstraShortestPathNaive.order.size(); i++)
		cout << dijkstraShortestPathNaive.order[i] << " ";
	cout << endl;
	cout << "DijkstraShortestPathNaive " << dijkstraShortestPathNaive.distance << endl;

	//----
	// cout << "Heap" << endl;
	Path dijkstraShortestPathHeap = G.DijkstraShortestPathHeap(source, destination);
	for (int i=0; i<dijkstraShortestPathHeap.order.size(); i++)
		cout << dijkstraShortestPathHeap.order[i] << " ";
	cout << endl;
	cout << "DijkstraShortestPathHeap " << dijkstraShortestPathHeap.distance << endl;

	if (dijkstraShortestPathNaive.distance != dijkstraShortestPathHeap.distance)
	{
		cout << "ERROR" << endl;
		G.PrintGraph();
	}
	*/
	//----
	/*
	MSTPath kruskalsMinimumSpanningTree = G.KruskalMinimumSpanningTree();
	for (int i=0; i<kruskalsMinimumSpanningTree.edges.size(); i++)
		cout << kruskalsMinimumSpanningTree.edges[i].first << " " << kruskalsMinimumSpanningTree.edges[i].second << endl;
	cout << endl;
	cout << kruskalsMinimumSpanningTree.weight << endl;

*/
	int num_graphs = 1;
	int num_pairs = 1;
	ofstream csv_report;
	csv_report.open("Final_report_Dense_graph.csv");
	csv_report << "Graph_num, source, destination, for_mst_generation, naive_approach, heap_approach, mst_approach" << endl;
	for (int graphs = 0; graphs<num_graphs; graphs++)
	{
		ofstream graph_gen;
		graph_gen.open("Dense_graph_"+to_string(graphs+1)+".txt");
		
		ofstream report, answer;
		report.open("report_Dense_graph"+to_string(graphs+1)+".txt");
		answer.open("answer_Dense_graph"+to_string(graphs+1)+".txt");

		int nodes = 5000;
	
		#if 1
		GraphGenerator x(nodes, true, 8, -1, true, false, 1000, 10);
		
		vector<pair<int, pair<int, int>>> graph;
		{
			MeasureTime m(string("Graph Generation"), graph_gen, graph_gen, graph_gen);
			cout << "here" << endl;
			graph = x.generate();
			m.getTime();
		}
		int edges = graph.size();
		// cout << "Edges = " << edges << endl;
		Graph temp(0, 0);
		Graph &G = temp;
		{
			MeasureTime m("Creating graph", graph_gen, graph_gen, graph_gen);
			Graph actualGraph(nodes, edges, graph);
			G = actualGraph;
			m.getTime();
		}
		
		{
			MeasureTime m("Saving the graph to file", graph_gen, graph_gen, graph_gen);
			G.PrintGraph(graph_gen);
			m.getTime();	
		}
		#else
		Graph G;
		//G.PrintGraph();
		// cout << "Naive" << endl;
	 	#endif

		double kmst_gen_time;
	 	MSTGraph kruskalsMaximumSpanningTree;
		{
			MeasureTime m("Finding maximum spanning tree", report, answer, csv_report);
			kruskalsMaximumSpanningTree = G.KruskalMaximumSpanningTree();
			kmst_gen_time = m.getTime();
		}
		
		
		for (int i=0; i<kruskalsMaximumSpanningTree.path.edges.size(); i++)
			answer << "<" << kruskalsMaximumSpanningTree.path.edges[i].second.first << ", " \
				<< kruskalsMaximumSpanningTree.path.edges[i].second.second << ">, ";
		answer << endl;
		answer << kruskalsMaximumSpanningTree.path.weight << endl;
		

		for (int pairs = 0; pairs<num_pairs	; pairs++)
		{	
			csv_report << graphs+1 << ", ";
			int source = rand()%(nodes) + 1;
			int destination = rand()%(nodes) + 1;
			report << "Number of nodes in graph = " << nodes << endl;
			report << "This is a Dense graph. All nodes are connected to approximately 20 percent of other nodes" <<endl;
			report << "Number of edges in graph = " << edges << endl;
			while (source == destination)
			{
				destination = rand()%(nodes) + 1;
			}
			report << "Source = " << source << " Destination = " << destination << endl;
			csv_report << source << ", " << destination << ", " << kmst_gen_time << ", ";

		 	MBPPath maximumBandwidthPathNaive;
		 	{
		 		MeasureTime m("Naive Dijkstra's approach", report, answer, csv_report);
		 		maximumBandwidthPathNaive = G.MaximumBandwidthPathNaive(source, destination);
		 		double naive_time = m.getTime();
		 		csv_report << naive_time << ", ";
		 	}
			
			vector<int> &naive = maximumBandwidthPathNaive.order;
			for (int i=0; i<naive.size(); i++)
				answer << naive[i] << " ";
			answer << endl;
			answer << maximumBandwidthPathNaive.bandwidth << endl;

			MBPPath maximumBandwidthPathHeap;
			{
				MeasureTime m("Dijkstra's Heap approach", report, answer, csv_report);
				maximumBandwidthPathHeap = G.MaximumBandwidthPathHeap(source, destination);
				double heap_time = m.getTime();
		 		csv_report << heap_time << ", ";
			}
			
			for (int i=0; i<maximumBandwidthPathHeap.order.size(); i++)
				answer << maximumBandwidthPathHeap.order[i] << " ";
			answer << endl;
			answer << maximumBandwidthPathHeap.bandwidth << endl;

			if (maximumBandwidthPathHeap.bandwidth != maximumBandwidthPathNaive.bandwidth)
			{
				cerr << " \n\n\nMinute ERROR : heap" << endl;

			}

			MBPPath kruskalsMaximumBandwidthPath;
			{
				MeasureTime m("Kruskal spanning tree approach", report, answer, csv_report);
				kruskalsMaximumBandwidthPath = G.KruskalMaxBandwidthPath(source, destination, kruskalsMaximumSpanningTree.mst);
				double kruskal_time = m.getTime();
		 		csv_report << kruskal_time << ", ";
			}

			for (int i=0; i<kruskalsMaximumBandwidthPath.order.size(); i++)
				answer << kruskalsMaximumBandwidthPath.order[i] << " ";
			answer << endl;
			answer << kruskalsMaximumBandwidthPath.bandwidth << endl;

			if (kruskalsMaximumBandwidthPath.bandwidth != maximumBandwidthPathNaive.bandwidth)
			{
				cerr << " \n\n\nMinute ERROR : kruskal" << endl;
			}
			csv_report << endl;

			report << "\n\n\n" << endl;
			answer << "\n\n\n" << endl;
		}
	}

	return 0;
}
