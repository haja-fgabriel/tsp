#include <Windows.h>
#include <iostream>

#include "Graph.h"
#include "GraphService.h"

#define NO_TESTS
#include "Tests.h"

#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <ctime>

using std::string;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <filename>\n";
		ExitProcess(1);
	}
#ifndef NO_TESTS
	Tests::RunTests();
#endif

	string inFile = string(argv[1]);
	Graph gr(inFile);
	GraphService service(gr);
	
	inFile.replace(inFile.find(".txt"), string::npos, "_solution.txt");

	std::ofstream outFile(inFile);

    clock_t timeElapsed = clock();

    /* using the ACO implementation, multiple implementations available */
	ChainedGraph result = service.GetShortestCyclicPath_ACO();

    timeElapsed = clock() - timeElapsed;
    
    std::cout << "Execution time: " << ((float)timeElapsed) / CLOCKS_PER_SEC << " seconds.\n";

	outFile << result << '\n';

	return 0;
}