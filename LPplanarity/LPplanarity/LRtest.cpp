#include "LRtest.h"

#include <cassert>


PlanarityTest::PlanarityTest(const Graph& _graph) :graph(_graph)
{
}

bool PlanarityTest::checkPlanar()
{
	const size_t vertexesCount = graph.size();
	const size_t _cntEdges = graph.EdgesCount();
	// 1. Euler planarity check
	if (vertexesCount > 2 && _cntEdges > (3 * vertexesCount - 6)) 
		return false;

	// 2. DFS orientation
	std::vector<int> Roots;

	height.assign(graph.size(), INF);
	parent.assign(graph.size(), -1);

	for (int v = 0; v < vertexesCount; ++v)
	{
		if (!isReached(v)) 
		{
			Roots.push_back(v);
			DFS1(v);
		}
	}
	// 3. Testing
	try
	{
		//sort adjacency lists according to non-decreasing nesting depth
		sortAdjacencyList(); // + create new oriented graph 

		for (int i = 0; i < Roots.size(); i++)
		{
			DFS2(Roots[i]);
		}
	}
	catch (not_planar_exception& e)
	{
		return false;
	}

	return true;
}

bool PlanarityTest::isReached(int v) const { return height[v] != INF; }

void PlanarityTest::DFS1(int v)
{
	height[v] = 0;
	doDfs1(v);
}

void PlanarityTest::doDfs1(int v)
{
	//let u be parent in dfs order to v:
	Edge u_v(parent[v], v);
	for (const int w : graph.getAdjacentVertexes(v)) 
	{
		// Check if we came from w
		if (orientation.find(Edge(w, v)) != orientation.end()) 
			continue;
		
		Edge v_w(v, w);
		orientation.insert(v_w);
		
		// tree edge
		if (height[w] == INF) 
		{ 
			parent[w] = v;
			height[w] = height[v] + 1;
			doDfs1(w);
		}
		// back edge
		else 
		{
			lowpt[v_w] = height[w];
		}
		// determine nesting depth
		if (lowpt.find(v_w) != lowpt.end()) 
		{
			nesting_depth[v_w] = 2 * lowpt[v_w];
			auto lp2Result = lowpt2.find(v_w);


			// chordal case
			if (lp2Result != lowpt2.end() && lp2Result->second < height[v]) 
			{
				nesting_depth[v_w] += 1;
			}
		}
		// Update lowpts of parent edge u_v.

		// If not root
		if (u_v.first != -1) 
		{ 
			if (lowpt.find(u_v) == lowpt.end()) 
			{
				lowpt[u_v] = lowpt[v_w];
				if (lowpt2.find(v_w) != lowpt2.end()) 
				{
					lowpt2[u_v] = lowpt2[v_w];
				}
			}
			else 
			{
				if (lowpt[v_w] < lowpt[u_v]) 
				{
					if (lowpt2.find(v_w) != lowpt2.end())
						lowpt2[u_v] = std::min(lowpt[u_v],
							                   lowpt2[v_w]);
					else
						lowpt2[u_v] = lowpt[u_v];
				
					lowpt[u_v] = lowpt[v_w];
				}
				else if (lowpt[v_w] > lowpt[u_v]) 
				{
					if (lowpt2.find(u_v) != lowpt2.end())
						lowpt2[u_v] = std::min(lowpt2[u_v],
							                   lowpt[v_w]);
					else
						lowpt2[u_v] = lowpt[v_w];
				}
				else 
				{
					if (lowpt2.find(u_v) != lowpt2.end()) 
					{
						if (lowpt2.find(v_w) != lowpt2.end()) 
						{
							lowpt2[u_v] = std::min(lowpt2[u_v],
								                   lowpt2[v_w]);
						}
					}
					else if (lowpt2.find(v_w) != lowpt2.end()) 
					{
						lowpt2[u_v] = lowpt2[v_w];
					}
				}
			}
		}
	}
}



void PlanarityTest::sortAdjacencyList() 
{
	reorderedGraph.reset(new Graph(graph.size())); // uptr
	vector<vector<pair<int, int>>> newEdges(graph.size());
	for (const auto& v : nesting_depth)
	{
		const int from = v.first.first;
		const int to = v.first.second;
		const int order = v.second;
		newEdges[from].push_back(make_pair(order, to));
	}
	for (int i = 0; i < newEdges.size(); ++i) 
	{
		std::sort(newEdges[i].begin(), newEdges[i].end(), less<std::pair<int, int>>());
		for (const auto& v : newEdges[i]) 
		{
			reorderedGraph->addOrientedEdge(i, v.second);
		}
	}
	orientation.clear();
}

void PlanarityTest::DFS2(int v)
{
	const int u = parent[v];
	Edge u_v(u, v);
	for (int i = 0; i < reorderedGraph->getAdjacentVertexes(v).size(); ++i) 
	{
		const int w = reorderedGraph->getAdjacentVertexes(v)[i];
		Edge v_w(v, w);
		if (!S.empty()) 
		{
			stack_bottom[v_w] = S.top();
		}
		if (parent[w] == v) 
		{ 
			//tree edge
			DFS2(w);
		}
		else 
		{
			// back edge
			lowpt_edge[v_w] = v_w;
			S.push(ConflictPair(Interval(), Interval(v_w, v_w)));
		}
		// integrate new return edges
		if (lowpt[v_w] < height[v]) 
		{
			// v_w has return edge
			if (i == 0) 
			{
				lowpt_edge[u_v] = v_w;
			}
			else 
			{
				addEdgeConstraint(v_w);
			}
		}
	}
	// remove back edges returning to parent
	if (u != -1) 
	{
		trimBackEdgesEndingAtParent(u);
		// side of u_v is side of a highest return edge
		if (lowpt[u_v] < height[u] && !S.empty()) 
		{ 
			/* e has return edge */
			Edge h_L = S.top().L().high();
			Edge h_R = S.top().R().high();
			if (h_L.first != -1 && (h_R.first != -1 || lowpt[h_L] > lowpt[h_R])) 
			{
				ref[u_v] = h_L;
			}
			else
			{
				ref[u_v] = h_R;
			}
		}
	}
}

void PlanarityTest::addEdgeConstraint(const Edge &v_w)
{
	const int v = v_w.first;
	const Edge u_v(parent[v], v);
	ConflictPair P;
	// merge return edges of e into P.R()
	do {
		ConflictPair Q = S.top();
		S.pop();

		if (!Q.L().IsEmpty()) 
		{
			std::swap(Q.L(), Q.R());
		}
		if (!Q.L().IsEmpty()) 
		{
			////HALT//////
			throw not_planar_exception(); 
		}
		else {
			if (lowpt[Q.R().low()] > lowpt[u_v]) 
			{
				// merge intevals
				if (P.R().IsEmpty())
				{ 
					// topmost interval
					P.R().high() = Q.R().high();
				}
				else 
				{
					ref[P.R().low()] = Q.R().high();
				}
				P.R().low() = Q.R().low();
			}
			else 
			{ 
				// align
				ref[Q.R().low()] = lowpt_edge[u_v];
			}
		}
	} while (!S.empty() && S.top() != stack_bottom[v_w]);

	// merge conflicting return edges of e1,...,ei−1 into P.L()
	while (!S.empty() && (conflicting(S.top().L(), v_w) || conflicting(S.top().R(), v_w))) 
	{
		ConflictPair Q = S.top(); S.pop();
		if (conflicting(Q.R(), v_w))
		{
			std::swap(Q.L(), Q.R());
		}
		if (conflicting(Q.R(), v_w))
		{
			////HALT//////
			throw not_planar_exception();          
		}
		else 
		{ 
			// merge interval below lowpt(e) into P.R
			ref[P.R().low()] = Q.R().high();
			if (!Q.R().low().IsEmpty())
			{
				P.R().low() = Q.R().low();
			}
		}
		if (P.L().IsEmpty()) 
		{ 
			// topmost interval
			P.L().high() = Q.L().high();
		}
		else 
		{
			ref[P.L().low()] = Q.L().high();
		}
		P.L().low() = Q.L().low();
	}
	if (!P.IsEmpty())
	{
		S.push(P);
	}

}

void PlanarityTest::trimBackEdgesEndingAtParent(int u)
{
	//drop entire conflict pairs
	while (!S.empty() && lowest(S.top()) == height[u])
	{
		ConflictPair P = S.top(); S.pop();
		if (!P.L().low().IsEmpty()) 
		{
			side[P.L().low()] = -1;
		}
	}
	if (!S.empty()) 
	{
		// one more conflict pair to consider
		ConflictPair P = S.top(); S.pop();
		// trim left interval
		while (!P.L().high().IsEmpty() && P.L().high().second == u) 
		{
			P.L().high() = ref[P.L().high()];
		}
		if (P.L().high().IsEmpty() && !P.L().low().IsEmpty()) 
		{ 
			// just emptied
			ref[P.L().low()] = P.R().low();
			side[P.L().low()] = -1;
			P.L().low().MakeEmpty();
		}
		// trim right interval
		S.push(P);
	}
}

bool PlanarityTest::conflicting(const Interval &I, const Edge &b)
{
	return (!I.IsEmpty() && lowpt[I.high()] > lowpt[b]);
}

int PlanarityTest::lowest(const PlanarityTest::ConflictPair &P) 
{
	if (P.L().IsEmpty())
	{
		return lowpt[P.R().low()];
	}
	if (P.R().IsEmpty()) 
	{
		return lowpt[P.L().low()];
	}
	return std::min(lowpt[P.L().low()], lowpt[P.R().low()]);
}
