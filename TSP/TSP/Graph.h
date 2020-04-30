#pragma once

#include <vector>
#include <string>
#include "Edge.h"

using std::vector;
using std::string;

class Graph
{
private:
	int Size;
	vector<Edge> Edges;

public:
	size_t SourceNode;
	size_t DestinationNode;

	vector<vector<double>> AdjacencyMatrix;

	Graph(int);
	Graph(const string&);
	
	vector<Edge>& GetEdges();
	int GetSize() const;

    bool IsEdgeExisting(int Left, int Right) const;

	void AddEdge(const Edge&); 

	~Graph();
};

