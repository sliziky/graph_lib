// graph_library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include "Graph.h"
#include "GraphInterface.h"
#include "colors.h"
template < typename T >
void print_vec( const std::vector<T>& vec ) {
	for ( const auto& x : vec ) std::cout << x << " ";
	std::cout << std::endl;
}


template < typename Graph >
typename Graph::bfs_adj_list bfs( const Graph& graph, const Vertex< typename Graph::type >& root ) {
	std::queue<Vertex < typename Graph::type >> queue {};
	//root.setColor( color::g );
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
typename Graph::bfs_adj_mat bfs( const Graph& graph, int vertex ) {
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
		//for ( auto& n : neighbours[  ] ) {
		//	if ( n.getColor() == color::w ) {
		//		n.setColor( color::g );
		//		queue.push( Vertex( n ) );
		//	}
		//	node.setColor( color::b );
		//}
	}
}

template < typename T >
bool vec_contains( const std::vector<T>& vec, const T& item ) {
	return std::find( vec.begin(), vec.end(), item ) != vec.end();
}

int main()
{
	//Graph<int> graph;
	//graph.add_vertex( 2 );
	//graph.add_vertex( 2 );
	////graph.add_vertex( 2 );
	////graph.add_vertex( 3 );
	//graph.add_vertex( 5 );
	//graph.add_edge( 2, 5 );
	Adjacency_matrix mat( 5 );
	mat.insert_edge( 1, 1 );
	mat.insert_edge( 1, 3 );
	mat.insert_edge( 2, 0 );
	mat.insert_edge( 2, 2 );
	mat.insert_edge( 1, 2 );

	bfs( mat, 2 );

	return 0;
}
