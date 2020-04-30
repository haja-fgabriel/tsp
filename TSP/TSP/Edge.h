#pragma once

class Edge
{
public:
	int Left, Right;
	double Cost;

	Edge(int, int, double);

	Edge operator=(const Edge& other);

	bool operator<(const Edge& other) const;
	//bool operator==(const Edge& other);

	~Edge() = default;
};

