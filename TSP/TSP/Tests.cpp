#include "Tests.h"
#include "Utils.h"
#include "Chromosome.h"

#include <unordered_map>
#include <cassert>
#include <iostream>

static bool CheckIfPermutation(vector<int> elements, bool verbose = false)
{
	std::unordered_map<int, int> elemCounts;
	if (verbose)
		std::cout << "[TEST] Contents: ";

	for (auto elem : elements)
	{
		if (verbose)
			std::cout << elem << ' ';
		elemCounts[elem]++;
	}
	if (verbose)
		std::cout << '\n';

	for (int i = 1; i <= elements.size(); i++)
	{
		if (elemCounts[i] != 1)
			return false;
	}
	return true;
}

static void TestGeneratePermutation()
{
	vector<int> solution = Utils::GeneratePermutation(30);
	assert(CheckIfPermutation(solution));

}

static void TestGenerateInteger()
{
	int generated = Utils::GenerateInteger(1, 2000000000);
	assert(generated >= 1 && generated <= 2000000000);
}

static void TestChromosomes()
{
	Chromosome c(30);
	Chromosome c2(30);
	Chromosome newChromosome = c.Crossover(c2);
	assert(CheckIfPermutation(newChromosome.GetPermutation()));
	c.ApplyMutation();
	assert(CheckIfPermutation(newChromosome.GetPermutation()));
}

static void RunTest(void(*Functor)())
{
	for (int i = 1; i <= 1000; i++)
	{
		Functor();
	}
	std::cout << "[TEST] Test passed.\n";
}

namespace Tests
{
	void RunTests()
	{
		RunTest(TestGeneratePermutation);
		RunTest(TestGenerateInteger);
		RunTest(TestChromosomes);
	}
}
