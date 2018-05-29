#pragma once
#include <vector>
using namespace std;

#define INF 200000

class Graph 
{
public:
	Graph(int numberOfVertexes) : adjList(numberOfVertexes), _cntEdges(0) {}
	~Graph() {}

	const size_t size() const { return adjList.size(); }
	const size_t EdgesCount() const { return _cntEdges; }
	const std::vector<int>& getAdjacentVertexes(size_t v) const { return adjList.at(v); }
	void addEdge(int from, int to);
	void addOrientedEdge(int from, int to);

	bool connected(int v1, int v2) 
	{
		for (int w : adjList[v1])
		{
			if (w == v2)
				return 1;
		}
		return 0;
	}

private:
	std::vector<std::vector<int>> adjList;
	size_t _cntEdges;
};

/////////////////////////////////////////////////////////////////////////////////////

inline void Graph::addEdge(int from, int to)
{
	adjList.at(from).push_back(to);
	adjList.at(to).push_back(from);
	_cntEdges++;
}

inline void Graph::addOrientedEdge(int from, int to)
{
	adjList.at(from).push_back(to);
	_cntEdges++;
}