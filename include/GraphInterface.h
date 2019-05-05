#pragma once
#include <algorithm>
#include "colors.h"
template < typename T >
struct Vertex {
	Vertex( const T& k, color col = color::w, int c = -1 )
		: key( k )
		, color( col )
		, cost( c ) {}

	int getCost() const { return cost; }
	const T& getKey() const { return key; }
	T& getKey() { return key; }
	void setColor( color c ) { color = c; }
	color getColor() { return color; }

	int cost;
	color color;
	T key;
	bool operator<( const Vertex& v1 ) const {
		return key < v1.key;
	}
};
template < typename T >
class Adjacency_list {
public:
	using adj_list = std::map<Vertex<T>, std::list<Vertex<T>> >;
	using type = T;
	using bfs_adj_list = void;

	Adjacency_list() = default;
	virtual ~Adjacency_list() = default;

	virtual void add_vertex( const T& vertex ) {
		// if exists then add else do nothing
		_graph[ vertex ];
	virtual void add_edge( const T& from,
			       const T& to,
			      int cost = -1 ) {
		// if vertices does NOT exist return
		auto it = _graph.find( from );
		if ( it == _graph.end() ) return;

		auto it2 = _graph.find( to );
		if ( it2 == _graph.end() ) return;



		auto& neighbours = it->second;
		auto it_exists = std::find_if( neighbours.begin(),
									   neighbours.end(),
									   [&to]( Vertex<T>& vertex ) { return vertex.getKey() == to; } );
						neighbours.end(),
						[&to]( const Vertex& vertex ) { return vertex.getKey() == to; } );
		// if edge already exists
		if ( it_exists != neighbours.end() ) return;
		neighbours.emplace_back( to, color::w, cost );
	}
	virtual void remove_vertex( const T& vertex ) {
		// nothing to be removed
		if ( _graph.erase( vertex ) == 0 ) {
			return;
		}
		// remove all edges going TO vertex
		for ( auto& v : _graph ) {
			v.second.remove_if( [&]( const auto& ver ) { return ver.getKey() == vertex; } );
	}
	virtual void remove_edge( const T& from, const T& to ) {
		auto it = _graph.find( from );
		if ( it == _graph.end() ) return;

		auto &edges = it->second;
		edges.remove_if( [&]( const auto& ver ) { return ver.getKey() == to; } );
	}


	const adj_list& graph() const { return _graph; }
	unsigned size() const { return _graph.size(); }
private:
	adj_list _graph;
};

class Adjacency_matrix {
public:
	using adj_matrix = std::vector<std::vector< int >>;
	using bfs_adj_mat = void;
	Adjacency_matrix( int size )
		: _graph( size, std::vector<int>(size, -1) ) 
		, _size(size)
	{
	}
	virtual ~Adjacency_matrix() = default;

	virtual void insert_edge( int from, int to, int cost = 1 ) {
		if ( from < 0 || to < 0 ) return;
		_graph[ from ][ to ] = cost;
	}
	virtual void remove_edge( int from, int to ) {
		if ( from < 0 || to < 0 ) return;
		_graph[ from ][ to ] = -1;
	}

	virtual const adj_matrix& graph() const { return _graph; }
	virtual int size() const { return _size; }

private:
	int _size;
	adj_matrix _graph;
};
