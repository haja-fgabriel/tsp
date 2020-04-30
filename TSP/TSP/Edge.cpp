#include "Edge.h"
#include "Utils.h"

Edge::Edge(int Left, int Right, double Cost) 
	: Left{ Left }, Right{ Right }, Cost{ Cost } { }


Edge Edge::operator=(const Edge & other)
{
	Left = other.Left;
	Right = other.Right;
	Cost = other.Cost;
	return *this;
}

bool Edge::operator<(const Edge & other) const
{
	return Cost - other.Cost < -EPS;
}

