#pragma once

#include "Chromosome.h"
#include "Graph.h"

class GeneticAlgorithm
{
private:
	Graph& G;
	vector<Chromosome> Population;
	int ChromosomeSize;
	int Size;
	int GenerationNumber;
	int PrintSize;
	bool IsPopulationSorted;

	void SortPopulation();
	void PrintSummary();

    /* Leave the value to false for massive speed improvement;
       however, it won't show the middle steps when calculating the new generations */
	static const bool Verbose = false;

public: 
	static const int PopulationCount = 200;
	static const int NumberGenerations = 1000;

	GeneticAlgorithm() = delete;
	GeneticAlgorithm(Graph& G, int Size);
	void Populate();

    //virtual Chromosome& MakeSelection() = 0;
	void NewGeneration();

	void ComputeAll();
	Chromosome& GetBestChromosome();

	~GeneticAlgorithm() = default;
};
