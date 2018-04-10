#pragma once

#ifndef Graph_H_
#define Graph_H_

#include <vector>

using namespace std;

class Graph
{
public:
	Graph(int numberOfVertexes) : _vertexes(numberOfVertexes), _cntEdges(0) {};

	// Number of vertexes.
	size_t size()       { return _vertexes.size(); }

	// Number of edges in whole graph.
	size_t edgesCount() { return _cntEdges;        }

	// Returns vector of vertexes' IDs that are connected to chosen 'vertex'.
	const vector<int>& getAdjacentVertexes(size_t vertex) { return _vertexes.at(vertex); }

	// Adds non-oriented edge.
	void addEdge(size_t from, size_t to);

	// Adds oriented edge with direction from -> to.
	void addOrientedEdge(size_t from, size_t to);

	// Return 1 if ID1 and ID2 are non-orient connected.
	bool connected(size_t ID1, size_t ID2);

	// DFS lookup on whether there is a way from u to v without verts from cycle in it.
	bool findWay(int u, int v, const vector<int>& cycle);
	bool dfsWay(int u, int v, const vector<int>& cycle, vector<bool>& visited);

private:
	vector< vector<int> > _vertexes;
	size_t _cntEdges;
};

#endif // !Graph_H_