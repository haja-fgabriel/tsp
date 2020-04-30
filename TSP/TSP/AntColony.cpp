#include "Utils.h"
#include "AntColony.h"

AntColony::AntColony(Graph & G, double Alpha, double Beta, double Q, double Ro, double TauMax)
    : G{ G }, RouteSize{ G.GetSize() }, Alpha{ Alpha }, Beta{ Beta }, Q{ Q }, Ro{ Ro }, TauMax{ TauMax }
{
    Initialize();
}

void AntColony::InitializePheromone()
{
    int size = G.GetSize();
    Pheromone.resize(size + 1);
    DeltaPheromone.resize(size + 1);
    for (int i = 1; i <= size; i++)
    {
        Pheromone[i].resize(size + 1);
        DeltaPheromone[i].resize(size + 1);
    }

    for (int i = 1; i <= size; i++)
    {
        for (int j = i; j <= size; j++)
        {
            Pheromone[i][j] = Utils::GenerateDouble(0.0, 1.0) * TauMax;
            Pheromone[j][i] = Pheromone[i][j];
        }
    }
}

void AntColony::InitializeColony()
{
    for (int i = 0; i < ColonySize; i++)
    {
        Colony.push_back(Ant(*this));
    }
}

void AntColony::Initialize()
{
    ColonySize = G.GetSize() / 2;
    InitializeColony();
    InitializePheromone();
}

void AntColony::UpdatePheromones()
{
    for (int i = 0; i < ColonySize; i++)
    {
        double routeLength = Colony[i].GetRouteCost();
        for (int j = 0; j < RouteSize - 1; j++)
        {
            int currentNode = Colony[i].GetRoute()[j];
            int nextNode = Colony[i].GetRoute()[j + 1];

            DeltaPheromone[currentNode][nextNode] += Q / routeLength;
            DeltaPheromone[nextNode][currentNode] += Q / routeLength;
        }
    }

    for (int i = 1; i <= RouteSize; i++)
    {
        for (int j = 1; j <= RouteSize; j++)
        {
            Pheromone[i][j] = (1 - Ro) * Pheromone[i][j] + DeltaPheromone[i][j];
            DeltaPheromone[i][j] = 0.0;
        }
    }
}


void AntColony::Optimize(int Iterations)
{
    int initTime = Time;
    for (; Time < initTime + Iterations; Time++)
    {
        for (int i = 0; i < ColonySize; i++)
        {
            while (Success != Colony[i].Validate())
            {
                Colony[i].ReleaseAgain();
                Colony[i].ComputeRoute();
            }

            /* TODO print solution for given ant */

            double routeLength = Colony[i].GetRouteCost();
            if (BestLength < routeLength)
            {
                BestLength = routeLength;
                BestRoute = Colony[i].GetRoute();
            }
            
        }
        UpdatePheromones();
    }
}

double AntColony::GetBestLength() const
{
    return BestLength;
}

const vector<int>& AntColony::GetBestRoute() const
{
    return BestRoute;
}
