#pragma once

#include <vector>

using std::vector;

class DisjointSet
{
	int Size;
	vector<int> Parent;

public:
	DisjointSet(int Size);

	void JoinNode(int Set, int Node);
	int FindSet(int Node);

	~DisjointSet();
};

