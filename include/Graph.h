#pragma once
#include <vector>
#include <map>
#include <list>
#include <set>
#include "GraphInterface.h"
template < typename T >
class Graph : public Adjacency_list<T>{
public:

};

template < typename T >
class GraphMat : public Adjacency_matrix {

};
