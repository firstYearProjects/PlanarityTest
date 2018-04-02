#pragma once

#ifndef PlanarityTest_H_
#define PlanarityTest_H_

#include "Graph.h"

using namespace std;

// Structure that contains 
struct Edge: public pair<int, int>
{
	
};
struct EdgeHash {
	std::size_t operator() (const Edge& e) const
	{
		std::hash<int> intHash;
		return (intHash(e.first) << 4) + intHash(e.second);
	}
};

class PlanarityTest
{
public:
	PlanarityTest(const Graph& graph);
	
	// Return 1 - planar, 0 - not planar.
	bool checkPlanar();

private:
	const Graph& graph;



};

#endif // !PlanarityTest_H_


