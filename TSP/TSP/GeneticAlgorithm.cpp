#include "GeneticAlgorithm.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <functional>

using std::function;

void GeneticAlgorithm::SortPopulation()
{
	function<bool(Chromosome&, Chromosome&)> sortByFitness = [&](Chromosome& a, Chromosome& b) {
		return a.ComputeFitness() < b.ComputeFitness();
	};

	std::sort(Population.begin(), Population.end(), sortByFitness);
	IsPopulationSorted = true;
}

void GeneticAlgorithm::PrintSummary()
{
#ifdef _WIN32
	system("cls");
#elif __unix__
	system("clear");
#endif

	std::cout << "[INFO] Generation " << GenerationNumber
		<< " - best solution: " << Population.front().ComputeFitness() << '\n';

	for (int i = 0; i < PrintSize; i++)
	{
		std::cout << "Chromosome #" << i << " - fitness "
			<< Population[i].ComputeFitness() << ";\t\tpath: ";
		
		Population[i].PrintRepresentation();

		std::cout << '\n';
	}
}

GeneticAlgorithm::GeneticAlgorithm(Graph& G, int Size) : Size{Size}, G{G}, ChromosomeSize{G.GetSize()}
{
	PrintSize = std::min(6, Size);
	Populate();
}

void GeneticAlgorithm::Populate()
{
	Population.clear();
	for (int i = 0; i < Size; i++)
	{
		Population.push_back(Chromosome(&G, ChromosomeSize));
	}

}

void GeneticAlgorithm::NewGeneration()
{
	vector<Chromosome> newPopulation;

	for (int i = 0; i < Size; i += 2)
	{
		Chromosome& c1 = Population[i];
		Chromosome& c2 = Population[i + 1];
		
		Chromosome son = c1.Crossover(c2);
		son.ApplyMutation();

		newPopulation.push_back(c1);
		newPopulation.push_back(c2);
		newPopulation.push_back(son);
	}
	
	Population = std::move(newPopulation);
	IsPopulationSorted = false;

	SortPopulation();

	/* Remove as many chromosomes as we crossed over, to keep the constant size */
	int toRemove = Size / 2;
	for (int i = 0; i < toRemove; i++)
	{
		Population.pop_back();
	}

	GenerationNumber++;

	if (Verbose)
	{
        PrintSummary();
	}
}

void GeneticAlgorithm::ComputeAll()
{
	for (int i = 0; i < GeneticAlgorithm::NumberGenerations; i++)
	{
		NewGeneration();
	}

}

Chromosome& GeneticAlgorithm::GetBestChromosome()
{
	if (!IsPopulationSorted)
	{
		SortPopulation();
	}
	return Population.front();
}
