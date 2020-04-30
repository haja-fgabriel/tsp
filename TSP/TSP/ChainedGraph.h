#pragma once

#include <deque>
#include <iostream>
#include "Edge.h"
#include "Graph.h"

using std::deque;
using std::vector;
using std::ostream;

class ChainedGraph
{
private:
	int Size;
	deque<size_t> Chain;
	double TotalCost;

	void TransformRepresentation(const vector<Edge>& edges);

public:

	ChainedGraph(int size);
	ChainedGraph(Graph& G);
	ChainedGraph(int Size, const vector<int>& Path, double Cost);

	ChainedGraph(int Size, const vector<Edge>& edges);
	void AddNodeInChain(size_t node);
	void SetTotalCost(double cost);

	friend ostream& operator<<(ostream&, ChainedGraph& graph);

	~ChainedGraph() = default;
};

