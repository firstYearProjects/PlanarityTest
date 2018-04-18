#include "BrutePlanarityTest.h"


bool BrutePlanarityTest::checkPlanarity()
{
	const size_t vertexesCount = _graph.size();
	const size_t _cntEdges = _graph.edgesCount();
	if (vertexesCount < 5)
		return true;

	// Euler formula check.
	if (vertexesCount > 2 && _cntEdges > (3 * vertexesCount - 6)) 
	{
		return false;
	}

	return BruteCheck();
}

void BrutePlanarityTest::printAllCycles()
{
	vector<vector<int>> res = getVectorOfCycles();
	for (size_t i = 0; i < res.size(); i++)
	{
		for (size_t j = 0; j < res[i].size(); j++)
			cout << res[i][j] << " ";
		cout << "\n";
	}
}

vector<int> BrutePlanarityTest::getCycle(int begin, int end, vector<int>& cycle)
{
	vector<int> resCycle;
	int curEl = cycle.size() - 1;
	while (cycle[curEl] != begin)
	{
		resCycle.push_back(cycle[curEl]);
		curEl--;
		if (curEl == 0)
			break;
	}
	resCycle.push_back(cycle[curEl]);
	return resCycle;
}



void BrutePlanarityTest::DFS(int v, int prev, set<int>& color, vector<int>& cycle, vector<vector<int>>& allCycles, vector<bool>& visited)
{
	color.insert(edgeHash(prev,v));
	color.insert(edgeHash(v, prev));
	visited[v] = 1;
	for (size_t i = 0; i < _graph.getAdjacentVertexes(v).size(); i++)
	{
		int tmpV = _graph.getAdjacentVertexes(v)[i];
		if (color.find(edgeHash(v, tmpV)) == color.end())
		{
			if (visited[tmpV] == 1)
			{
				if (prev != tmpV)
				{
					// We need to look only for cycles that have >=5 verts.
					if (cycle.size() >= 5)
					{
						vector<int> tmpCyc = getCycle(tmpV, v, cycle);
						rotateToSmallest(tmpCyc);
						if (tmpCyc.size() >= 5)
						{
							bool checker = 1;
							for (auto finV = allCycles.begin(); finV != allCycles.end(); ++finV)
							{
								bool flag = 1;
								for (size_t elVec = 0; elVec < min(tmpCyc.size(), (*finV).size()); elVec++)
								{
									if (tmpCyc[elVec] != (*finV)[elVec])
									{
										flag = 0;
										break;
									}
								}

								if (flag == 1)
								{
									checker = 0;
									break;
								}
							}
							if (checker == 1)
								allCycles.push_back(tmpCyc);
						}
					}

				}

			}
			else
			{
				cycle.push_back(tmpV);

				DFS(tmpV, v, color, cycle, allCycles, visited);
			}
		}
	}
	cycle.pop_back();
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

void BrutePlanarityTest::rotateToSmallest(vector<int>& cycle)
{
	int etalon = cycle[0];
	size_t posmin = 0;
	for (size_t i = 0; i < cycle.size(); i++)
	{
		if (etalon > cycle[i])
		{
			etalon = cycle[i];
			posmin = i;
		}
	}
	for (size_t i = 0; i < posmin; i++)
	{
		int tmpVert = cycle[0];
		pop_front(cycle);
		cycle.push_back(tmpVert);
	}
}

bool BrutePlanarityTest::BruteCheck()
{
	vector< vector<int> > cycles = getVectorOfCycles();

	for (auto cycle = cycles.begin(); cycle != cycles.end(); ++cycle)
	{
		if (checkCycle(*cycle) == 0)
			return 0;
	}
	return 1;
}

bool BrutePlanarityTest::checkCycle(const vector<int>& cycle)
{
	for (size_t a = 0; a < cycle.size() - 4; a++)
	{
		for (size_t b = a + 1; b < cycle.size() - 3; b++)
		{
			for (size_t c = b + 1; c < cycle.size() - 2; c++)
			{
				for (size_t d = c + 1; d < cycle.size() - 1; d++)
				{
					for (size_t e = d + 1; e < cycle.size(); e++)
					{
						vector<int> tmpCyc;
						tmpCyc.push_back(cycle[a]);
						tmpCyc.push_back(cycle[b]);
						tmpCyc.push_back(cycle[c]);
						tmpCyc.push_back(cycle[d]);
						tmpCyc.push_back(cycle[e]);

						if (K5check(tmpCyc) == 1)
							return 0;
					}
				}
			}
		}
	}
	if (cycle.size() > 5)
	{
		for (size_t a = 0; a < cycle.size() - 5; a++)
		{
			for (size_t b = a + 1; b < cycle.size() - 4; b++)
			{
				for (size_t c = b + 1; c < cycle.size() - 3; c++)
				{
					for (size_t d = c + 1; d < cycle.size() - 2; d++)
					{
						for (size_t e = d + 1; e < cycle.size() - 1; e++)
						{
							for (size_t f = e + 1; f < cycle.size(); f++)
							{
								vector<int> tmpCyc;
								tmpCyc.push_back(cycle[a]);
								tmpCyc.push_back(cycle[b]);
								tmpCyc.push_back(cycle[c]);
								tmpCyc.push_back(cycle[d]);
								tmpCyc.push_back(cycle[e]);
								tmpCyc.push_back(cycle[f]);

								if (K33check(tmpCyc) == 1)
									return 0;
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

bool BrutePlanarityTest::K5check(const vector<int>& cycle)
{
	bool res = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			//res &= _graph.connected(cycle[i], cycle[j]);
			bool tmp = _graph.connected(cycle[i], cycle[j]);
			if (tmp == 1)
				continue;
			else
			{
				tmp = _graph.findWay(cycle[i], cycle[j], cycle);
			}
			res &= tmp;
		}
	}
	return res;
}

bool BrutePlanarityTest::K33check(const vector<int>& cycle)
{
	bool res = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j+=2)
		{
			bool tmp = _graph.connected(cycle[i], cycle[j]);
			if (tmp == 1)
				continue;
			else
			{
				tmp = _graph.findWay(cycle[i], cycle[j], cycle);
			}
			res &= tmp;
		}
	}
	return res;
}


vector< vector<int> > BrutePlanarityTest::getVectorOfCycles()
{
	// used to detect connected components
	vector<bool> visited(this->_graph.size(), 0);
	// vector of cycles
	vector<vector<int> > res; 
	// used to get all elementary cycles in connected component
	//bool *color = new (bool[this->_graph.size()]);
	set<int> color;

	for (int i = 0; i < this->_graph.size(); i++)
	{
		// found new connected component
		if (visited[i] == 0)
		{
			vector<int> curPath;
			curPath.push_back(i);
			DFS(i, i, color, curPath, res, visited);
		}
	}
	
	return res;
}



