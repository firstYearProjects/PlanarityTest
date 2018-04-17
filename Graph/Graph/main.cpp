#include "Graph.h"
#include"BrutePlanarityTest.h"
#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <ctime>
using namespace std;


void Test(const Graph& g, const string &name, bool expected)
{
	BrutePlanarityTest m(g);
	cout << name << '\n';
	bool res = m.checkPlanarity();
	cout << (res ? "planar : " : "not planar : ");
	cout << ((res == expected) ? "correct" : "wrong") << '\n';
}

void Test(const Graph& g, const string &name)
{
	BrutePlanarityTest m(g);
	cout << name << '\n';
	bool res = m.checkPlanarity();
	cout << (res ? "planar : " : "not planar : ") << '\n';
}

Graph& getCompleteGraph(size_t n)
{
	Graph* res = new Graph(n);
	for (int sub = 0; sub < n - 1; sub++)
	{
		for (size_t i = sub + 1; i < n ; i++)
		{
			res->addEdge(sub, i);
		}
	}
	return *res;
}

Graph& getRandomGraph(size_t n)
{
	Graph* res = new Graph(n);
	//srand(time(0));
	int edgeCnt = rand() % (n*(n - 2));
	for (int i = 0; i < edgeCnt; i++)
	{
		int v1 = 0;
		int v2 = 0;
		while (v1 == v2 || res->connected(v1,v2) )
		{
			v1 = rand() % n;
			v2 = rand() % n;
		}
		res->addEdge(v1, v2);
	}
	return *res;
}

int main()
{
	{
		cout << "\n";
		// K5
		Graph g(5);
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
		
		Test(g, "K5", 0);
	}

	{
		cout << "\n";
		// K33
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

		Test(g, "K33", 0);
	}

	{
		cout << "\n";
		// Almost K33
		Graph g(6);
		g.addEdge(0, 3);
		//g.addEdge(0, 4);
		g.addEdge(0, 5);

		g.addEdge(1, 3);
		//g.addEdge(1, 4);
		g.addEdge(1, 5);

		g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(2, 5);
		Test(g, "almost K33", 1);
	}

	{
		cout << "\n";
		// K5 with odd
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
		g.addEdge(2, 4);

		g.addEdge(3, 4);

		g.addEdge(5, 6);
		g.addEdge(6, 2);
		//g.addEdge(5, 7);
		//g.addEdge(6, 7);

		Test(g, "K5 with odd", 0);
	}

	{
		cout << "\n";
		// K33 with odd
		Graph g(10);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(0, 5);

		g.addEdge(1, 3);
		g.addEdge(1, 4);
		g.addEdge(1, 5);

		g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(2, 5);

		g.addEdge(9, 8); // more components

		Test(g, "K33 with odd", 0);
	}

	{
		cout << "\n";
		// K33 + K5
		Graph g(20);
		// K5 part
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
		///
		g.addEdge(10, 13);
		g.addEdge(10, 14);
		g.addEdge(10, 15);

		g.addEdge(11, 13);
		g.addEdge(11, 14);
		g.addEdge(11, 15);

		g.addEdge(12, 13);
		g.addEdge(12, 14);
		g.addEdge(12, 15);

		Test(g, "K33 + K5", 0);
	}

	{
		cout << "\n";
		// RND test
		Test(getRandomGraph(10), "rnd10");
	}

	{
		cout << "\n";
		// RND test
		Test(getRandomGraph(20), "rnd20");
	}




	{
		cout << "\n";
		// FULL 1001
		Test(getCompleteGraph(50), "full 1001", 0);
	}

	system("pause");
	return 0;
}