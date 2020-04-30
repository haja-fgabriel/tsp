#include "GraphService.h"
#include "DisjointSet.h"
#include "ChainedGraph.h"
#include "GraphAlgorithms.h"
#include "Utils.h"

#include "GeneticAlgorithm.h"
#include "AntColony.h"


#include <Windows.h>
#include <functional>
#include <bitset>
#include <queue>
#include <algorithm>
#include <iostream>
#include <iomanip>


GraphService::GraphService(Graph& G)
	: G{G} {}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GraphService::GetShortestCyclicPath

  Summary:  Gets the shortest cyclic path through all the nodes in 
			the given graph.

  Args:     none

  Modifies: [list of member data variables modified by this method].

  Returns:  ChainedGraph
			  Class containing a sequential representation of the cycle.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
ChainedGraph GraphService::GetShortestCyclicPath_Kruskal()
{
	vector<int> nodeDegree;
	nodeDegree.resize(G.GetSize() + 1);

	/* returns a new graph containing the required edges for the minimal
	   Hamiltonian cycle */
	Graph newGraph = GraphAlgorithms::Kruskal(G, 
	[&](DisjointSet& Set, Edge& e) { 
		/* condition for joining two chains */
		return Set.FindSet(e.Left) != Set.FindSet(e.Right) 
			&& nodeDegree[e.Left] < 2 && nodeDegree[e.Right] < 2;
	}, 
	[&](Edge& e) {		
		/* additional function required for storing each node's degree */
		nodeDegree[e.Left]++;
		nodeDegree[e.Right]++;
	});
	
	/* adding the required edge for completing the cycle */
	for (auto& edge : G.GetEdges())
	{
		if (nodeDegree[edge.Left] == 1 && nodeDegree[edge.Right] == 1)
		{
			newGraph.AddEdge(edge);
			nodeDegree[edge.Left]++;
			nodeDegree[edge.Right]++;
		}
	}

	/* converting to sequential representation */
	return ChainedGraph(newGraph);
}

ChainedGraph GraphService::GetShortestCyclicPath()
{
	return GraphAlgorithms::HeldKarp(G, false);
}

ChainedGraph GraphService::GetShortestTraversingPath()
{
	return GraphAlgorithms::HeldKarp(G, true);
}

ChainedGraph GraphService::GetShortestCyclicPath_GeneticAlgo()
{
	GeneticAlgorithm ga(G, GeneticAlgorithm::PopulationCount);
	
	ga.ComputeAll();

	Chromosome& result = ga.GetBestChromosome();
	return ChainedGraph(result.GetSize(), result.GetPermutation(), result.ComputeFitness());
}

ChainedGraph GraphService::GetShortestCyclicPath_ACO()
{
    AntColony antColony(G, 0.5, 0.8, 80, 0.2, 2);

    antColony.Optimize(10);

    return ChainedGraph(G.GetSize(), antColony.GetBestRoute(), antColony.GetBestLength());
}