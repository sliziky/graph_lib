// graph_library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <algorithm>
#include "../Graph.h"
#include "../GraphInterface.h"
#include "../colors.h"

template < typename T >
void print_vec( const std::vector<T>& vec ) {
	for ( const auto& x : vec ) std::cout << x << " ";
	std::cout << std::endl;
}


template < typename Graph >
typename Graph::adj_list bfs( const Graph& graph, const Vertex< typename Graph::type >& root ) {
	std::queue<Vertex < typename Graph::type >> queue {};
	queue.push( root );
	auto neighbours = graph.graph();
	while ( !queue.empty() ) {
		auto node = queue.front();
		std::cout << node.getKey() << std::endl;
		queue.pop();
		for ( auto& n : neighbours[ node.getKey() ] ) {
			if ( n.getColor() == color::w ) {
				n.setColor( color::g );
				queue.push( Vertex(n) );
			}
			node.setColor( color::b );
		}
	}
}

template < typename Graph >
typename Graph::adj_mat bfs( const Graph& graph, int vertex ) {
	std::queue<int> queue {};
	queue.push( vertex );
	std::vector<bool> visited( graph.size() );
	visited[ vertex ] = true;
	auto matrix = graph.graph();
	while ( !queue.empty() ) {
		auto node = queue.front();
		std::cout << node << std::endl;
		queue.pop();
		for ( unsigned i = 0; i < matrix[ node ].size(); ++i ) {
			if ( matrix[ node ][ i ] == 1 && !visited[ i ]) {
				visited[ i ] = true;
				queue.push( i );
			}
		}
	}
}

template < typename Graph >
typename Graph::adj_list dfs( Graph& graph, 
							 Vertex< typename Graph::type > root ) {
	std::vector<bool> visited (graph.size(), false);
	dfs_util(graph, root, visited);
}
template < typename Graph >
typename Graph::adj_list dfs_util( Graph& graph,
							  Vertex< typename Graph::type >& root,
							  std::vector<bool>& visited ) {
	auto& neighbours = graph.graph();
	visited[ root.getKey() ] = true;
	for ( auto& n : neighbours[ root.getKey() ] ) {
		if ( !visited[ n.getKey() ] ) {
			dfs_util( graph, n, visited );
		}
	}
}

template < typename T >
bool vec_contains( const std::vector<T>& vec, const T& item ) {
	return std::find( vec.begin(), vec.end(), item ) != vec.end();
}

int main()
{
	Adjacency_list<int> graph;
	graph.add_vertex( 0 );
	graph.add_vertex( 1 );
	graph.add_vertex( 2 );
	graph.add_vertex( 3 );
	graph.add_vertex( 4 );
	
	
	graph.add_edge( 0, 1 );
	graph.add_edge( 0, 2 );
	graph.add_edge( 1, 2 );
	graph.add_edge( 2, 0 );
	graph.add_edge( 2, 3 );
	graph.add_edge( 3, 3 );

	Adjacency_matrix mat( 5 );
	mat.insert_edge( 1, 1 );
	mat.insert_edge( 1, 3 );
	mat.insert_edge( 2, 0 );
	mat.insert_edge( 2, 2 );
	mat.insert_edge( 1, 2 );
	dfs( graph, 2 );

	return 0;
}
