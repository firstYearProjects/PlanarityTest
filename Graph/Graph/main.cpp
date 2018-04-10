#include "Graph.h"
#include"BrutePlanarityTest.h"
#include <iostream>
#include <string>
using namespace std;


void Test(const Graph& g, const string &name, bool expected)
{
	BrutePlanarityTest m(g);
	cout << name << '\n';
	bool res = m.checkPlanarity();
	cout << (res ? "planar : " : "not planar : ");
	cout << ((res == expected) ? "correct" : "wrong") << '\n';
}

Graph& getCompleteGraph(size_t n)
{
	Graph* res = new Graph(n);
	for (int sub = 0; sub < n - 1; sub++)
	{
		for (size_t i = sub + 1; i < n - 1; i++)
		{
			res->addEdge(sub, i);
		}
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
		Graph r(6);
		r.addEdge(0, 3);
		r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);

		Test(r, "K33", 0);
	}

	{
		cout << "\n";
		// Almost K33
		Graph r(6);
		r.addEdge(0, 3);
		//r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		//r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);
		Test(r, "almost K33", 1);
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
		Graph r(10);
		r.addEdge(0, 3);
		r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);

		r.addEdge(9, 8); // more components

		Test(r, "K33 with odd", 0);
	}

	{
		cout << "\n";
		// K33 + K5
		Graph r(20);
		r.addEdge(0, 3);
		r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);
		///
		r.addEdge(5, 6);
		r.addEdge(5, 7);
		r.addEdge(5, 8);
		r.addEdge(5, 9);

		r.addEdge(6, 7);
		r.addEdge(6, 8);
		r.addEdge(6, 9);

		r.addEdge(7, 8);
		r.addEdge(7, 9);

		r.addEdge(8, 9);

		Test(r, "K33 + K5", 0);
	}

	{
		cout << "\n";
		// FULL 1001
		Test(getCompleteGraph(1001), "full 1001", 0);
	}

	system("pause");
	return 0;
}