# Graph_Lib

Simple C++ graph library.

So far includes Graph Interface, functions such as BFS, DFS etc are about to be
added very soon


## Usage

Include ```GraphI.h```
``` 
Graph<int> graph;
graph.add_vertex(4);
graph.add_vertex(3);
graph.add_edge(3, 4, 2); // adds edge from 3 to 4 with cost 2
BFS(graph, 3); // starts BFS from vertix 3
```

