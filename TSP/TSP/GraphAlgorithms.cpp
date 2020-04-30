#include "GraphAlgorithms.h"
#include "Utils.h"

#include <limits>

using std::numeric_limits;

struct PreviousConfiguration
{
	uint64_t Configuration;
	size_t Node;
};

static bool CheckEdgeAvailability(uint64_t Configuration, const Edge& edge)
{
	size_t left = edge.Left - 1;
	size_t right = edge.Right - 1;
	return ((Configuration & (1ULL << left)) != 0 && (Configuration & (1ULL << right)) != 0);
}

static void UpdateSolution(
	vector<vector<double>>& Solution,
	vector<vector<PreviousConfiguration>>& PreviousConfigs,
	uint64_t Configuration,
	const Edge& edge,
	bool Recursed = false)
{
	size_t left = edge.Left - 1;
	size_t right = edge.Right - 1;

	const uint64_t previousConfiguration = (Configuration ^ (1ULL << right));

	const size_t previousConfigurationIndex = (size_t)(previousConfiguration);

	if (previousConfiguration != 0 &&
		Solution[(size_t)Configuration][right] - (Solution[previousConfigurationIndex][left] + edge.Cost) > EPS)
	{
		Solution[Configuration][right] = Solution[previousConfigurationIndex][left] + edge.Cost;
		PreviousConfigs[Configuration][right] = { previousConfiguration, left };
	}
	if (!Recursed)
		UpdateSolution(Solution, PreviousConfigs, Configuration, { edge.Right, edge.Left, edge.Cost }, true);
}

namespace GraphAlgorithms
{
	ChainedGraph HeldKarp(Graph& G, bool FixedEnds)
	{
		ChainedGraph result(G.GetSize());
		vector<vector<double>> solution;
		vector<vector<PreviousConfiguration>> previousConfigs;
		const size_t size = G.GetSize();
		const uint64_t allNodes = ((1ULL << size) - 1);

		solution.resize((1ULL << size));
		previousConfigs.resize((1ULL << size));
		for (uint64_t i = 0; i <= allNodes; i++)
		{
			previousConfigs[i].resize(size);
			for (size_t j = 0; j < size; j++)
			{
				solution[i].push_back(numeric_limits<double>::infinity());
			}
		}

		if (!FixedEnds)
		{
			solution[1][0] = 0;
		}
		else
		{
			size_t source = G.SourceNode - 1;
			solution[(1ULL << source)][source] = 0;
		}

		PreviousConfiguration config = { allNodes, 0 };
		double minimumCost = numeric_limits<double>::infinity();
		for (uint64_t i = 2; i <= allNodes; i++)
		{
			if ((i & (i - 1)) == 0)
				continue;
			for (auto& edge : G.GetEdges())
			{
				if (CheckEdgeAvailability(i, edge))
				{
					UpdateSolution(solution, previousConfigs, i, edge);
				}
			}

			if (FixedEnds)
			{
				if (minimumCost - solution[i][G.DestinationNode - 1] > EPS)
				{
					minimumCost = solution[i][G.DestinationNode - 1];
					config = { i, G.DestinationNode - 1 };
				}
			}
		}

		if (!FixedEnds)
		{
			for (size_t i = 1; i < size; i++)
			{
				if (solution[allNodes][i] + G.AdjacencyMatrix[i + 1][1] < minimumCost)
				{
					minimumCost = solution[allNodes][i] + G.AdjacencyMatrix[i + 1][1];
					config = { allNodes, i };
				}
			}
		}

		result.SetTotalCost(minimumCost);
		while (config.Configuration != 0)
		{
			/* add current node to sequential representation */
			result.AddNodeInChain(config.Node + 1);
			config = previousConfigs[(size_t)config.Configuration][config.Node];
		}

		return result;
	}

	Graph Kruskal(Graph& G, Predicate p, AuxiliaryFunction f)
	{
		DisjointSet set(G.GetSize());
		vector<Edge> sorted = G.GetEdges();
		vector<Edge> solution;
		Graph result(G.GetSize());

		std::sort(sorted.begin(), sorted.end());

		for (auto& edge : sorted)
		{
			if (p(set, edge))
			{
				f(edge);
				set.JoinNode(edge.Left, edge.Right);
				result.AddEdge(edge);
			}
		}

		return result;
	}
}