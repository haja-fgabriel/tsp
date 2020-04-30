#pragma once

#include <vector>

using std::vector;



#define EPS (1e-5)
#define INF (1LL * 0x3F3F3F3F3F3F3F3F)
#define UINT64_BIT (64)

namespace Utils
{
	vector<int> GeneratePermutation(int Size);
	int GenerateInteger(int Left, int Right);
    double GenerateDouble(double Left, double Right);
}