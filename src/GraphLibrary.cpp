// graph_library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <type_traits>
#include "../include/Graph.h"
#include "../include/GraphInterface.h"
#include "../include/colors.h"

/**
 * Runs BFS for given Adjacency List Graph from given vertex
 *
 * If Graph::type is int, then in order to reach
 * O(V+E) time complexity we use std::vector
 * for storing visited vertices, std::set otherwise 
 *
 * @tparam Graph the type of graph
 * @param graph a given Adj_list graph
 * @param root a vertex to start BFS from
 */
template < typename Graph >
typename 
Graph::adj_list bfs( const Graph& graph, 
	 				 Vertex< typename Graph::type > root ) {
	if constexpr ( std::is_integral_v< typename Graph::type > ) {
		std::vector< int > visited ( graph.size(), 0 );
		bfs_util( graph, root.getKey(), visited );
	}
	else {
		std::set< typename Graph::type > visited;
		bfs_util( graph, root, visited );
	}
}


template < typename Graph >
typename
Graph::adj_list bfs_util( const Graph& graph,
						  const Vertex<int>& vertex,
						  std::vector<int>& visited )
{
	std::queue< Vertex<int> > queue;
	queue.push( vertex );
	visited[ vertex.getKey() ] = 1;
	while ( !queue.empty() ) {
		auto& v = queue.front();
		std::cout << v.getKey() << std::endl;
		const auto& neighbours = graph.graph().at( v );
		queue.pop();
		for ( const auto& neighbour : neighbours ) {
			const int key = neighbour.getKey();
			if (visited[ key ] == 0)
			{
				visited[ key ] = 1;
				queue.push( neighbour );
			}
		}
	}
}

template < typename Graph >
typename
Graph::adj_list bfs_util( const Graph& graph,
						  const Vertex< typename Graph::type >& vertex,
						  std::set< typename Graph::type >& visited ) {

	std::queue< typename Graph::type > queue {};
	auto key = vertex.getKey();
	queue.push( key );
	visited.insert( key );
	while ( !queue.empty() ) {
		auto& v = queue.front();
		std::cout << v << std::endl;
		const auto& neighbours = graph.graph().at( v );
		queue.pop();
		for ( const auto& n : neighbours ) {
			const auto& key = n.getKey();
			if ( visited.find( key ) == visited.end()) {
				visited.insert( key );
				queue.push( key );
			}
		}
	}
}


/**
 * Runs BFS for given Matrix Graph from given vertex
 * 
 * @tparam Graph the type of graph
 * @param graph a given graph of type Adj_mat
 * @param vertex a vertex to start BFS from
 */
template < typename Graph >
typename
Graph::adj_mat bfs( const Graph& graph, int vertex )
{
	std::vector< int > visited( graph.size(), 0 );
	std::queue<int> queue;
	queue.push( vertex );
	visited[ vertex ] = 1;
	while ( !queue.empty() ){
		auto v = queue.front();
		std::cout << v << std::endl;
		queue.pop();
		const auto& neighbours = graph.graph()[ v ];
		for ( int i = 0; i < graph.size(); ++i ) {
			if ( neighbours[ i ] == 1 && visited[ i ] == 0) {
				queue.push( i );
				visited[ i ] = 1;
			}
		}
	}
}



/**
 * Runs DFS for given Graph from given vertex
 *
 * If Graph::type is int, then in order to reach
 * O(V+E) time complexity we use std::vector
 * for storing visited vertices, std::set otherwise 
 *
 * @tparam Graph the type of graph
 * @param graph a given graph - Adj_list or Adj_mat
 * @param root a vertex to start DFS from
 */
template < typename Graph >
typename 
Graph::adj_list dfs( const Graph& graph, 
					 Vertex< typename Graph::type > root ) {

	if ( graph.empty() ) { std::cout << "Empty graph \n"; return; }
	std::ostringstream os;

	// for int type
	if constexpr ( std::is_integral_v< typename Graph::type > ) {
		std::vector< int > visited( graph.size(), 0 );
		dfs_util( graph, root, visited, os );
	}
	// for other types
	else { 
		std::set< typename Graph::type > visited;
		dfs_util( graph, root, visited, os );
	}

	std::cout << os.str();
}

template < typename Graph >
typename 
Graph::adj_list dfs_util( const Graph& graph,
						  const Vertex< typename Graph::type >& vertex,
						  std::set< typename Graph::type >& visited,
						  std::ostringstream& os) {

	visited.insert( vertex.getKey() );
	const auto& neighbours = graph.graph().at( vertex.getKey() );
	os << vertex.getKey() << " ";
	for ( const auto& neighbour : neighbours  ) {
		if ( visited.find( neighbour.getKey() ) == visited.end()) {
			dfs_util( graph, neighbour, visited, os );
		}
	}
}


// specialized for int vertices
template < typename Graph >
typename
Graph::adj_list dfs_util( const Graph& graph,
						  const Vertex< int >& vertex,
						  std::vector< int >& visited,
						  std::ostringstream& os ) {

	int key = vertex.getKey();
	visited[ key ] = 1;
	const auto& neighbours = graph.graph().at( key );
	os << key << " ";
	for ( const auto& neighbour : neighbours ) {
		if ( visited[ neighbour.getKey() ] == 0 ) {
			dfs_util( graph, neighbour, visited, os );
		}
	}
}

template < typename Graph >
typename
Graph::adj_mat dfs( const Graph& graph,
                    int root )
{
	std::vector< int > visited ( graph.size(), 0 );
	dfs_util( graph, root, visited );
}

template < typename Graph >
typename
Graph::adj_mat dfs_util( const Graph& graph,
						 int vertex,
						 std::vector< int >& visited)
{
	visited[ vertex ] = 1;
	const auto& neighbours = graph.graph()[ vertex ];
	std::cout << vertex << "\n";
	for (int i = 0; i < graph.size(); ++i ) {
		if (graph.path_exists(vertex, i) && visited[i] == 0 ){
			dfs_util( graph, i, visited );
		}
	}
}

int main()
{
	Adjacency_list<std::string> graph;
	graph.add_vertices({"A","B","C","D","E"});
	graph.add_edges({
					  {"A","B"}, {"A","C"},
					  {"B","C"},
					  {"C","A"}, {"C","D"},
					  {"D","D"} 
					});

	Adjacency_list<int> g;
	g.add_vertices({1,2,3,4,5});
	g.add_edges({{0,1},{0,2},{1,3},{1,5},{2,2},{2,4},{4,5}});
	

	dfs(g, 0);
	return 0;
}
