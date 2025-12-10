#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "invalid usage." << std::endl;
		return -1;
	}

	std::ifstream ifs(argv[1]);

	if (!ifs.is_open())
	{
		std::cout << "invalid input." << std::endl;
		return -1;
	}

	int total_joltage = 0;

	std::string bank;
	while (std::getline(ifs, bank))
	{
		int left = 0;
		int right = 0;

		

		total_joltage += left * 10 + right;
	}

	std::cout << "total joltage: " << total_joltage << std::endl;

	return 0 ;
}