#include "Utils.h"

#include <unordered_map>
#include <random>

std::random_device gSeeder;
std::mt19937 gGenerator(gSeeder());

namespace Utils
{
	vector<int> GeneratePermutation(int Size)
	{
		std::unordered_map<int, bool> isUsed;
		vector<int> permutation;
		std::uniform_int_distribution<int> distribution(1, Size);

		for (int i = 0; i < Size; i++)
		{
			int x;
			do
			{
				x = distribution(gGenerator);
			} while (isUsed[x]);

			isUsed[x] = true;
			permutation.push_back(x);
		}

		return permutation;
	}

	int GenerateInteger(int Left, int Right)
	{
		std::uniform_int_distribution<int> distribution(Left, Right);
		return distribution(gGenerator);
	}

    double GenerateDouble(double Left, double Right)
    {
        std::uniform_real_distribution<double> distribution(Left, Right);
        return distribution(gGenerator);
    }
}