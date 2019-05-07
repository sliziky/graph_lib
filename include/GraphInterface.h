#pragma once
#include <algorithm>
#include <vector>
#include "colors.h"

template < typename T >
struct Vertex {
	Vertex( const T& k )
		: key( k )
	{}

	
	const T& getKey() const { return key; }
	T& getKey() { return key; }

	T key;
	bool operator<( const Vertex& v1 ) const {
		return key < v1.key;
	}
};

template < typename T >
class Adjacency_list {
public:
	using adjacency_list = std::map< Vertex<T>, std::list<Vertex<T>> >;
	using type = T;
	using adj_list = void;
	// i guess the compiler would generate the same code as ours
	Adjacency_list() = default;
	Adjacency_list( std::initializer_list<T> l ) {}
	Adjacency_list( const Adjacency_list& other )
		: _graph( other._graph )
	{}
	Adjacency_list( Adjacency_list&& other ) noexcept
		: _graph( std::move(other._graph) )
	{}
	Adjacency_list& operator=( Adjacency_list adj_l ) {
		swap( *this, adj_l );
		return *this;
	}
	~Adjacency_list() = default;

	void add_vertex( const T& vertex ) {
		// if exists then add else do nothing
		_graph[ vertex ];
	}

	void add_vertices( std::initializer_list<T> vertices ) {
		for ( const auto& vertex : vertices ) {
			add_vertex( vertex );
		}
	}

	void add_vertices( const std::vector<T>& vertices ) {
		for ( const auto& vertex : vertices ) {
			add_vertex( vertex );
		}
	}

	void add_edge( const std::pair<T,T>& edge ) {
		auto& v = _graph[ edge.first ];
		v.push_back(edge.second);
	}
	
	void add_edges( const std::vector<std::pair<T, T>> & edges ) {
		for ( const auto& edge : edges ) {
			add_edge( edge );
		}
	}

	void remove_vertex( const T& vertex ) {
		// nothing to be removed
		if ( _graph.erase( vertex ) == 0 ) {
			return;
		}
		// remove all edges going TO vertex
		for ( auto& v : _graph ) {
			v.second.remove_if( [&]( const auto& ver ) { return ver.getKey() == vertex; } );
		}
	}
	void remove_edge( const T& from, const T& to ) {
		auto it = _graph.find( from );
		if ( it == _graph.end() ) return;

		auto &edges = it->second;
		edges.remove_if( [&]( const auto& ver ) { return ver.getKey() == to; } );
	}

	void swap( Adjacency_list& first, Adjacency_list& sec ) {
		using std::swap;
		swap( first._graph, sec._graph );
	}

	const adjacency_list& graph() const { return _graph; }
	adjacency_list& graph() { return _graph; }
	unsigned size() const { return _graph.size(); }
	bool empty() const { return size() == 0; }

private:
	adjacency_list _graph;
};


class Adjacency_matrix {
public:
	using adj_matrix = std::vector<std::vector< int >>;
	using adj_mat = void;
	
	Adjacency_matrix( int size )
		: _graph( size, std::vector<int>(size, 0) ) 
	{}
	Adjacency_matrix( const Adjacency_matrix& other )
		: _graph( other._graph )
	{}
	Adjacency_matrix( Adjacency_matrix&& other ) noexcept
		: _graph( std::move(other._graph) ) 
	{}
	Adjacency_matrix& operator=( Adjacency_matrix other ) {
		swap( *this, other );
		return *this;
	}
	~Adjacency_matrix() = default;

	void add_edge( int from, int to ) {
		if ( from < 0 || to < 0 ) return;
		_graph[ from ][ to ] = 1;
	}

	void add_edges( const std::vector<std::pair<int , int>>& edges ) 
	{
		for ( const auto& edge : edges ) {
			add_edge( edge.first, edge.second );
		}
	}

	void remove_edge( int from, int to ) {
		if ( from < 0 || to < 0 ) return;
		_graph[ from ][ to ] = 0;
	}

	bool path_exists( int from, int to ) const {
		return _graph[ from ][ to ] != 0;
	}
	void setMatrix( const std::vector<std::vector< int >>& matrix ) {
		_graph = matrix;
	}
	
	void fillMatrixWith( int value ) {
		for (auto& row : _graph) {
			std::fill( row.begin(), row.end(), value );
		}
	}
	void resetMatrix() {
		fillMatrixWith( 0 );
	}

	void swap( Adjacency_matrix& first, Adjacency_matrix& sec ) {
		using std::swap;
		swap( first._graph, sec._graph );
	}

	const adj_matrix& graph() const { return _graph; }
	int size() const { return _graph.size(); }
	bool empty() const { return size() == 0; }

private:
	adj_matrix _graph;
};
