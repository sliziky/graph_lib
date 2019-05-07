#pragma once
#include <algorithm>
#include <vector>
#include "colors.h"
template < typename T >
struct Vertex {
	Vertex( const T& k )
		: key( k )
		, color( color::w )
		, cost( -1 ) {}

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
	using adjacency_list = std::map<Vertex<T>, std::list<Vertex<T>> >;
	using type = T;
	using adj_list = void;

	Adjacency_list() = default;
	Adjacency_list(std::initializer_list<T> l) {}
	virtual ~Adjacency_list() = default;

	virtual void add_vertices( std::initializer_list<T> v ) {
		for (const auto& i : v) {
			_graph[i];
		}
	}
	virtual void add_vertex( const T& vertex ) {
		// if exists then add else do nothing
		_graph[ vertex ];
	}
	virtual void add_edge( const std::pair<T,T>& edge ) {
		auto& v = _graph[edge.first];
		v.push_back(edge.second);
	}
	
	virtual void add_edges( const std::vector<std::pair<T, T>> & edges) {
		for (const auto& v : edges) {
			add_edge(v);
		}
	}

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
			
		// if edge already exists
		if ( it_exists != neighbours.end() ) return;
		neighbours.emplace_back( to );
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
	}
	virtual void remove_edge( const T& from, const T& to ) {
		auto it = _graph.find( from );
		if ( it == _graph.end() ) return;

		auto &edges = it->second;
		edges.remove_if( [&]( const auto& ver ) { return ver.getKey() == to; } );
	}


	const adjacency_list& graph() const { return _graph; }
	adjacency_list& graph() { return _graph; }
	unsigned size() const { return _graph.size(); }
private:
	adjacency_list _graph;
};

class Adjacency_matrix {
public:
	using adj_matrix = std::vector<std::vector< int >>;
	using adj_mat = void;
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
