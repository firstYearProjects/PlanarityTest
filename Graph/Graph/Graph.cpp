#include "Graph.h"


Graph::Graph(size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		addVertex();
	}
}

Graph::~Graph()
{
	for (auto vert = vertexes.begin(); vert != vertexes.end(); ++vert)
	{
		delete (*vert);
	}
}

void Graph::addVertex()
{

	Vertex* newVert = new Vertex;
	vertexes.push_back(newVert);
}

void Graph::addEdge(size_t ID1, size_t ID2)
{
	if (ID1 >= this->vertexes.size() || ID2 >= this->vertexes.size())
		return;
	Vertex* v1 = (vertexes)[ID1];
	Vertex* v2 = (vertexes)[ID2];
	(*v1->edges).push_back(v2);
	(*v2->edges).push_back(v1);
}

Vertex::Vertex()
{
	this->edges = new vector<Vertex*>;
}

Vertex::~Vertex()

{
	for (auto edge = (*this->edges).begin(); edge != (*this->edges).end(); ++edge)
	{
		delete (*edge);
	}
}

bool Vertex::HasAdgeToVertex(Vertex * vertex)
{
	for (auto edge = this->edges->begin(); edge != this->edges->end(); ++edge)
	{
		if ((*edge) == vertex)
			return true;
	}
	return false;
}

bool IsK5graph(vector<Vertex*>& subgraph)
{
	bool result = false;
	int n = 5;
	if (subgraph.size() == n)
	{
		result = true;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				result &= subgraph[i]->HasAdgeToVertex(subgraph[j]);
			}
		}
	}
	return result;
}

bool IsK33graph(vector<Vertex*>& subgraph)
{
	bool result = false;
	int n = 6;
	if (subgraph.size() == n)
	{
		result = true;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				result &= subgraph[i]->HasAdgeToVertex(subgraph[j]);
			}
		}
	}
	return result;
}