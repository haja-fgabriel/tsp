#include "Graph.h"
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <cmath>

using std::fstream;

Graph::Graph(int Size) 
	: Size{Size} {}

Graph::Graph(const string & Filename)
{
	fstream f(Filename);
	double cost;

	f >> Size;
    //AdjacencyMatrix.push_back(vector<double>());
	AdjacencyMatrix.resize(Size + 1);

	for (int i = 1; i <= Size; i++)
	{
		AdjacencyMatrix[i].resize(Size + 1, nan(""));
		for (int j = 1; j <= Size; j++)
		{
			f >> cost;
			AdjacencyMatrix[i][j] = cost;

			/* ignora virgula */
			if (j < Size)
				f.ignore(1); 

			/* adauga noua muchie */
			if (i < j)
				Edges.push_back(Edge(i, j, cost));
		}
	}
	f >> SourceNode >> DestinationNode;
}

vector<Edge>& Graph::GetEdges()
{
	return Edges;
}

int Graph::GetSize() const
{
	return Size;
}

bool Graph::IsEdgeExisting(int Left, int Right) const
{
    return !isnan(AdjacencyMatrix[Left][Right]);
}

void Graph::AddEdge(const Edge& e)
{
	Edges.push_back(e);
}

Graph::~Graph()
{
}
