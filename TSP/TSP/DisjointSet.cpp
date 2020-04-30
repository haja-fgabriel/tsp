#include "DisjointSet.h"

DisjointSet::DisjointSet(int Size) : Size{Size}
{
	Parent.push_back(0);
	for (int i = 1; i <= Size; i++)
	{
		Parent.push_back(i);
	}
}

void DisjointSet::JoinNode(int Set, int Node)
{
	Parent[Node] = Set;
}

int DisjointSet::FindSet(int Node)
{
	int root = Node;
	while (Parent[root] != root)
	{
		root = Parent[root];
	}
	int aux;
	while (Parent[Node] != Node)
	{
		aux = Parent[Node];
		Parent[Node] = root;
		Node = aux;
	}
	return root;
}

DisjointSet::~DisjointSet()
{
}
