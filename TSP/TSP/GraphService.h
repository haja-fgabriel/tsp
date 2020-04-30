#pragma once

#include "Graph.h"
#include "ChainedGraph.h"

class GraphService
{
private:
	Graph& G;
	ChainedGraph GetShortestCyclicPath_Kruskal();

public:
	GraphService(Graph&);
	
	ChainedGraph GetShortestCyclicPath_GeneticAlgo();
	ChainedGraph GetShortestCyclicPath();
	ChainedGraph GetShortestTraversingPath();
    ChainedGraph GetShortestCyclicPath_ACO();

	~GraphService() = default;
};