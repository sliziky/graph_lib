# Graph_Lib

Simple C++ graph library.

Includes ```Breadth-First Search```, ```Depth-First Search``` for included
graph representations - ```Adjacency_list```, ```Adjacency_matrix```


## Usage
```c++
Adjacency_list<int> graph;
graph.add_vertices({0,1,2,3,4});
graph.add_edges({
		         {0,1}, {0,2},
	             {1,2},
			     {2,0}, {2,3},
		         {3,3} 
			     });
dfs(graph, 2);

>>> 2 0 1 3

Adjacency_matrix graph2( 5 );
graph2.insert_edge( 0, 1 );
graph2.insert_edge( 0, 2 );
graph2.insert_edge( 1, 2 );
graph2.insert_edge( 2, 0 );
graph2.insert_edge( 2, 3 );
graph2.insert_edge( 3, 3 );

bfs( graph2, 2 );

>>> 2 0 3 1
```
