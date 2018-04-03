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

bool Graph::connected(size_t ID1, size_t ID2)
{
	if (this->_vertexes.size() <= ID1 || this->_vertexes.size() <= ID2)
		return 0;
	for (size_t i = 0; i < this->_vertexes.at(ID1).size(); i++)
	{
		if (this->_vertexes.at(ID1)[i] == ID2)
			return 1;
	}
	return 0;
}
