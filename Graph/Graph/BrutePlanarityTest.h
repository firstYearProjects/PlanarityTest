#pragma once
//Mei and Gibbs

#ifndef BrutePlanarityTest_H_
#define BrutePlanarityTest_H_


#include "Graph.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class BrutePlanarityTest
{
public:
	BrutePlanarityTest(const Graph& graph) : _graph(graph) {};

	bool checkPlanarity();
	bool BruteCheck();

	void printAllCycles();
private:
	Graph _graph;

	vector<int> getCycle(int begin, int end, vector<int>& cycle);


	void DFS(int v, int prev, set<int>& color, vector<int>& cycle, vector<vector<int>>& allCycles, vector<bool>& visited);

	void rotateToSmallest(vector<int>& cycle);
	bool checkCycle(const vector<int>& cycle);
	bool K5check(const vector<int>& cycle);
	bool K33check(const vector<int>& cycle);
	vector< vector<int> > getVectorOfCycles();

	size_t edgeHash(int first, int second)
	{
		hash<int> intHash;
		return (intHash(first) << 4) + intHash(second);
	}
};


#endif // !BrutePlanarityTest_H_