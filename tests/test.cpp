#include "pch.h"
#include "../graph_library/Graph.h"

template < typename Container, typename T >
bool map_contains( const Container & graph,
			   const T& item ) {
	auto it = graph.find( item );
	return it != graph.end();
}

template < typename Container, typename T >
bool edge_exists( const Container& map,const T& from,
				  const T& to) {
	auto it = 
	return std::find( vec.begin(), vec.end(), item ) != vec.end();
}


TEST(GraphTest, AddVertex) {
	Graph<int> graph {};
	graph.add_vertex( 2 );
	graph.add_vertex( 2 );
	graph.add_vertex( 2 );
	graph.add_vertex( 3 );
	graph.add_vertex( 6 );
	auto graph_map = graph.graph();
	EXPECT_TRUE( map_contains( graph_map, 2) );
	EXPECT_TRUE( map_contains( graph_map, 3 ) );
	EXPECT_TRUE( map_contains( graph_map, 6 ) );
	EXPECT_FALSE( map_contains( graph_map, 0 ) );
	EXPECT_FALSE( map_contains( graph_map, 1 ) );
}
//
//TEST( GraphTest, AddEdge ) {
//	Graph<int> graph {};
//	graph.add_vertex( 2 );
//	graph.add_vertex( 2 );
//	graph.add_vertex( 2 );
//	graph.add_vertex( 3 );
//	graph.add_vertex( 6 );
//	EXPECT_FALSE( vec_contains( graph._graph.at( 2 ), 1 ) );
//	graph.add_edge( 2, 3 );
//	EXPECT_TRUE( vec_contains( graph._graph.at( 2 ), 3 ) );
//	graph.add_edge( 8, 3 ); // vertex 8 does not exist
//	graph.add_edge( 2, 1 ); // vertex 1 does not exist
//	graph.add_edge( 2, 9 ); // same here
//	EXPECT_FALSE( vec_contains( graph._graph.at( 2 ), 1 ) );
//	EXPECT_THROW( vec_contains( graph._graph.at( 8 ), 1 ), std::out_of_range );
//	EXPECT_FALSE( vec_contains( graph._graph.at( 2 ), 9 ) );
//
//
//
//
//
//}


