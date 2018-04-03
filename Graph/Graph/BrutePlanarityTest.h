#pragma once
//Mei and Gibbs

#ifndef BrutePlanarityTest_H_
#define BrutePlanarityTest_H_


#include "Graph.h"
#include <vector>
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


	void DFS(int v, int prev, bool *color, vector<int>& cycle, vector<vector<int>>& allCycles);

	void rotateToSmallest(vector<int>& cycle);
	bool checkCycle(const vector<int>& cycle);
	bool K5check(const vector<int>& cycle);
	bool K33check(const vector<int>& cycle);
	vector< vector<int> > getVectorOfCycles();
};


#endif // !BrutePlanarityTest_H_