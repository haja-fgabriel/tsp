#pragma once

#include "Graph.h"

#include <vector>
#include <utility>
#include <memory>

using std::vector;

class Chromosome
{
private:
	Graph* G = nullptr;
	vector<int> Permutation;
	int Size;
	double Fitness;
	bool IsFitnessComputed = false;

public:
	
	Chromosome() = default;
	
	// Constructor used in tests
	Chromosome(int Size);
	Chromosome(Graph* G, int Size);
	Chromosome(Graph* G, int Size, const vector<int> Representation);

	const vector<int>& GetPermutation();
	Chromosome Crossover(const Chromosome& other);
	void ApplyMutation();

	double ComputeFitness();
	int GetSize();

	void PrintRepresentation();

	~Chromosome() = default;
};

