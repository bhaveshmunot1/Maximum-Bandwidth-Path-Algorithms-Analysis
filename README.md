# Maximum-Bandwidth-Path-Algorithms-Analysis

This project makes a comparative analysis of various algorithms of finding maximum bandwidth path in a given graph or a network.

At this moment, there are 3 algorithms that are used for the comparison.
1. Approach similar to Dijkstra's algorithm for shortest path. This approach finds the next node to explore by scanning the entire array. Theoratically, the time complexity of this approach is O(n^2).
2. Approach similar to Dijkstra's algorithm for shortest path. This approach uses heap for finding the next node to explore. Theoratically, the time complexity for this is O(n*log(n)).
3. Approach which finds maximum spanning tree using Kruskal's algorithm and then finds the path using simple BFS. The time complexity of this is also O(n*log(n)).

Results of this analysis were quiet interesting. Insterested readers can have a look at it in "report.pdf".
