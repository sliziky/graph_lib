#pragma once
#include <algorithm>
#include "colors.h"
struct Vertex;
template < typename T >
class GraphI {
	
public:
	struct Vertex {
		Vertex( const T& k, color col = color::w, int c = -1 )
			: key( k )
			, color(col)
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
	using Graph = std::map<Vertex, std::list<Vertex> >;
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
									   [&to]( const Vertex& vertex ) { return vertex.getKey() == to; } );
		// if edge already exists
		if ( it_exists != neighbours.end() ) return;
		neighbours.emplace_back( Vertex(to, color::w, cost) );
	}
	virtual void remove_vertex( const T& vertex ) {
		_graph.erase( vertex );
		--_size;
		// remove all edges going TO vertex
		for ( auto& v : _graph ) { 
			auto it = std::find_if( v.second.begin(),
									v.second.end(),
									[&vertex]( const auto& v )
									{ return vertex == v.getKey(); } );
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
								 [&]( const auto& vertex ) { return vertex.key == to; } );
	
		if ( it2 == edges.end() ) return;
		edges.erase( it2 );
	}
	
	const Graph& graph() const { return _graph; }
	unsigned size() const { return _size; }
private:
	Graph _graph;
	unsigned _size;
};
