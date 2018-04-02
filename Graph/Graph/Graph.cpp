#include "Graph.h"


void Graph::addEdge(size_t from, size_t to)
{
	if (from > _vertexes.size() || to > _vertexes.size())
		return;
	_vertexes.at(from).push_back(to);
	_vertexes.at(to).push_back(from);
	_cntEdges++;
}

void Graph::addOrientedEdge(size_t from, size_t to)
{
	if (from > _vertexes.size() || to > _vertexes.size())
		return;
	_vertexes.at(from).push_back(to);
	_cntEdges++;
}
