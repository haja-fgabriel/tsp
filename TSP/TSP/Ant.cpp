#include "Ant.h"
#include "Utils.h"

#include <cmath>

Ant::Ant(const AntColony& Colony) 
    : Colony{Colony}, G{Colony.G}, RouteSize{Colony.RouteSize}
{
    InitialNode = Utils::GenerateInteger(1, RouteSize);
    RouteSize = G.GetSize();
}

ValidationErrorType Ant::Validate()
{
    if (Route.size() < RouteSize)
    {
        return NotEnoughNodes;
    }


    VisitedNodes.clear();
    VisitedNodes.resize(RouteSize + 1, false);

    for (int i = 0; i < RouteSize - 1; i++)
    {
        int current = Route[i];
        int next = Route[i + 1];
        if (current < 0 || next < 0)
            return InvalidNode;
        
        if (!G.IsEdgeExisting(current, next))
            return UnexistingEdge;

        if (VisitedNodes[next] == true)
            return DuplicateNodes;

        VisitedNodes[current] = true;
        VisitedNodes[next] = true;
    }


    if (!G.IsEdgeExisting(Route.back(), Route.front()))
        return UnexistingFinalEdge;
    return Success;
}

const vector<int>& Ant::GetRoute() const
{
    return Route;
}

void Ant::ReleaseAgain()
{
    Route.clear();
    VisitedNodes.clear();
    VisitedNodes.resize(RouteSize + 1, false);
}

void Ant::ComputeRoute()
{

    Route.push_back(InitialNode);
    VisitedNodes[InitialNode] = true;

    for (int i = 0; i < RouteSize - 1; i++)
    {
        int currentNode = Route[i];
        Neighbors.clear();
        int nextNode = 1;
        for (; nextNode <= RouteSize; nextNode++)
        {
            if (currentNode != nextNode && G.IsEdgeExisting(currentNode, nextNode) && !VisitedNodes[nextNode])
            {
                pair<double, int> neighbor = { Phi(currentNode, nextNode), nextNode };
                Neighbors.push_back(neighbor);
            }
        }
        if (Neighbors.empty())
            return;

        nextNode = ComputeBestNeighbor();
        Route.push_back(nextNode);
        VisitedNodes[nextNode] = true;
    }
}

double Ant::Phi(int Left, int Right)
{
    double eta = (double)pow(1 / G.AdjacencyMatrix[Left][Right], Colony.Beta);
    double tau = (double)pow(Colony.Pheromone[Left][Right], Colony.Alpha);

    double sum = 0.0;   

    for (int i = 1; i <= RouteSize; i++)
    {
        if (Left != i && G.IsEdgeExisting(Left, i) && !VisitedNodes[i])
        {
            double etaNeighbor = (double) pow(1 / G.AdjacencyMatrix[Left][i], Colony.Beta);
            double tauNeighbor = (double)pow(Colony.Pheromone[Left][i], Colony.Alpha);

            sum += etaNeighbor * tauNeighbor;
        }
    }
    return (eta * tau) / sum;
}

double Ant::GetRouteCost()
{
    double sum = 0.0;
    for (int i = 0; i < RouteSize - 1; i++)
    {
        sum += G.AdjacencyMatrix[Route[i]][Route[i + 1]];
    }
    return sum + G.AdjacencyMatrix[Route.back()][Route.front()];
}

int Ant::ComputeBestNeighbor()
{
    double target = Utils::GenerateDouble(0.0, 1.0);
    int i = 0;
    double sum = Neighbors[i].first;
    
    while (sum < target)
    {
        i++;
        sum += Neighbors[i].first;
    }
    
    return Neighbors[i].second;
}
