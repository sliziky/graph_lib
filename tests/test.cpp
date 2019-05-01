#include "pch.h"
#include "../graph_library/Graph.h"

template < typename Container, typename T >
bool map_contains( const Container& graph,
				   const T& item ) {
	auto it = graph.find( item );
	return it != graph.end();
}

template < typename Container, typename T >
bool edge_exists( const Container& map, const T& from,
				  const T& to ) {
	auto it = map.find( from );
	auto it2 = map.find( to );
	if ( it == map.end() || it2 == map.end() ) return false;
	return std::find_if( it->second.begin(), it->second.end(), [&]( const auto& pair ) { return pair.first == to; } ) != it->second.end();
}


TEST( GraphTest, AddVertex ) {
	Graph<int> graph {};

	std::vector<bool> vertices = { 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0 };
	for ( int i = 0; i < vertices.size(); ++i ) {
		if ( vertices[ i ] ) {
			graph.add_vertex( i );
		}
	}
	for ( int i = 0; i < vertices.size(); ++i ) {
		if ( vertices[ i ] ) {
			EXPECT_TRUE( map_contains( graph.graph(), i ) );
		}
		else {
			EXPECT_FALSE( map_contains( graph.graph(), i ) );
		}
	}
	EXPECT_EQ( graph.size(), 6 );
}
//
TEST( GraphTest, AddEdge ) {
	Graph<int> graph {};
	std::vector<int> vertices { 1, 2, 3, 4, 5, 6, 7, 8 };
	for ( const auto& v : vertices ) graph.add_vertex( v );

	std::vector<std::pair<int, int>> edges = {
		{1, 2}, 
		{2, 4}, {2, 3}, {2,1},
		{4, 1}, 
		{5, 2}, 
		{8, 4}
	};
	for ( const auto& pair : edges ) {
		graph.add_edge( pair.first, pair.second );
	}

	for ( int i = 0; i < vertices.size() + 1; ++i ) {
		for ( int j = 0; j < vertices.size() + 1; ++j ) {
			auto e = std::make_pair( i, j);
			if ( std::find( edges.begin(), edges.end(), e ) != edges.end() ) {
				EXPECT_TRUE( edge_exists( graph.graph(), i, j ) );
			}
			else {
				EXPECT_FALSE( edge_exists( graph.graph(), i, j ) );
			}
		}
	}
	EXPECT_EQ( graph.size(), 8 );
}

TEST( GraphTest, RemoveVertex ) {
	Graph<int> graph {};
	std::vector<int> vertices { 1, 2, 3, 4, 5, 6, 7, 8 };
	for ( const auto& v : vertices ) graph.add_vertex( v );

	std::vector<std::pair<int, int>> edges = {
		{1, 2},
		{2, 4}, {2, 3}, {2,1},
		{4, 1},
		{5, 2},
		{8, 4}
	};
	for ( const auto& pair : edges ) {
		graph.add_edge( pair.first, pair.second );
	}
	EXPECT_EQ( graph.size(), 8 );
	graph.remove_vertex( 2 );
	EXPECT_EQ( graph.size(), 7 );
	EXPECT_TRUE(map_contains(graph.graph(), 1));
	EXPECT_FALSE( map_contains( graph.graph(), 2 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 3 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 4 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 5 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 6 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 7 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 8 ) );

	EXPECT_FALSE( edge_exists( graph.graph(), 5, 2 ) );
	EXPECT_FALSE( edge_exists( graph.graph(), 1, 2 ) );
	EXPECT_FALSE( edge_exists( graph.graph(), 2, 4 ) );

}

TEST( GraphTest, removeEdge ) {
	Graph<int> graph {};
	std::vector<int> vertices { 1, 2, 3, 4, 5, 6, 7, 8 };
	for ( const auto& v : vertices ) graph.add_vertex( v );

	std::vector<std::pair<int, int>> edges = {
		{1, 2},
		{2, 4}, {2, 3}, {2,1},
		{4, 1},
		{5, 2},
		{8, 4}
	};
	for ( const auto& pair : edges ) {
		graph.add_edge( pair.first, pair.second );
	}
	graph.remove_edge( 2, 4 );
	EXPECT_TRUE( map_contains( graph.graph(), 1 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 2 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 3 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 4 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 5 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 6 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 7 ) );
	EXPECT_TRUE( map_contains( graph.graph(), 8 ) );

	EXPECT_TRUE( edge_exists( graph.graph(), 5, 2 ) );
	EXPECT_TRUE( edge_exists( graph.graph(), 1, 2 ) );
	EXPECT_FALSE( edge_exists( graph.graph(), 2, 4 ) );
	EXPECT_EQ( graph.size(), 8 );
}
