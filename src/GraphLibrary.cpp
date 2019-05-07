// graph_library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
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
		std::cout << node << "\n";
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
typename 
Graph::adj_list dfs( const Graph& graph, 
							 Vertex< typename Graph::type > root ) {
	std::set< Graph::type > visited;
	std::ostringstream os;
	os << "Adj_list DFS ";
	dfs_util( graph, root, visited, os);
	std::cout << os.str();
}

template < typename Graph >
typename 
Graph::adj_list dfs_util( const Graph& graph,
						  const Vertex< typename Graph::type >& vertex,
						  std::set< typename Graph::type >& visited,
						  std::ostringstream& os) {


	visited.insert(vertex.getKey());
	const auto& neighbours = graph.graph().at(vertex.getKey());
	os << vertex.getKey() << " ";
	for ( const auto& v : neighbours  ) {
		if ( visited.find(v.getKey()) == visited.end()) {
			dfs_util( graph, v, visited, os );
		}
	}
}

template < typename Graph >
typename
Graph::adj_mat dfs( const Graph& graph,
                    int root )
{
	std::set< int > visited;
	dfs_util( graph, root, visited );
}

template < typename Graph >
typename
Graph::adj_mat dfs_util( const Graph& graph,
						 int vertex,
						 std::set< int >& visited)
{
	visited.insert(vertex);
	const auto& neighbours = graph.graph()[vertex];
	std::cout << vertex << "\n";
	for (int i = 0; i < graph.size(); ++i ) {
		if (neighbours[i] == 1 && visited.find(i) == visited.end() ){
			dfs_util(graph, i, visited);
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
	graph.add_verteces({0,1,2,3,4});
	graph.add_edges({
					  {0,1}, {0,2},
					  {1,2},
					  {2,0}, {2,3},
					  {3,3} 
					});
	Adjacency_matrix mat( 5 );
	mat.insert_edge( 0, 1 );
	mat.insert_edge( 0, 2 );
	mat.insert_edge( 1, 2 );
	mat.insert_edge( 2, 0 );
	mat.insert_edge( 2, 3 );
	mat.insert_edge( 3, 3 );

	dfs( graph, 2 );

	return 0;
}
