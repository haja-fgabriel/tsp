#include "Chromosome.h"

#include "Utils.h"
#include <exception>
#include <algorithm>
#include <unordered_map>
#include <iostream>

Chromosome::Chromosome(Graph* G, int Size)
	: G{G}, Size{ Size }, Permutation{ Utils::GeneratePermutation(Size) } {}

Chromosome::Chromosome(Graph* G, int Size, const vector<int> Representation)
	: G{G}, Size{ Size }, Permutation{ Representation } {}

Chromosome::Chromosome(int Size)
	: Size{ Size }, Permutation{ Utils::GeneratePermutation(Size) } {}

const vector<int>& Chromosome::GetPermutation() 
{ 
	return Permutation;
}

Chromosome Chromosome::Crossover(const Chromosome & other)
{
	if (other.Size != Size)
		throw new std::exception("Lengths of chromosomes must be identical");
	
	int position1 = Utils::GenerateInteger(0, Size - 1);
	int position2 = Utils::GenerateInteger(0, Size - 1);

	if (position1 > position2)
		std::swap(position1, position2);

	std::unordered_map<int, bool> isUsed;
	vector<int> newRepresentation;
	vector<int>::iterator begin = Permutation.begin();
	for (int i = position1; i < position2; i++)
	{
		newRepresentation.push_back(Permutation[i]);
		isUsed[Permutation[i]] = true;
	}

	int insertOffset = 0;

	for (int i = 0; i < Size; i++)
	{
		int index = (position2 + i) % Size;
		
		if (isUsed[other.Permutation[index]])
			continue;
		isUsed[other.Permutation[index]] = true;
		if (newRepresentation.size() < Size - position1)
		{
			newRepresentation.push_back(other.Permutation[index]);
		}
		else
		{
			newRepresentation.insert(
				newRepresentation.begin()+insertOffset,
				other.Permutation[index]);
			insertOffset++;
		}
	}
	Chromosome offspring(G, Size, newRepresentation);
	return offspring;
}

void Chromosome::ApplyMutation()
{
	int position1 = Utils::GenerateInteger(0, Size - 1);
	int position2 = Utils::GenerateInteger(0, Size - 1);

	if (position1 > position2)
		std::swap(position1, position2);

	vector<int>::iterator begin = Permutation.begin();
	std::swap(*(begin + position1), *(begin + position2));
}

double Chromosome::ComputeFitness()
{
	if (!IsFitnessComputed)
	{
		Fitness = 0;
		for (int i = 0; i < Permutation.size() - 1; i++)
		{
			int Left = Permutation[i];
			int Right = Permutation[i + 1];

			Fitness += G->AdjacencyMatrix[Left][Right];
		}
		Fitness += G->AdjacencyMatrix[Permutation.front()][Permutation.back()];
		IsFitnessComputed = true;
	}
	return Fitness;
}

int Chromosome::GetSize()
{
	return Size;
}

void Chromosome::PrintRepresentation()
{
	for (auto& x : GetPermutation())
	{
		std::cout << x << ' ';
	}
}
