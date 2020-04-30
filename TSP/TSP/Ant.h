#pragma once

#include "Graph.h"
#include "ValidationErrorType.h"
#include "AntColony.h"

#include <vector>

using std::vector;
using std::pair;

class Ant
{
    friend class AntColony;

private:
    const AntColony& Colony;
    const Graph& G;

    int InitialNode;
    int RouteSize;
    vector<int> Route;
    vector<bool> VisitedNodes;

    vector<pair<double, int>> Neighbors;
    int ComputeBestNeighbor();


public:
    Ant(const AntColony& Colony);

    ValidationErrorType Validate();
    const vector<int>& GetRoute() const;
    void ReleaseAgain();
    void ComputeRoute();

    double Phi(int Left, int Right);
    double GetRouteCost();

    ~Ant() = default;
};