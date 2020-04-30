#include "ChainedGraph.h"

#include <algorithm>

ChainedGraph::ChainedGraph(int size) 
	: Size{size} {}

ChainedGraph::ChainedGraph(Graph & G) : Size{G.GetSize()}
{
	TransformRepresentation(G.GetEdges());
}

ChainedGraph::ChainedGraph(int Size, const vector<int>& Path, double Cost)
	: Size{Size}, Chain(Path.begin(), Path.end()), TotalCost{Cost} {}

void ChainedGraph::TransformRepresentation(const vector<Edge>& edges)
{
	size_t currentNode;
	size_t nextNode;
	vector<vector<size_t>> adjacencyList;
	adjacencyList.resize(Size + 1);

	TotalCost = 0;
	for (auto& edge : edges)
	{
		TotalCost += edge.Cost;
		currentNode = edge.Left;
		adjacencyList[edge.Left].push_back(edge.Right);
		adjacencyList[edge.Right].push_back(edge.Left);
	}

	Chain.push_back(currentNode);
	while (!adjacencyList[currentNode].empty())
	{
		nextNode = adjacencyList[currentNode].back();
		adjacencyList[currentNode].pop_back();
		adjacencyList[nextNode].erase(std::find(adjacencyList[nextNode].begin(), adjacencyList[nextNode].end(), currentNode));

		currentNode = nextNode;
		Chain.push_back(nextNode);
	}
}

ChainedGraph::ChainedGraph(int Size, const vector<Edge>& edges) : Size{Size}
{
	TransformRepresentation(edges);
}

void ChainedGraph::AddNodeInChain(size_t Node)
{
	Chain.push_front(Node);
}

void ChainedGraph::SetTotalCost(double NewCost)
{
	TotalCost = NewCost;
}

ostream & operator<<(ostream & g, ChainedGraph & graph)
{
	g << graph.Chain.size() << '\n';
	deque<size_t>::iterator it = graph.Chain.begin();
	for (int i = 0; i < graph.Chain.size(); i++)
	{
		g << *it;
		if (it + 1 != graph.Chain.end())
			g << ",";
		it++;
	}
	g << '\n' << graph.TotalCost;
	return g;
}
