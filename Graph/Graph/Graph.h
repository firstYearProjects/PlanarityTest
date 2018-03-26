#pragma once


#ifndef Graph_H_
#define Graph_H_

#include <vector>

using namespace std;

class Vertex
{
public:
	Vertex();
	~Vertex();

	vector<Vertex*>* edges;
	bool HasAdgeToVertex(Vertex* vertex);
};

bool IsK5graph(vector<Vertex*> &subgraph);

bool IsK33graph(vector<Vertex*> &subgraph);

class Graph
{
public:
	Graph(size_t n);
	~Graph();
	void addVertex();
	void addEdge(size_t ID1, size_t ID2);
private:
	vector<Vertex*> vertexes;
};


#endif // !Graph_H_
