#pragma once
#include <algorithm>
template < typename T >
class GraphI {
	using Graph = std::map<T, std::list<std::pair<T, int>> >;
public:
	GraphI() = default;
	virtual ~GraphI() = default;

	virtual void add_vertex( const T& vertex ) {
		// if exists then add else do nothing
		_graph[ vertex ] = {};
		++_size;
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
									   [&to]( const auto& pair ) { return pair.first == to; } );
		// if edge already exists
		if ( it_exists != neighbours.end() ) return;
		neighbours.emplace_back( to, cost );
	}
	virtual void remove_vertex( const T& vertex ) {
		_graph.erase( vertex );
		--_size;
		// remove all edges going TO vertex
		for ( auto& v : _graph ) { 
			auto it = std::find_if( v.second.begin(),
									v.second.end(),
									[&vertex]( const auto& pair )
									{ return vertex == pair.first; } );
			// if vertex does NOT exist
			if ( it == v.second.end() ) return;
			v.second.erase( it );
		}
		
	}
    virtual void remove_edge( const T& from, const T& to ) {
		auto it = _graph.find( from );
		if ( it == _graph.end() ) return;

		auto &edges = it->second;
		auto it2 = std::find_if( edges.begin(), edges.end(),
								 [&]( const auto& pair ) { return pair.first == to; } );
	
		if ( it2 == edges.end() ) return;
		edges.erase( it2 );
	}
	
	const Graph& graph() const { return _graph; }
	unsigned size() const { return _size; }
private:
	Graph _graph;
	unsigned _size;
};
