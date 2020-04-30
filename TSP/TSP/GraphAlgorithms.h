#pragma once

#include "Graph.h"
#include "DisjointSet.h"
#include "ChainedGraph.h"
#include "Edge.h"

#include <algorithm>
#include <functional>
#include <vector>

using std::vector;

using Predicate = std::function<bool(DisjointSet&, Edge&)>;
using AuxiliaryFunction = std::function<void(Edge&)>;
using CompletionFunction = std::function<void(int, vector<Edge>&)>;
using Comparator = std::function<double(const Edge&, const Edge&)>;

namespace GraphAlgorithms
{
	ChainedGraph HeldKarp(Graph& G, bool FixedEnds);
	Graph Kruskal(Graph& G, Predicate p, AuxiliaryFunction f);
};

