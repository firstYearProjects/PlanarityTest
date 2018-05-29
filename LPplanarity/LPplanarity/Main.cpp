#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cassert>
#include <ctime>

#include "Graph.h"
#include "LRtest.h"

using namespace std;

void test(const Graph& g, const string &testName, const bool isPlanar)
{
	cout << "test: \"" << testName << "\"";
	if (PlanarityTest(g).checkPlanar() == isPlanar) {
		cout << " passed" << endl;
	}
	else {
		cout << " failed" << endl;
	}
}

void test(const Graph& g, const string &testName)
{
	cout << "test: \"" << testName << "\"";
	cout << (((PlanarityTest(g).checkPlanar()) == 1) ? " planar\n" : " not planar\n");
}

void rndTest(int n)
{
	Graph g(n);
	srand(time(0));

	int edgeCnt = rand() % (3 * n - 7);
	for (int i = 0; i < edgeCnt; i++)
	{
		int v1 = 0;
		int v2 = 0;
		while (v1 == v2 || g.connected(v1, v2))
		{
			v1 = rand() % n;
			v2 = rand() % n;
		}
		g.addEdge(v1, v2);
	}
	//rnd 40
	test(g, "RANDOM ");
}

int main() 
{
	{
		// 2 components planar
		Graph g(6);
		g.addEdge(0, 3);
		g.addEdge(0, 4);

		g.addEdge(5, 2);
		test(g, "2 components", true);
	}

	{ 
		// K_3_3 not planar
		Graph g(6);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(0, 5);
		g.addEdge(1, 3);
		g.addEdge(1, 4);
		g.addEdge(1, 5);
		g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(2, 5);

		test(g, "K_3_3 not planar", false);
	}

	{ 
		// K_5 not planar
		Graph g(6);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(1, 2);
		g.addEdge(1, 3);
		g.addEdge(1, 4);
		g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(3, 4);

		test(g, "K_5 not planar", false);
	}

	{ 
		// planar
		Graph g(6);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(1, 3);
		g.addEdge(2, 3);
		g.addEdge(3, 4);
		g.addEdge(2, 4);
		g.addEdge(4, 5);
		g.addEdge(5, 2);
		g.addEdge(5, 0);
		test(g, "simple planar", true);
	}

	{ 
		// almost K_5 planar
		Graph g(5);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(1, 2);
		g.addEdge(1, 4);
		g.addEdge(2, 0);
		g.addEdge(2, 3);
		g.addEdge(2, 4);

		test(g, "almost K_5 planar", true);
	}

	{ 
		// almost K_5 not planar
		Graph g(8);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(1, 2);
		g.addEdge(1, 3);
		g.addEdge(1, 4);
		g.addEdge(2, 5);
		g.addEdge(5, 3);
		//g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(3, 4);
		g.addEdge(2, 6);
		g.addEdge(5, 6);
		g.addEdge(6, 7);
		g.addEdge(5, 7);

		test(g, "almost K_5 planar", false);
	}
	{ 
		// almost K_5 not planar
		Graph g(100);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		//g.addEdge(0, 4);
		g.addEdge(1, 2);
		g.addEdge(1, 3);
		g.addEdge(1, 4);
		g.addEdge(2, 5);
		g.addEdge(5, 3);
		//g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(3, 4);
		g.addEdge(2, 6);
		g.addEdge(5, 6);
		g.addEdge(6, 7);
		g.addEdge(5, 7);
		g.addEdge(10, 7);
		g.addEdge(11, 7);
		test(g, "almost K_5 planar", false);
	}

	system("pause");
	return 0;
}
