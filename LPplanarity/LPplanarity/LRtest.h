

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <memory>
#include <algorithm>
#include "Graph.h"

class PlanarityTest
{
public:
	PlanarityTest(const Graph& graph);

	bool checkPlanar();

private:
	const Graph& graph;


	struct Edge : public std::pair<int, int> 
	{
		Edge() : std::pair<int, int>(-1, -1) {}
		Edge(int from, int to) : std::pair<int, int>(from, to) {}

		bool IsEmpty() const { return first == -1 && second == -1; }
		void MakeEmpty() { first = -1; second = -1; }
	};

	struct EdgeHash 
	{
		std::size_t operator() (const Edge& e) const
		{
			std::hash<int> intHash;
			return (intHash(e.first) << 4) + intHash(e.second);
		}
	};

	template <typename T>
	using EdgeDict = std::unordered_map<Edge, T, EdgeHash>;

	// Edge pair
	struct Interval : public std::pair<Edge, Edge> 
	{
		Interval() = default;
		Interval(Edge low, Edge high) : std::pair<Edge, Edge>(low, high) {}

		Edge& low() { return first; }
		const Edge& low() const { return first; }
		Edge& high() { return second; }
		const Edge& high() const { return second; }
		bool IsEmpty() const { return first.IsEmpty() && second.IsEmpty(); }
	};

	// Interval pair
	struct ConflictPair : public std::pair<Interval, Interval> 
	{
		ConflictPair() = default;
		ConflictPair(Interval L, Interval R) : std::pair<Interval, Interval>(L, R) {}

		Interval& L() { return first; }
		const Interval& L() const { return first; }
		Interval& R() { return second; }
		const Interval& R() const { return second; }
		bool IsEmpty() const { return first.IsEmpty() && second.IsEmpty(); }
	};

	class not_planar_exception : public std::exception 
	{
	};


	/* orientation phase */

	// Orientation of dfs
	std::unordered_set<Edge, EdgeHash> orientation;

	// Distance to the root in DFS tree for each vert
	std::vector<int> height;
	
	// Parent vertex in dfs orientation
	std::vector<int> parent;
	
	// height of lowest return point
	EdgeDict<int> lowpt;
	
	// height of next-to-lowest return point (tree edges only)
	EdgeDict<int> lowpt2;
	
	// nesting depth, proxy for nesting order given by twice lowpt (plus 1 if chordal)
	EdgeDict<int> nesting_depth;


	/* testing phase */
	
	//top of stack S when traversing the edge(tree edges only)
	EdgeDict<ConflictPair> stack_bottom;

	// conflict pairs consisting of current return edges
	std::stack<ConflictPair> S;

	// edge relative to which side is defined
	EdgeDict<Edge> ref;

	// side of edge, or modier for side of reference edge (-1, 1)
	EdgeDict<int> side;

	//next back edge in traversal (i.e.with lowest return point)
	EdgeDict<Edge> lowpt_edge;


	void doDfs1(int v);

	// Check if was in dfs
	bool isReached(int v) const;
	// Wrapper to set root height in each connection comp to 0
	void DFS1(int v);

	void sortAdjacencyList();
	void DFS2(int v);

	void addEdgeConstraint(const Edge& e);
	bool conflicting(const Interval& I, const Edge& b);
	void trimBackEdgesEndingAtParent(int u);
	int lowest(const ConflictPair& P);

	// DFS2 new graph
	std::unique_ptr<Graph> reorderedGraph;

};

